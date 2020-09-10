#ifndef MODEL_H
#define MODEL_H
#include <unordered_map>
#include <map>
#include <queue>
#include "View.h"
#include "Warehouse.h"
#include "VehicleFactory.h"
class Model{
    public:
        enum COMMENDS{STATUS,CREATE,COURSE,POSITION,DESTINATION,ATTACK,STOPPED};//commends from the controller to the model
        Model(Model &&) = delete;
        Model(Model &) = delete;
        Model &operator=(Model &&) = delete;
        Model &operator=(const Model &) = delete;
        ~Model();
        static Model &getInstance();
        void addMapObjects(const std::vector<std::shared_ptr<MapObject>>&);
        unsigned int getTime() const;
        std::shared_ptr<MapObject> findMapObjectByName(std::string) const;//return a pointer to map object or null if this object dose not exist
        Warehouse& getClosestWarehouse(const Point&) const;
        bool existInTheMap(std::string) const;//receive a of an object and return true if it is in the map
        void addCommend(COMMENDS,const std::vector<std::string>& arg);//add commend to the queue, the arguments are already cheacked and confirmed 
        View& getView();
        void _go();//go over the commends queue and apply all the commends4
        void status() const;
    private:
        std::map<std::string,std::string> nameANDtype;//name and type of all the object in the map -> type{"Warehouse","Truck","Chopper","Police"}
        std::unordered_multimap<std::string,std::shared_ptr<MapObject>> mapObjects;//the string is the type of the object
        std::queue<std::pair<Model::COMMENDS,std::vector<std::string>>> commends;//commends from the controller, run them when the controller call go.
        //every item in the queue contain the type of the commend and the commend arguments if exist   
        View view;
        unsigned int time=0;
        VehicleFactory& factory;
        Model();
        bool SuccessfulAttack(const Point&) const;//return true if there is no police in 10km radius from the point
        void addToMap(const std::shared_ptr<MapObject>&);
        std::string getMapObjectType(const std::shared_ptr<MapObject>&) const;//return the string of that map objects
        std::vector<std::shared_ptr<MapObject>> copyAllMapObject();
        void updateView();
        void create(std::vector<std::string>&);//the vector look like this [name of vehicle,type of vehicle,point or warehose to start from]
        void course(const std::vector<std::string>&);//if it is a TrooperState -> arg.size()=3 (curse,name,angle) and it is a Chopper -> arg.size()=4 (curse,name,angle,speed)
        void position(const std::vector<std::string>&);
        void destination(const std::vector<std::string>& arg);
        bool attack(const std::vector<std::string>& arg);//return true if the attack succeeded
        void stopped(const std::string& arg);
        const Point& FindWarehouse(const std::string&) const;
};
#endif