#include <iostream>
#include "Controller.h"

using namespace std;

int main(int argc, char *argv[]) {
    try{
        Controller c;
        c.Init(argc,argv);
    }
    catch(exception& e){
        cout<<"FINISH"<<endl;
    }
    
    return 0;
}