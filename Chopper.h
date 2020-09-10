#ifndef INC_3_CHOPPER_H
#define INC_3_CHOPPER_H
#include <iostream>
#include "Vehicles.h"


const int maxAttackRange=20;
const int minAttackRange=2;

class Chopper:public Vehicles {
    private:
        unsigned int attackRange;
        void checkMaxSpeed(float speed);
        Point getPointFromString(std::string& temp);
    public:
        /**c'tor and d'tor*/
        Chopper();
        Chopper(std::string name,std::string& location_);
        Chopper(std::string name,Point location_);
        Chopper(const Chopper& temp);
        Chopper(Chopper&& temp);
        ~Chopper()=default;
        /*getter and setter*/
        unsigned int getAttackRange();
        virtual void setSpeed(float temp);

        /*Override operator */

        Chopper& operator=(const Chopper& rhs);
        Chopper& operator=(Chopper&& rhs);
        Chopper& operator++(); //מעלה את הטווח תקיפה ב1
        const Chopper operator++(int);///מעלה את הטווח תקיפה ב1
        Chopper& operator--(); ///מוריד את הטווח תקיפה ב1
        const Chopper operator--(int);///מוריד את הטווח תקיפה ב1
        /*Function */
        virtual void print(std::ostream& out)const; //print Chopper
        virtual void Course (float angle);
        virtual void Position(Point& locale);
        virtual void Stop();
/*exception*/
};
bool operator==(const Chopper& lhs,const Chopper& rhs);
std::ostream& operator<<(std::ostream&, const Chopper&);
#endif //INC_3_CHOPPER_H
