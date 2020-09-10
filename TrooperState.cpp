#include "TrooperState.h"


using namespace std;


/***********************************************************************public methods ******************************************************************************/
TrooperState::TrooperState():Vehicles(){}
/**************************************************/
TrooperState::TrooperState(const std::string& name_,const Warehouse& location_):Vehicles()
{
    this->name=name_;
    this->location=location_.getLocation();
    warehouseArray.push_back(location_.getName());
}
/**************************************************/
TrooperState::TrooperState(const TrooperState& temp):Vehicles(temp),warehouseArray(temp.warehouseArray),startPoint(temp.startPoint){}
/**************************************************/
TrooperState::TrooperState(TrooperState&& temp):Vehicles(temp),warehouseArray(temp.warehouseArray),startPoint(temp.startPoint){}
/**************************************************/
TrooperState& TrooperState::operator=(const TrooperState& rhs)
{
    if(this==&rhs) return *this;
    Vehicles::operator=(rhs);
    warehouseArray=rhs.warehouseArray;
    startPoint=rhs.startPoint;
    return *this;
}
/**************************************************/
TrooperState& TrooperState::operator=(TrooperState&& rhs)
{
    if(this==&rhs) return *this;
    Vehicles::operator=(rhs);
    warehouseArray=rhs.warehouseArray;
    startPoint=rhs.startPoint;
    return *this;
}
/**************************************************/
void TrooperState::print(std::ostream& out)const{
     out<<"State_trooper "<<this->name<<" at "<<this->location<<" States:"<<statesPrint<<endl;
}
/**************************************************/
void TrooperState:: Course(float angle)
{
    this->direction=angle;
    this->moveByDirectionVehicles();
}
/**************************************************/
void TrooperState::Position(Point& locale)
{
    this->destination.reset(new Point(locale));
    this->moveByDestinationVehicles();
}
/**************************************************/
void TrooperState::Stop()
{
    this->stopVehicles();
}
/**************************************************/
void TrooperState::Destination(const string& WarehouseName)
{
    this->destination.reset(new Point( Model::getInstance().findMapObjectByName(WarehouseName)->getLocation()));
    //this->warehouseArray.push_back(Model::getInstance().findMapObjectByName(WarehouseName)->getName());
    this->statesPrint=("Moving to "+WarehouseName+" on course");
}
/***************************************************/
bool TrooperState::checkIfVisit(const Warehouse& temp)
{
    for(string t:warehouseArray){
        if(t==temp.getName()) return true;
    }
    return false;
}
/***********************************************************************getters/setters ******************************************************************************/



/***********************************************************************global methods ******************************************************************************/
bool TrooperState::operator==(const TrooperState& rhs) const {return this->getName()==rhs.getName();}