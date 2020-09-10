#include "Vehicles.h"

using namespace std;
/***********************************************************************private methods ******************************************************************************/
void Vehicles::checkSpeed(float speed){if(speed<0) throw SpeedError();}
/***********************************************************************protected methods ******************************************************************************/
void Vehicles::moveByX(){
    if(direction<90 && direction>0)
        location.moveDeltaX((speed/100)*cosf(((direction)*M_PI)/180));
    if(direction<180 && direction>90)
        location.moveDeltaX((speed/100)*cosf(((direction)*M_PI)/180));
    if(direction<270 && direction>180)
        location.moveDeltaX((speed/100)*cosf(((direction)*M_PI)/180));
    if(direction<270 && direction>360)
        location.moveDeltaX((speed/100)*cosf(((direction)*M_PI)/180));
    }
/**************************************************************************************************/
void Vehicles::moveByY(){ 

    if(direction<=90 && direction>=0)
        location.moveDeltaY((speed/100)*sinf(((direction)*M_PI)/180));
    if(direction<=180 && direction>90)
        location.moveDeltaY((speed/100)*sinf(((direction)*M_PI)/180));
    if(direction<=270 && direction>180)
        location.moveDeltaY((speed/100)*sinf(((direction)*M_PI)/180));
    if(direction<360 && direction>270)
        location.moveDeltaY((speed/100)*sinf(((direction)*M_PI)/180));
    }
/***********************************************************************public methods ******************************************************************************/
Vehicles::Vehicles()
:MapObject(),direction(0),states(STOPPEDD),speed(0),destination()
{
    stopVehicles();
}
/**************************************************************************************************/
Vehicles::Vehicles(const std::string& name,const Point& location_)
:MapObject(name,location_),direction(0),states(STOPPEDD),speed(0),destination()
{

}
/**************************************************************************************************/
Vehicles::Vehicles(const std::string &name,const Point &location_, const Point &destination_, const float &direction_)
:MapObject(name,location_),direction(direction_),states(STOPPEDD),speed(0),destination(new Point(destination_))
{
    stopVehicles();
}
/**************************************************************************************************/
Vehicles::Vehicles(const std::string &name, const Point &location_, const float &direction_, float &speed_)
:MapObject(name,location_),direction(direction_),states(STOPPEDD),speed(speed_),destination(nullptr)
{
    checkSpeed(speed_);
}
/**************************************************************************************************/
Vehicles::Vehicles(const Vehicles &temp)
:MapObject(temp),direction(temp.direction),states(temp.states),speed(temp.speed),destination(temp.destination),statesPrint(temp.statesPrint)
{

}
/**************************************************************************************************/
Vehicles::Vehicles(Vehicles &&temp)
:MapObject(temp),direction(temp.direction),states(temp.states),speed(temp.speed),destination(temp.destination),statesPrint(temp.statesPrint)
{

}
/**************************************************************************************************/
Vehicles::~Vehicles(){}
/**************************************************************************************************/
bool operator==(const Vehicles &lhs, const Vehicles &rhs)
{
    if(lhs.getName()==rhs.getName()) return true;
    return false;
}
/**************************************************************************************************/
Vehicles &Vehicles::operator=(const Vehicles &rhs){
    if(this==&rhs)return *this;
    MapObject::operator=(rhs); 
    direction=rhs.direction;
    states=rhs.states;
    speed=rhs.speed;
    destination=rhs.destination;
    statesPrint=rhs.statesPrint;
    return *this;
}
/**************************************************************************************************/
Vehicles &Vehicles::operator=(Vehicles &&rhs) {
    if(this==&rhs)return *this;
    MapObject::operator=(rhs); 
    direction=rhs.direction;
    states=rhs.states;
    speed=rhs.speed;
    destination=rhs.destination;
    destination=std::move(rhs.destination);
    statesPrint=rhs.statesPrint;
    return *this;
}
/**************************************************************************************************/
void Vehicles::update()
{
    this->moveByX();
    this->moveByY();
}
/**************************************************************************************************/
void Vehicles::stopVehicles()
{
    statesPrint="STOPPEDD";
    states=STOPPEDD;
    speed=0;
}
/**************************************************************************************************/
void Vehicles::moveByDirectionVehicles()
{
    statesPrint="MOVINGG on course";
    states=MOVINGG;
}
/**************************************************************************************************/
void Vehicles::moveByDestinationVehicles()
{
    statesPrint="MOVINGG to on course";
    states=MOVINGG;
}
/***********************************************************************getters/setters ******************************************************************************/
STATE Vehicles::getStates() const{return states;}
/**************************************************************************************************/
void Vehicles::setStates(STATE temp) {states=temp;}
/**************************************************************************************************/
float Vehicles::getSpeed() const {return speed;}
/**************************************************************************************************/
void Vehicles::setSpeed(float temp) {speed=temp;};
/**************************************************************************************************/
float Vehicles::getDirection() const {return direction;}
/**************************************************************************************************/
void Vehicles::setDirection(float temp){direction=temp;}
/**************************************************************************************************/
const Point &Vehicles::getDestination() const {return *destination;}
/**************************************************************************************************/
void Vehicles::setDestination(const Point &temp) {destination.reset(new Point(temp));}
/**************************************************************************************************/