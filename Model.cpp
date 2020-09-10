
/*
    public:
        bool SuccessfulAttack(const Point&) const;//return true if there is no police in 10km radius from the point*/
#include "Model.h"
#include <utility>
#include <typeinfo>
#include <algorithm>//somthing 
#include <sstream>
#include <climits>
#include "Chopper.h"
#include "Truck.h"
#include <cmath>
#include "TrooperState.h"
using namespace std;
/***********************************************************************private methods ******************************************************************************/
Model::Model():nameANDtype(),mapObjects(),commends(),view(),time(0),factory(VehicleFactory::getInstance()){
    addToMap(shared_ptr<MapObject>(new Warehouse("Frankfurt",Point(40,10),100000)));
}

void Model::addToMap(const std::shared_ptr<MapObject>& p)//add map object use in addMapObjects
{
    string type=getMapObjectType(p);
    mapObjects.emplace(type,p);
    nameANDtype.emplace(p->getName(),type);
}


string Model::getMapObjectType(const std::shared_ptr<MapObject>& p) const//return the string of that map objects
{
    if(typeid(*p)==typeid(Warehouse))
        return "Warehouse";
    if(typeid(*p)==typeid(Truck))
        return "Truck";
    if(typeid(*p)==typeid(Chopper))
        return "Chopper"; 
    if(typeid(*p)==typeid(TrooperState))
        return "TrooperState";
    return "";
}

vector<shared_ptr<MapObject>> Model::copyAllMapObject()
{
    vector<shared_ptr<MapObject>> ret;
    for(auto it:mapObjects)
        ret.push_back(it.second);
    return ret;
}
void Model::updateView()
{
    for(auto tmp:mapObjects)
    {
        if(typeid(*tmp.second)==typeid(Warehouse))
            continue;
        //else is a type a vehicle
        Vehicles& v=dynamic_cast<Vehicles&>(*tmp.second);
        v.update();
    }
    view.push(copyAllMapObject());
}


void Model::status() const// print the status of every object in the map
{
    for_each(mapObjects.begin(),mapObjects.end(),[](const pair<string,shared_ptr<MapObject>>& p){ cout << *p.second <<endl;});
}
void Model::create(vector<string>& arg)//the vector look like this [name of vehicle,type of vehicle,point or warehose to start from]
{
    swap(arg[1],arg[2]);
    addToMap(factory.makeVehicle(arg));
}
void Model::course(const vector<string>& arg)//if it is a TrooperState -> arg.size()=3 (name,curse,angle) and it is a Chopper -> arg.size()=4 (name,curse,angle,speed)
{//change the car
    float direction,speed;
    Vehicles &car=dynamic_cast<Vehicles&>(*findMapObjectByName(arg[0]));
    stringstream stream(arg[2]);
    stream>>direction;
    car.setDirection(direction);
    if(arg.size()==4){
        stringstream temp(arg[3]);
        temp>>speed;
        car.setSpeed(speed);
    }
    car.Course(direction);
}
void Model::position(const vector<string>& arg)//if it is a TrooperState -> arg.size()=3 (name,position,Point) and it is a Chopper -> arg.size()=4 (name,position,Point,speed)
{
    float speed;
    Vehicles &car=dynamic_cast<Vehicles&>(*findMapObjectByName(arg[0]));
    stringstream stream(arg[2]);
    Point p(arg[2]);
    if(arg.size()==4){
        stream>>speed;
        car.setSpeed(speed);
    }
    car.Position(p);   
}
void Model::destination(const vector<string>& arg)//only a TrooperState -> arg.size()=3 (name,destination,warehose name)
{
    if(!existInTheMap(arg[0])){
        cout<<mapObjects.size()<<endl;
        return;
    }
    TrooperState &car=dynamic_cast<TrooperState&>(*findMapObjectByName(arg[0]));
    car.Destination(arg[2]);
}

void Model::stopped(const string& arg){
    Vehicles &car=dynamic_cast<Vehicles&>(*findMapObjectByName(arg));
    car.Stop();

}

bool Model::SuccessfulAttack(const Point& p) const//return true if there is no police in 10km radius from the point
{
    auto police=mapObjects.find("TrooperState");//return all the TrooperState in the map
    while(police!=mapObjects.end())
    {
        Point tmp_p=(police->second->getLocation());
        if((p-tmp_p)<=0.1)
            return false;
    }
    return true;
}


bool Model::attack(const vector<string>& arg)// arg=[Chopper name,"attack",Truck name]
{
    Chopper &c=dynamic_cast<Chopper&>(*findMapObjectByName(arg[0])); 
    Truck &t=dynamic_cast<Truck&>(*findMapObjectByName(arg[2]));
    c.Stop();
    if((c.getAttackRange()<(c.getLocation()-t.getLocation())) || !(SuccessfulAttack(c.getLocation()))){
        c--;
        return false;
    }
    t.Attack();
    c++;
    return true;
}

/***********************************************************************public methods ******************************************************************************/

Model& Model::getInstance()
{
    static Model model;
    return model;
}

Model::~Model(){}

void Model::addMapObjects(const vector<shared_ptr<MapObject>>& objects)
{
    for(auto p:objects)
        addToMap(p);
    view.push(copyAllMapObject());
}

bool Model::existInTheMap(string str) const//receive a of an object and return true if it is in the map
{
    return (nameANDtype.find(str)!=nameANDtype.end());
}

shared_ptr<MapObject> Model::findMapObjectByName(string str) const//return a pointer to map object or null if this object dose not exist
{
    if(!existInTheMap(str))
        return shared_ptr<MapObject>();
    string type = nameANDtype.find(str)->second;
    auto res=find_if(mapObjects.find(type),mapObjects.end(),[&str](const pair<string,shared_ptr<MapObject>>& a)->bool{
        return (!str.compare(a.second->getName()));
    });
    return res->second;
}

unsigned int Model::getTime() const
{
    return time;
}

Warehouse& Model::getClosestWarehouse(const Point& p) const
{
    pair<shared_ptr<MapObject>,float> minDis(shared_ptr<MapObject>(),UINT_MAX);
    auto tmp=mapObjects.find("Warehouse");
    while(tmp!=mapObjects.end())
    {
        Point tmp_p=(tmp->second->getLocation());
        float sum=((p.getX()-tmp_p.getX())*(p.getX()-tmp_p.getX()))+((p.getY()-tmp_p.getY())*(p.getY()-tmp_p.getY()));
        float dis=sqrt(sum);
        if(dis<minDis.second){
            minDis.first=(tmp->second);
            minDis.second=dis;
        }
        tmp++;
    }
    return dynamic_cast<Warehouse&>(*minDis.first);
}


const Point& Model::FindWarehouse(const std::string& name) const
{
    return findMapObjectByName(name)->getLocation();
}

void Model::addCommend(Model::COMMENDS c,const vector<string>& arg)//add commend to the queue
//assuming the commend and all the arguments are ok 
{
    commends.emplace(pair<Model::COMMENDS,vector<string>>(c,arg));
}

View& Model::getView()
{
    return view;
}

void Model::_go()
{
    time++;
    while(!commends.empty())
    {
        auto pair=commends.front();
        auto commend=pair.first;
        switch (commend)
        {
            case Model::STATUS:
                status();
                break;
            case Model::CREATE:
                create(pair.second);
                break;
            case Model::COURSE:
                course(pair.second);
                break;
            case Model::POSITION:
                position(pair.second);
                break;
            case Model::DESTINATION:
                destination(pair.second);
                break;
            case Model::ATTACK:
                attack(pair.second);
                break;
            case Model::STOPPED:
                stopped(pair.second[0]);
                break;
        }
        commends.pop();
    }
    updateView();
}