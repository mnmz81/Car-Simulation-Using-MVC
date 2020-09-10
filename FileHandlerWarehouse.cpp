#include "FileHandlerWarehouse.h"

using namespace std;


/**************************************************************** private methods *******************************************************************/
Point FileHandlerWarehouse::getPoint(string& temp)
{
    string x,y;
    auto s=temp.begin();
    auto e=temp.end();
    int index=temp.find(',');
    x=temp.substr(0,index-1);
    y=temp.substr(index+1,temp.length()-index);
    return Point(atof(x.c_str()),atof(y.c_str()));
}
/***********************************************/
unsigned int FileHandlerWarehouse::getBoxs(string& temp)
{
    auto s=temp.begin();
    auto e=temp.end();
    string sum;
    while (s!=e) {
        if(!isdigit(*s)) throw InputErrorWarhouse();
        sum+=*s;
        s++;
    }
    return stoi(sum);
 }
/**************************************************************** public methods *******************************************************************/
FileHandlerWarehouse::FileHandlerWarehouse(string& fileName)
{
    ifstream input1(fileName);
    string warehouseName,point, numOfBoxs;
    if (!input1.good() || input1.eof()) throw InputErrorWarhouse();
    while(!input1.eof()){
        getline(input1,warehouseName,',');
        getline(input1,point,')');
        getline(input1,numOfBoxs);
        point=point.substr(2,point.size()-1);
        numOfBoxs=numOfBoxs.substr(2,numOfBoxs.size()-2);
        Point p=getPoint(point);
        unsigned int boxs=getBoxs(numOfBoxs);
        shared_ptr<MapObject> newWarehose(new Warehouse(warehouseName,p,boxs));
        warehouseArray.push_back(newWarehose);
    }
    
}
/*******************************************************/
FileHandlerWarehouse::FileHandlerWarehouse(const FileHandlerWarehouse& temp):warehouseArray(temp.warehouseArray){}
/*******************************************************/
FileHandlerWarehouse::FileHandlerWarehouse(FileHandlerWarehouse&& temp):warehouseArray(temp.warehouseArray){}
/*******************************************************/
FileHandlerWarehouse::~FileHandlerWarehouse(){}
/*******************************************************/
FileHandlerWarehouse& FileHandlerWarehouse::operator=(const FileHandlerWarehouse& rhs)
{
    if(this==&rhs) return *this;
    warehouseArray=rhs.warehouseArray;
    return *this;
}
/*******************************************************/
FileHandlerWarehouse& FileHandlerWarehouse::operator=(FileHandlerWarehouse&& rhs)
{
    if(this==&rhs) return *this;
    warehouseArray.clear();
    warehouseArray=rhs.warehouseArray;
    move(rhs.warehouseArray);
    return *this;
}
/***********************************************************************getters******************************************************************************/
std::vector<std::shared_ptr<MapObject>> FileHandlerWarehouse::getWarehouseArray(){return warehouseArray;};
