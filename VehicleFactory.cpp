#include "VehicleFactory.h"
#include "Truck.h"
#include "TrooperState.h"
#include "Chopper.h"
#include "Controller.h"
#include "Model.h"
using namespace std;
/***********************************************************************private methods ******************************************************************************/
VehicleFactory::VehicleFactory(){}

VehicleFactory::~VehicleFactory(){}
/***********************************************************************public methods ******************************************************************************/
VehicleFactory& VehicleFactory::getInstance()
{
    static VehicleFactory instance;
    return instance;
}
shared_ptr<Vehicles> VehicleFactory::makeVehicle(vector<string>& arg)
{
    if(Model::getInstance().existInTheMap(arg[2]))throw Controller::ErrorIllegalCommand();
    const string type=arg[1];// the arg vector look like this [type of vehicle, arg...]
     if(type=="Truck")//the secund argument in the vector is a file name for truck the vector = ["Truck",string::file name of truck file]
        return shared_ptr<Vehicles>(new Truck(arg[1]));
    if(type=="Chopper")//the arg vector look like this ["Chopper",string::name,string::point]
        return shared_ptr<Vehicles>(new Chopper(arg[2],Point(arg[3])));
    if(type=="State_trooper")////the arg vector look like this ["Chopper",string::name,string::warehouse name
    {
        auto& warehouse=dynamic_cast<Warehouse&>( *Model::getInstance().findMapObjectByName(arg[3]));
        return shared_ptr<Vehicles>(new TrooperState(arg[2],warehouse));
    }
    return shared_ptr<Vehicles>();

}
