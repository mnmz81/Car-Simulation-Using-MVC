
#ifndef INC_3_FileHandlerWarehouse_H
#define INC_3_FileHandlerWarehouse_H

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <istream>
#include "Warehouse.h"



/* המחלקה הזאת מקבלת קובץ טקסט ועושה מערך של מחסנים ובודק קלטים*/


class FileHandlerWarehouse {
    private:
        std::vector<std::shared_ptr<MapObject>> warehouseArray;
        /*private function*/
        Point getPoint(std::string& temp);
        unsigned int getBoxs(std::string& temp);
    public:
        //ctor and dtor//
        FileHandlerWarehouse(std::string& name);
        FileHandlerWarehouse(const FileHandlerWarehouse& temp);
        FileHandlerWarehouse(FileHandlerWarehouse&& temp);
        ~FileHandlerWarehouse();
        //getter//
        std::vector<std::shared_ptr<MapObject>> getWarehouseArray();
        //operators//
        FileHandlerWarehouse& operator=(const FileHandlerWarehouse& rhs);
        FileHandlerWarehouse& operator=(FileHandlerWarehouse&& rhs);
        //exception//
    class InputErrorWarhouse{
        public:
            InputErrorWarhouse() {}
            virtual void PrintError(){
                std::cout <<"Invalid input in Warehouse File"<<std::endl;
            }
    };
};


#endif //INC_3_FileHandlerWarehouse_H
