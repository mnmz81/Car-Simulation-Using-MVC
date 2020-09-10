#ifndef INC_3_VIEW_H
#define INC_3_VIEW_H
#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include "MapObject.h"
class View{
    private:
        unsigned int window_size;
        float map_scale;
        Point map_origin;
        std::vector<std::shared_ptr<MapObject>> map_objects;//contine all the map objects that should apper in the window base on the window_size,map_scale,map_origin
        std::vector<std::shared_ptr<MapObject>> all_Objects;
    /*Functions*/
        void subset();//get only the object in the window to map_objects
        void fixMapObjects();//fix the coordinates in map objects
    public:
        View();
        View(const View&)=default;
        View(View&&)=default;
        View& operator=(const View&)=default;
        View& operator=(View&&)=default;
        ~View()=default;
        void push(std::vector<std::shared_ptr<MapObject>>&&);//update map_objects
        void _default();//go back to default view
        void _size(unsigned int);// change the window size
        void _zoom(float);//change the scale of the map
        void _pan(const Point&);//change map origin
        void _show(std::ostream&);//show the map in the ostream
};
#endif