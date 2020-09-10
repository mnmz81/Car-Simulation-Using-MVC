#ifndef INC_3_TROOPERSTATE_H
#define INC_3_TROOPERSTATE_H
#include "Vehicles.h"
#include "Warehouse.h"
#include "Point.h"
#include "iostream"
#include <vector>
#include "Model.h"

class Warehouse;

class TrooperState:public Vehicles {
private:
        std::vector<std::string> warehouseArray;//list of Warehouse that police visit
        Point startPoint;
        const float maxSpeed=90;
public:
/**c'tor and d'tor*/
TrooperState();
TrooperState(const std::string& name,const Warehouse& location_);
TrooperState(const TrooperState& temp);
TrooperState(TrooperState&& temp);
~TrooperState()=default;
/*getter and setter*/


/*Override operator */
friend std::ostream& operator<<(std::ostream&, const TrooperState&);
TrooperState& operator=(const TrooperState& rhs);
TrooperState& operator=(TrooperState&& rhs);
bool operator==(const TrooperState& rhs) const;
/*Function */
virtual void print(std::ostream& out)const;
virtual bool checkIfVisit(const Warehouse& name);
virtual void Course (float angle);
virtual void Position(Point& locale);
virtual void Stop();
virtual void Destination(const std::string& WarehouseName);
/*exception*/

};
#endif //INC_3_TROOPERSTATE_H
