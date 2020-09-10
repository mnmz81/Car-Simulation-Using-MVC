#include "MapObject.h"
#include <cctype>//for isalpha and isspace
using namespace std;

/***********************************************************************private methods ******************************************************************************/
void MapObject::checkName()
{
    auto s=name.begin();
    auto e=name.end();
    int count;
    for(count=0; s!=e && (isalpha(*s) || isspace(*s));count++,s++);
    if((s!=e) || count>12) 
        throw NameError();
 }
 /***********************************************************************public methods ******************************************************************************/
MapObject::MapObject():name("Dumbledore"),location(0,0){}//defult c'tor
/******************************************************/
MapObject::MapObject(const string &Name_,const Point &Location_):name(Name_),location(Location_)//c'tor
{
    checkName();
}
/******************************************************/
MapObject::MapObject(const MapObject &rhs):name(rhs.name),location(rhs.location){}
/******************************************************/
MapObject::MapObject(MapObject &&rhs):name(rhs.name),location(rhs.location){}
/******************************************************/
MapObject::~MapObject(){}
/******************************************************/
MapObject &MapObject::operator=(const MapObject &rhs)
{
    if(this==&rhs) return *this;
    this->name=rhs.name;
    this->location=rhs.location;
    return *this;
}
/******************************************************/
MapObject &MapObject::operator=(MapObject &&rhs){
    if(this==&rhs) return *this;
    this->name=move(rhs.name);
    this->location=move(rhs.location);
    return *this;
}
 /***********************************************************************getters/setters ******************************************************************************/
string MapObject::getName() const {return name;}
const Point& MapObject::getLocation() const { return location;}
void MapObject::setLocation(float x,float y){ setLocation(Point(x,y));}
void MapObject::setLocation(const Point& rhs) { location=rhs; }
 /***********************************************************************global ******************************************************************************/
ostream& operator<<(ostream& out,const MapObject& o)
{
    o.print(out);
    return out;
}