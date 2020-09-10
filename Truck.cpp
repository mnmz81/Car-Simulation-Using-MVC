#include "Truck.h"
#include "FileHandlerTruck.h"
#include "Model.h"
using namespace  std;

/***********************************************************************private methods ******************************************************************************/
void Truck::unloadingBox(){sumOfAllDelivery-=DeliveryArray[0]->getNumberOfBoxes();};
/***********************************************************************/
void Truck::speedOfTruck(Point& from, Point& to,Delivery& times )
{
  float dis = distancePoints(from,to);
  dis *= 100;
  float tmpTime=((times.getDepartureTime().getHour() + (times.getDepartureTime().getMinutes() / 60))
    -(times.getArrivalTime().getMinutes() + (times.getArrivalTime().getMinutes()/60)));
   this->speed = dis/tmpTime;
}
/************************************************************************/
float Truck::distancePoints(Point& from, Point& to)
{
  return sqrt(pow(from.getX()-to.getX(), 2) + pow(from.getY()-to.getY(), 2));
}
/************************************************************************/
float Truck::anglePoints(Point& from, Point& to)
{
    if(from.getX()==to.getX()) return 0; 
    return tan((to.getY()-from.getY())/(to.getX()-from.getX()));
}

/**************************************************************** public methods *******************************************************************/
Truck::Truck(){}
/****************************************/
Truck::Truck(string fileName)
{
    
    FileHandlerTruck temp(fileName);

    this->states=PARKEDD;
    this->name=temp.getTruckName();
    this->DeliveryArray=move(temp.getDeliveryArray());
    this->sumOfAllDelivery=temp.getSumOfBox();
    this->location=(Model::getInstance().findMapObjectByName(DeliveryArray[0]->getOrigin()))->getLocation();
    this->destination.reset(new Point((Model::getInstance().findMapObjectByName(DeliveryArray[0]->getDestination()))->getLocation()));
    this->statesPrint="Parked at "+ (Model::getInstance().findMapObjectByName(DeliveryArray[0]->getOrigin()))->getName();
    speedOfTruck(location,*(this->destination),*DeliveryArray[0]);
    this->direction=anglePoints(location,*(this->destination));
}

/****************************************/
Truck::Truck(const string& name,const Point& location_,const std::vector<std::shared_ptr<Delivery>>& DeliveryArray_,unsigned int sumOfAllDelivery_)
:Vehicles(name,location_),DeliveryArray(DeliveryArray_),sumOfAllDelivery(sumOfAllDelivery_)
{

}
/****************************************/
Truck& Truck::operator=(const Truck& rhs)
{
    if(this==&rhs) return *this;
    Vehicles::operator=(rhs);
    DeliveryArray.clear();
    DeliveryArray.assign(rhs.DeliveryArray.begin(),rhs.DeliveryArray.end());
    sumOfAllDelivery=rhs.sumOfAllDelivery;
    return *this;
}
/****************************************/
Truck& Truck::operator=(Truck&& rhs)
{
    if(this==&rhs) return *this;
    DeliveryArray.clear();
    DeliveryArray.assign(rhs.DeliveryArray.begin(),rhs.DeliveryArray.end());
    sumOfAllDelivery=rhs.sumOfAllDelivery;
    return *this;
}
/****************************************/
void  Truck::update()
{
    unsigned int t=Model::getInstance().getTime();
    if(t<DeliveryArray[0]->getArrivalTime().getHour() || ((t=DeliveryArray[0]->getArrivalTime().getHour())&& 0!=DeliveryArray[0]->getArrivalTime().getMinutes()))
    {
        this->moveByX();
        this->moveByY();
        this->statesPrint=" Heading to " +DeliveryArray[0]->getDestination();
        this->states=MOVINGG;
        return;
    }
    if(t>DeliveryArray[0]->getArrivalTime().getHour())
    {
        if(this->DeliveryArray.size()==1){
            Parked();
            return;
        }
        if(t>DeliveryArray[0]->getArrivalTime().getHour()&& t<DeliveryArray[1]->getArrivalTime().getHour()){
            Parked();
            return;
        }
        this->moveByX();
        this->moveByY();
        DeliveryArray.erase(DeliveryArray.begin());
        this->statesPrint=" Heading to" +DeliveryArray[0]->getDestination();
        this->states=MOVINGG;
    }
}




void Truck::Parked()
{
    speed=0;
    statesPrint="Parked at "+DeliveryArray[0]->getOrigin();
    states=PARKEDD;
    unloadingBox();
}
/****************************************/
void Truck::Attack()
{
    sumOfAllDelivery=0;
    DeliveryArray.clear();
    speed=0;
    statesPrint="Off road ";
    states=OFFROADD;
}

void Truck::print(std::ostream& out)const
{
    out<<"Truck "<<this->name<<" at "<<this->location<<" States:"<<statesPrint<<endl;
}
void Truck::Course (float angle){}
void Truck::Position(Point& locale){}
void Truck::Stop(){}


/***********************************************************************getters/setters ******************************************************************************/
unsigned int Truck::getSumOfAllDelivery() const {return sumOfAllDelivery;};

