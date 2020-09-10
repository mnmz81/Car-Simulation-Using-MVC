#ifndef INC_3_VEHICLES_H
#define INC_3_VEHICLES_H
#include <iostream>
#include <vector>
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include "MapObject.h"
#include "Point.h"

enum STATE{STOPPEDD,MOVINGG,PARKEDD,OFFROADD};

class Vehicles:public MapObject {
private:
    void checkSpeed(float speed);
protected:
    float direction;// direction the Vehicles move to
    STATE states;//states of the Vehicles
    float speed;//speed of the Vehicles
    std::shared_ptr<Point> destination;//destination point the the Vehicles move to
    std::string statesPrint;
    void moveByX(); //move X Cordinta 
    void moveByY();//move Y Cordinta 
public:
    /**c'tor and d'tor*/
    Vehicles();
    Vehicles(const std::string& name,const Point& location_);
    Vehicles(const std::string& name,const Point& location_,const Point& destination_,const float& direction_);
    Vehicles(const std::string& name,const Point& location_,const float& direction_,float& speed_);
    Vehicles(const Vehicles& temp);
    Vehicles(Vehicles&& temp);
    virtual ~Vehicles()=0;
    /*getter and setter*/
    STATE getStates() const;
    void setStates(STATE temp);
    float getSpeed()const;
    virtual void setSpeed(float temp);
    float getDirection() const;
    void setDirection(float temp);
    const Point& getDestination() const;
    void setDestination(const Point& temp);
    /*Override operator */
    friend bool operator==(const Vehicles& lhs,const Vehicles& rhs);
    Vehicles& operator=(const Vehicles& rhs);
    Vehicles& operator=(Vehicles&& rhs);
    /*Function */
    virtual void print(std::ostream& out)const=0;
    virtual void update();//מוזיז את הרכב
    virtual void stopVehicles();//משנה את הסטטוסים
    virtual void moveByDirectionVehicles();//משנה את הסטטוסים
    virtual void moveByDestinationVehicles();//משנה את הסטטוסים
    virtual void Course (float angle)=0;
    virtual void Position(Point& locale)=0;
    virtual void Stop()=0;
    /*exception*/
        class SpeedError{
            public:
                SpeedError(){}
                virtual void PrintError(){std::cerr<<"ERROR:This speed are illegal"<<std::endl;}
        };
};
#endif //INC_3_VEHICLES_H
