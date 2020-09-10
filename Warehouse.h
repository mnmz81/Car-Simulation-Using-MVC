#ifndef INC_3_WAREHOUSE_H
#define INC_3_WAREHOUSE_H


#include "MapObject.h"
#include "Delivery.h"
#include "Truck.h"

class Warehouse: public MapObject {
private:
    unsigned int crates;
public:
    /*c'tor and d'tor */
    Warehouse();
    Warehouse(const std::string& name_,const Point& loca_,unsigned int crates_);
    Warehouse(const Warehouse& rhs);
    Warehouse(Warehouse&& rhs);
    ~Warehouse();
    /*operators */
    Warehouse& operator=(const Warehouse& rhs);
    Warehouse& operator=(Warehouse&& rhs);
    /* function*/
    void print(std::ostream&)const;
    void receiveDelivery(const Delivery&);// מקבלת משלוח ומוסיפה את כמות החבילות שם
    void sendDelivery(const Truck&);//שולחת משאית לסבב פריקה ומורידה ממנה את כמות הארגים שיש לה
};


#endif //INC_3_WAREHOUSE_H
