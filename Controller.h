#ifndef INC_3_CONTROLLER_H
#define INC_3_CONTROLLER_H

#include <iostream>
#include "Point.h"
#include "FileHandlerWarehouse.h"
#include "vector"
#include "Model.h"
#include "View.h"



class Controller {
private:
/*private Functions*/
void PrintLineInTheBegin();
std::vector<std::string> getDataFromCin();

void Run();
/*Model Functions*/
void Status();
void Go();
void Create(std::vector<std::string>& temp);


/*View Functions*/
void Default();
void Size(std::string& s);
void Zoom(std::string& s);
void Pan(std::vector<std::string>& temp);
void Show();

/*Vehicles Functions*/
void Stop(std::vector<std::string>& temp);
void Attack(std::vector<std::string>& temp);
void Course(std::vector<std::string>& temp);
void Position(std::vector<std::string>& temp);
void Destination(std::vector<std::string>& temp);
public:
/**c'tor and d'tor*/
Controller();
Controller(const Controller &)=default;
Controller(Controller &&)=default;
~Controller();
/*Override operator*/
Controller &operator=(Controller &&)=default;
Controller &operator=(const Controller &)=default;
/*Functions*/
void Init(int argc, char *argv[]);
//exception//
class ErrorNumOfArgument{
    public:
        ErrorNumOfArgument() {}
        virtual void PrintError(){
            std::cout <<"Error In The Nnm of Arguments"<<std::endl;
        }
    };
class ErrorInFlagsOfArgument{
    public:
        ErrorInFlagsOfArgument() {}
        virtual void PrintError(){
            std::cout <<"Error in the flags of the arguments"<<std::endl;
        }
    };
class ErrorIllegalCommand{
    public:
        ErrorIllegalCommand() {}
        virtual void PrintError(){
            std::cout <<"Error Command are not illegal"<<std::endl;
        }
 };
 class ErrorNoInTheModel{
    public:
        ErrorNoInTheModel() {}
        virtual void PrintError(){
            std::cout <<"Error this name are not in the data base"<<std::endl;
        }
 };

};


#endif //INC_3_CONTROLLER_H
