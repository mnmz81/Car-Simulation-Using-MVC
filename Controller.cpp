#include "Controller.h"

using namespace std;

/**************************************************************** private methods *******************************************************************/
vector<string> Controller::getDataFromCin(){
    vector<string> tmp;
    string line;
    string temp1;
    getline(cin,line);
    string::iterator b=line.begin();
    string::iterator e=line.end();
    while (b!=e)
    {
        while (b!=e && *b!=' '){
            temp1+=*b;
            b++;
        }
        if(*(b-1)==','){
            b++;
            continue;
        }
        tmp.push_back(temp1);
        temp1.clear();
        
        if(b==e) return tmp;
        b++;
    }
    return tmp;
 }
/***************************************************************/
void Controller::PrintLineInTheBegin()
{
    cout<<"Time "<<Model::getInstance().getTime()<<" : Enter command: ";
}


/**************************************************************** public methods *******************************************************************/

Controller::Controller(){}
/****************************************************/
Controller::~Controller(){}
/***************************************************/
void Controller::Go()
{
    Model::getInstance()._go();
}
/****************************************************/
void Controller::Show()
{
    Model::getInstance().getView()._show(cout);
}
/****************************************************/
void Controller::Stop(vector<string>& temp)
{
    Model::getInstance().addCommend(Model::STOPPED,temp);
}

/****************************************************/
void Controller::Default()
{
     Model::getInstance().getView()._default();
}
/****************************************************/
void Controller::Size(string& s)
{
    string temp;
    string::iterator b=s.begin();
    string::iterator e=s.end();
    for(;b!=e && isdigit(*b);temp+=*b,b++);
    if(b!=e) throw ErrorIllegalCommand();
    if(stoi(temp)<6 || stoi(temp)>30 ) throw ErrorIllegalCommand();
    Model::getInstance().getView()._size(stoi(temp));
}
/****************************************************/
void Controller::Zoom(string& s)
{
    string temp;
    string::iterator b=s.begin();
    string::iterator e=s.end();
    for(;b!=e && isdigit(*b);temp+=*b,b++);
    if(b!=e) throw ErrorIllegalCommand();
    if(stoi(temp)<0) throw ErrorIllegalCommand();
    Model::getInstance().getView()._zoom(stoi(temp));
}
/****************************************************/
void Controller::Pan(vector<std::string>& temp)
{
    if(temp.size()!=3)  throw ErrorIllegalCommand();;
    string x,y;
    string::iterator b=temp[1].begin();
    string::iterator e=temp[1].end();
    for(;b!=e && isdigit(*b);x+=*b,b++);
    if(b!=e) throw ErrorIllegalCommand();
    b=temp[2].begin();
    e=temp[2].end();
    for(;b!=e && isdigit(*b);y+=*b,b++);
    if(b!=e) throw ErrorIllegalCommand();
    Point tmp(stoi(x),stoi(y));
    Model::getInstance().getView()._pan(tmp);
}
/***************************************************/
void Controller::Status()
{
    Model::getInstance().status();
}
/****************************************************/
void Controller::Create(vector<string>& temp)
{
    if(Model::getInstance().existInTheMap(temp[1]))throw ErrorIllegalCommand();
    if(temp[2]=="Chopper"){
        Model::getInstance().addCommend(Model::CREATE,temp);
        return;
    }
    if(temp[2]=="State_trooper"&& Model::getInstance().existInTheMap(temp[3])){
        Model::getInstance().addCommend(Model::CREATE,temp);
        return;
    }
    throw ErrorIllegalCommand();
}
/****************************************************/
void Controller::Attack(vector<string>& temp)
{
    if(temp.size()!=3 || ( (Model::getInstance().existInTheMap(temp[2]) && (typeid(Model::getInstance().findMapObjectByName(temp[2])).name()!="Truck")))) throw ErrorIllegalCommand();
    if(typeid(*Model::getInstance().findMapObjectByName(temp[0])).name()=="Chopper")
        Model::getInstance().addCommend(Model::ATTACK,temp);
    else  throw ErrorIllegalCommand();
}
/****************************************************/
void Controller::Course(vector<string>& temp)
{
    Model::getInstance().addCommend(Model::COURSE,temp);
}
/****************************************************/
void Controller::Position(vector<string>& temp)
{
    Model::getInstance().addCommend(Model::POSITION,temp);
}
/****************************************************/
void Controller::Destination(vector<string>& temp)
{
    if((!(Model::getInstance().existInTheMap(temp[2])))) throw ErrorIllegalCommand();
    Model::getInstance().addCommend(Model::DESTINATION,temp);
}
/****************************************************/
void Controller::Init(int argc, char *argv[])
{
    string temp;
    try{
        vector<shared_ptr<MapObject>> truckArray;
        shared_ptr<MapObject> t(new Truck());
        if (argc < 4) throw ErrorNumOfArgument();
        temp=argv[1];
        if (temp != "-w") throw ErrorInFlagsOfArgument();
        temp=argv[3];
        if (temp != "-t") throw ErrorInFlagsOfArgument();
        temp=argv[2];
        FileHandlerWarehouse wr(temp);
        Model::getInstance().addMapObjects(wr.getWarehouseArray());
        for (int i = 4; i < argc; i++)
        {
            temp=argv[i];
            t.reset(new Truck(temp));
            truckArray.push_back(t);
        }
        Model::getInstance().addMapObjects(truckArray); 
    }
    catch (ErrorNumOfArgument& e)
    {
        e.PrintError();
        exit(1);
    }
    catch (ErrorInFlagsOfArgument& e)
    {
        e.PrintError();
        exit(1);
    }
    Run();
    
}
/****************************************************/
void Controller::Run()
{
    vector<string> line;
    while (true){
        try{
            PrintLineInTheBegin();
            line=getDataFromCin();
            if(line.size()==0) throw ErrorIllegalCommand();
            if(line.size()==1){
                if(line[0]=="exit") {cout<<"\nBye Bye"<<endl;exit(1);}
                if(line[0]=="go") {Go();continue;} //לעבור על העדכון
                if(line[0]=="show") {Show();continue;}
                if(line[0]=="default") {Default();continue;}
                if(line[0]=="status") {Status();continue;}
                throw  ErrorIllegalCommand();
            } 
            if(line.size()==2){
                    if(line[0]=="size") {Size(line[1]);continue;}
                    if(line[0]=="zoom") {Zoom(line[1]);continue;}
                    throw  ErrorIllegalCommand();
            }
            if(line[0]=="pan") {Pan(line);;continue;}
            if(line[0]=="create"){Create(line);continue;}
            if(line[1]=="course"){Course(line);continue;}
            if(line[1]=="position"){Position(line);continue;}
            if(line[1]=="attack"){Attack(line);continue;}
            if(line[1]=="stop") {Stop(line);continue;}
            if(line[1]=="destination") {Destination(line);continue;}
            throw  ErrorIllegalCommand();
        }
        catch (ErrorIllegalCommand& e)
        {
            e.PrintError();
        }
    }
}
/****************************************************/