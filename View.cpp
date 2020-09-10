#include "View.h"
#include <algorithm>
#include <iomanip>
using namespace std;
 /***********************************************************************private methods ******************************************************************************/

void View::subset()//get only the object in the window to map_objects
{
    //max point = int(origin + size* scale -scale)
    int plusToOrigin=(map_scale*window_size) - map_scale;//the number to add origin x and y
    Point maxPoint(map_origin.getXint()+plusToOrigin,map_origin.getYint()+plusToOrigin);
    for(auto it:all_Objects)
    {
        if(it->getLocation()>=map_origin && it->getLocation()<=maxPoint)
            map_objects.push_back(it);
    }
}
void View::fixMapObjects()//fix the coordinates in map objects
{
    int scale=map_scale;
    for_each(map_objects.begin(),map_objects.end(),[&scale](const std::shared_ptr<MapObject>& a){
        auto pair=a->getLocation().getInt();
        pair.first+=(pair.first <0)?((-1)*pair.first)%scale:-(pair.first%scale);
        pair.second+=(pair.second <0)?((-1)*pair.second)%scale:-(pair.second%scale);
        a->setLocation(Point(pair.first,pair.second));
    });
}
    
/***********************************************************************public methods ******************************************************************************/
View::View():window_size(25),map_scale(2),map_origin(-10,-10),map_objects(),all_Objects(){}

void View::push(vector<shared_ptr<MapObject>>&& vec){//update map_objects    
    all_Objects.clear();
    all_Objects=vec;
}
void View::_default(){//go back to default view
    window_size=25; map_scale=2;map_origin=Point(-10,-10);
}
void View::_size(unsigned int size)// change the window size
{
    window_size=size;
}
void View::_zoom(float z)//change the scale of the map
{
    map_scale=z;
}
void View::_pan(const Point& p)//change map origin
{
    map_origin=p;
}
void View::_show(std::ostream& out)//show the map in the ostream
{
    //_pan(Point(0,0));
    map_objects.clear();
    subset();
    fixMapObjects();
    sort(map_objects.begin(),map_objects.end(),[](const std::shared_ptr<MapObject>& a,const std::shared_ptr<MapObject>& b){ return a->getLocation().getXint()<b->getLocation().getXint();});
    stable_sort(map_objects.begin(),map_objects.end(),[](const std::shared_ptr<MapObject>& a,const std::shared_ptr<MapObject>& b){ return a->getLocation().getYint()>b->getLocation().getYint();});
    auto end=unique(map_objects.begin(),map_objects.end(),[](const std::shared_ptr<MapObject>& a,const std::shared_ptr<MapObject>& b){return a->getLocation().getXint()==b->getLocation().getXint() && a->getLocation().getYint()==b->getLocation().getYint();});
    map_objects.resize(distance(map_objects.begin(),end));
    auto it=map_objects.begin();
    int maxY=map_origin.getY()+(map_scale*window_size) - map_scale,maxX=map_origin.getX()+(map_scale*window_size) - map_scale;
    for(int y=maxY,line=0;y>=map_origin.getY();y-=map_scale,line++){
        (!(line%3))? out<<setw(4)<<y<<" " : out<<setw(5)<<" ";//print the line number or space
        for(int x=map_origin.getX();x<=maxX;x+=map_scale){
            if((it!=map_objects.end()) && ((*it)->getLocation()==Point(x,y))){//if there is any object in this point
               out<<(*it)->getName().substr(0,2);
                it++;
            }
            else
                out<<". ";
        }
        out<<endl;
    }
    for(int i=map_origin.getX(),num=0;i<=maxX;i+=map_scale,num++)
        if(num%3==0)
            out<<setw(6)<<i;
    out<<endl;
}