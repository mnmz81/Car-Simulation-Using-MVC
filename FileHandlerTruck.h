#ifndef CLION_FileHandlerTruck_H
#define CLION_FileHandlerTruck_H

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "Delivery.h"
#include "Point.h"



//this class open a file and get all the arguments os Truck
//this class also check input of file
class FileHandlerTruck {
private:
    std::string trackName;
    std::vector<std::shared_ptr<Delivery>> DeliveryArray;
    unsigned int sumOfAllDelivery;
    Point firstLoca; //אומר איפה המשאית מתחילה
    /*private function*/
    void checkBoxs(std::string& temp);
    void checkName(std::string& temp);
    int getBoxs(std::string& temp);
    void getTrackName(std::string& temp);
public:
    //ctor and dtor//
    FileHandlerTruck(std::string& name);
    FileHandlerTruck(const FileHandlerTruck& temp);
    FileHandlerTruck(FileHandlerTruck&& temp);
    ~FileHandlerTruck();
    //getter//
    std::string getTruckName();
    std::vector<std::shared_ptr<Delivery>> getDeliveryArray();
    unsigned getSumOfBox();
    //operators//
    FileHandlerTruck& operator=(const FileHandlerTruck& rhs);
    FileHandlerTruck& operator=(FileHandlerTruck&& rhs);
    //exception//
    class InputErrorTruck{
    public:
        InputErrorTruck() {}
        virtual void PrintError(){
            std::cout <<"Invalid input in Truck File"<<std::endl;
        }
    };

};


#endif //CLION_FileHandlerTruck_H
