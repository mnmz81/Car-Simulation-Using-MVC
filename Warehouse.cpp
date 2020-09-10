#include "Warehouse.h"
using namespace std;

/***********************************************************************public methods ******************************************************************************/
Warehouse::Warehouse():crates(10000){}
/****************************************************************/
Warehouse::Warehouse(const string& name_, const Point &loca_, unsigned int crates_):MapObject(name_,loca_),crates(crates_){}
/****************************************************************/
Warehouse::Warehouse(const Warehouse &rhs):MapObject((Warehouse)rhs),crates(rhs.crates){}
/****************************************************************/
Warehouse::Warehouse(Warehouse &&rhs):MapObject((Warehouse)rhs),crates(rhs.crates){}
/****************************************************************/
Warehouse::~Warehouse(){}
/****************************************************************/
void Warehouse::print(ostream& out) const
{
    out<<"Warehouse "<<this->name<<" at position "<<location<<", Inventory: "<<this->crates<<endl;
}
/****************************************************************/
void Warehouse::receiveDelivery(const Delivery & delivery){crates+=delivery.getNumberOfBoxes();}
/****************************************************************/
void Warehouse::sendDelivery(const Truck & truck){crates-=truck.getSumOfAllDelivery();}
/***********************************************************************operators******************************************************************************/
Warehouse &Warehouse::operator=(const Warehouse &rhs) {
    if(this==&rhs) return *this;
    MapObject::operator=(rhs);
    this->crates=rhs.crates;
    return *this;
 }
/****************************************************************/
Warehouse &Warehouse::operator=(Warehouse &&rhs) {
    if(this==&rhs) return *this;
    MapObject::operator=(rhs);
    this->crates=rhs.crates;
    return *this;
 }
/****************************************************************/