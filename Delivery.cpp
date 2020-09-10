#include "Delivery.h"
using namespace std;
/**************************************************************** public methods *******************************************************************/
Delivery::Delivery(std::string origin,std::string destination,const Time& departure,const Time& arrival,unsigned int Boxes) 
:origin(origin),destination(destination),departureTime(departure),arrivalTime(arrival),boxes(Boxes){}//c'tor

/**************************************************************** getters *******************************************************************/
const string& Delivery::getOrigin() const{return origin;}
/*************************************************************************************/
const string& Delivery::getDestination() const{ return destination; }
/*************************************************************************************/
const Time& Delivery::getDepartureTime() const{ return departureTime;}
/*************************************************************************************/
const Time& Delivery::getArrivalTime() const { return arrivalTime; }
/*************************************************************************************/
unsigned int Delivery::getNumberOfBoxes() const { return boxes;}
/**************************************************************** global *******************************************************************/
ostream& operator<<(ostream& o,const Delivery& d)
{
    return o<<d.getArrivalTime()<<", "<<d.getNumberOfBoxes();
}
/*************************************************************************************/