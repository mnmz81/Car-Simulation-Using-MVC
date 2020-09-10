#include "Chopper.h"

using namespace std;
/***********************************************************************private methods ******************************************************************************/
Point Chopper::getPointFromString(std::string& temp)
{

    string x,y;
    auto b=temp.begin();
    auto e=temp.end();
    while (b!=e && !isdigit(*b)){b++;}
    while ((b!=e && isdigit(*b)) || *b=='.'){x=*b;b++;}
    if(*b!=',') throw "error input";
    while ((b!=e && isdigit(*b)) || *b=='.'){y=*b;b++;}
    if(*b!=')') throw "error input";
    cout <<x<<" "<<y;
    return Point(stoi(x),stoi(y));
}


/***********************************************************************public methods ******************************************************************************/
Chopper::Chopper():attackRange(minAttackRange){}
/**************************************************/
Chopper::Chopper(std::string name,std::string& location_):Vehicles(name,getPointFromString(location_)),attackRange(minAttackRange){this->Stop();}
/**************************************************/
Chopper::Chopper(std::string name,Point location_):Vehicles(name,location_),attackRange(minAttackRange){this->Stop();}
/**************************************************/
Chopper::Chopper(const Chopper& temp):Vehicles(temp),attackRange(minAttackRange){}
/**************************************************/
Chopper::Chopper(Chopper&& temp):Vehicles(temp),attackRange(minAttackRange){}
/**************************************************/
Chopper& Chopper::operator=(const Chopper& rhs)
{
    if(this==&rhs) return *this;
    Vehicles::operator=(rhs);
    attackRange=rhs.attackRange;
    return *this;
    
}
/**************************************************/
Chopper& Chopper::operator=(Chopper&& rhs)
{
    if(this==&rhs) return *this;
    Vehicles::operator=(rhs);
    attackRange=rhs.attackRange;
    return *this;
}
/**************************************************/
Chopper& Chopper::operator++()
{
    if(attackRange==maxAttackRange) return *this;
    this->attackRange++;
    return *this;
}
/**************************************************/
const Chopper Chopper::operator++(int)
{
    if(attackRange==maxAttackRange) return *this;
    Chopper temp = *this;
    this->attackRange++;
    return temp;
}
/**************************************************/
Chopper& Chopper::operator--()
{
    if(attackRange==minAttackRange) return *this;
    this->attackRange--;
    return *this;
}
/**************************************************/
const Chopper Chopper::operator--(int)
{
    if(attackRange==minAttackRange) return *this;
    Chopper temp = *this;
    this->attackRange--;
    return temp;
}
/**************************************************/
void Chopper::print(std::ostream& out)const{
     out<<"Chopper "<<this->name<<" at "<<this->location<<", States:"<<statesPrint<<endl;
}
/**************************************************/
void Chopper::Course(float angle_)
{
    this->direction=angle_;
    this->moveByDirectionVehicles();
}
/**************************************************/
void Chopper::setSpeed(float temp){
    if(temp>170 || temp<1) throw SpeedError();  
    this->speed=temp; 
}
/**************************************************/
void Chopper::Position(Point& locale)
{
    this->destination.reset(new Point(locale));
    this->moveByDestinationVehicles();
}
/**************************************************/
void Chopper::Stop()
{
    this->stopVehicles();
}
/***********************************************************************getters/setters ******************************************************************************/
unsigned int Chopper::getAttackRange(){return attackRange;}
/***********************************************************************global methods ******************************************************************************/
bool operator==(const Chopper& lhs,const Chopper& rhs){return lhs.getName()==rhs.getName();}
/**************************************************/
ostream& operator<<(ostream& out , const Chopper& temp)
{
    temp.print(out);
    return out;
}
/**************************************************/