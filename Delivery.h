#ifndef DELIVERY_H
#define DELIVERY_H
#include "Time.h"
class Delivery{
    private:
        std::string origin;//origin of the delivery
        std::string destination;// the delivery destination
        Time departureTime;// the time the delivery left origin
        Time arrivalTime;//the time the delivery reached to destination
        unsigned int boxes;//the number of boxes in the delivery
    public:
        Delivery(std::string origin,std::string destination,const Time& departure,const Time& arrival,unsigned int Boxes);//c'tor
        ~Delivery()=default;//d'tor
        Delivery(const Delivery&)=default;//copy c'tor
        Delivery(Delivery&&)=default;//move c'tor
        Delivery& operator=(const Delivery&)=default;//operator=
        Delivery& operator=(Delivery&&)=default;//move operator=
        //getters
        const std::string& getOrigin() const;
        const std::string& getDestination() const;
        const Time& getDepartureTime() const;
        const Time& getArrivalTime() const;
        unsigned int getNumberOfBoxes() const;
};
std::ostream& operator<<(std::ostream&,const Delivery&);
#endif