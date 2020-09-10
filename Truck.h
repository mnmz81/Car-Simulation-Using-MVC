#ifndef INC_3_TRUCK_H
#define INC_3_TRUCK_H
#include "Vehicles.h"
#include "Delivery.h"
#include <iostream>

class Truck: public Vehicles {
private:
std::vector<std::shared_ptr<Delivery>> DeliveryArray;
unsigned int sumOfAllDelivery;
/*private function*/
void unloadingBox();
void speedOfTruck(Point& from, Point& to,Delivery& times );
float distancePoints(Point& from, Point& to);
float anglePoints(Point& from, Point& to);
public:
//ctor and dtor//
Truck();
Truck(std::string fileName);
Truck(const std::string& name,const Point& location_,const std::vector<std::shared_ptr<Delivery>>& DeliveryArray,unsigned int sumOfAllDelivery);
Truck(const Truck& rhs)=default;
Truck(Truck&& rhs)=default;
//getter//
unsigned int getSumOfAllDelivery()const;

//operators//
Truck& operator=(const Truck& rhs);
Truck& operator=(Truck&& rhs);

/*function*/
void Parked();//פונקציה שאומרת שהמשאית חנתה במחסן
void Attack();//פונקציה שאומרת שהמשאית הותקפה
virtual void update();
virtual void print(std::ostream& out)const;
virtual void Course (float angle);
virtual void Position(Point& locale);
virtual void Stop();


//exception//
class WarehouseNotInDateBase{
    public:
        WarehouseNotInDateBase() {}
        virtual void PrintError(){
            std::cout <<"Warehouse Not In the DateBase"<<std::endl;
        }
    };

};


#endif //INC_3_TRUCK_H
