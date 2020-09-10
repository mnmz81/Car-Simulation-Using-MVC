#ifndef VEHICLE_FACTORY_H
#define VEHICLE_FACTORY_H
#include <memory>
#include "Vehicles.h"
#include <vector>
//singeltone vehicle factory
//abstract factory
class VehicleFactory
{
    private:
        VehicleFactory();
        ~VehicleFactory();
    public:
        static VehicleFactory& getInstance();
        std::shared_ptr<Vehicles> makeVehicle(std::vector<std::string>&);
};

#endif