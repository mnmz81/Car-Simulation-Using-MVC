#ifndef INC_3_MAPOBJECT_H
#define INC_3_MAPOBJECT_H
#include "Point.h"
#include <iostream>


class MapObject {
    protected:
        std::string name;
        Point location;
        /*Functions*/
        void checkName();
    public:
    /*c'tor and d'tor */
        MapObject();
        MapObject(const std::string& Name_,const Point& Location_);
        MapObject(const MapObject& rhs);
        MapObject(MapObject&& rhs);
        virtual ~MapObject()=0;
    /*operators */
        MapObject& operator=(const MapObject& rhs);
        MapObject& operator=(MapObject&& rhs);
    /*getter and setter*/
        std::string getName() const;
        const Point& getLocation() const;
        void setLocation(float x,float y);
        void setLocation(const Point& rhs);
    /*exception*/
        class NameError{
            public:
                NameError(){}
                virtual void PrintError(){std::cerr<<"ERROR:This name are illegal"<<std::endl;}
        };
    /*print */
        virtual void print(std::ostream&) const=0;
};
std::ostream& operator<<(std::ostream& out,const MapObject& o);


#endif //INC_3_MAPOBJECT_H
