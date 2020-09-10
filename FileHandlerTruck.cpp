#include "FileHandlerTruck.h"

using namespace std;
/**************************************************************** private methods *******************************************************************/
void FileHandlerTruck::checkName(string& temp)
{
    auto s=temp.begin();
    auto e=temp.end();
    int count;
    for(count=0; s!=e && (isalpha(*s) || isspace(*s));count++,s++);
    if(s!=e || count>12) throw InputErrorTruck();
 }
/***************************************************/
void FileHandlerTruck::checkBoxs(string &temp)
{
    auto s=temp.begin();
    string sum;
    while (isdigit(*s))
    {
        sum+=*s;
        s++;
    }
    if(s!=temp.end()) throw InputErrorTruck();;
    if(stoi(sum)<0)  throw InputErrorTruck();;
 }
/***************************************************/
int FileHandlerTruck::getBoxs(string& temp)
{
    auto s=temp.begin();
    auto e=temp.end();
    string sum;
    while (!isdigit(*s)){ s++;}
    while (s!=e) {
        sum+=*s;
        s++;
    }
    return stoi(sum);
 }
/***************************************************/
void FileHandlerTruck::getTrackName(string& temp)
{
    int index=temp.find('.');
    trackName=temp.substr(0,index);
}
/**************************************************************** public methods *******************************************************************/
FileHandlerTruck::FileHandlerTruck(string& name):sumOfAllDelivery(0)
{
    getTrackName(name);
    ifstream input1(name);
    int counter=1;
    string origin,destination,departureTime,arrivalTime, numOfBoxs;
    if (!input1.good() || input1.eof()) throw InputErrorTruck();
    getline(input1,origin,',');
    getline(input1,departureTime);
    while(!input1.eof()){
        getline(input1,destination,',');
        getline(input1,arrivalTime,',');
        getline(input1,numOfBoxs,',');
        checkName(origin);
        checkName(destination);
        checkBoxs(numOfBoxs);
        Time departureTime1(departureTime);
        Time arrivalTime1(arrivalTime);
        shared_ptr<Delivery> newDelivery(new Delivery(origin,destination,departureTime1,arrivalTime1,getBoxs(numOfBoxs)));
        sumOfAllDelivery+=newDelivery->getNumberOfBoxes();
        this->DeliveryArray.push_back(newDelivery);
        origin=destination;
        getline(input1,departureTime);
        counter++;
    }
 }
/***************************************************/
FileHandlerTruck::FileHandlerTruck(const FileHandlerTruck &temp):trackName(temp.trackName),DeliveryArray(temp.DeliveryArray){}
/***************************************************/
FileHandlerTruck::FileHandlerTruck(FileHandlerTruck &&temp):trackName(temp.trackName),DeliveryArray(temp.DeliveryArray){}
/***************************************************/
FileHandlerTruck::~FileHandlerTruck() {}
/***************************************************/
FileHandlerTruck &FileHandlerTruck::operator=(const FileHandlerTruck &rhs)
{
    if(this==&rhs) return  *this;
    this->trackName=rhs.trackName;
    this->DeliveryArray.clear();
    this->DeliveryArray.assign(rhs.DeliveryArray.begin(),rhs.DeliveryArray.end());
    this->sumOfAllDelivery=rhs.sumOfAllDelivery;
    return *this;
 }
/***************************************************/
FileHandlerTruck &FileHandlerTruck::operator=(FileHandlerTruck &&rhs)
{
    if(this==&rhs) return  *this;
    this->trackName=rhs.trackName;
    this->DeliveryArray.clear();
    this->DeliveryArray=move(rhs.DeliveryArray);
    this->sumOfAllDelivery=rhs.sumOfAllDelivery;
    return *this;
 }
/***********************************************************************getters******************************************************************************/
vector<shared_ptr<Delivery>> FileHandlerTruck::getDeliveryArray(){ return  DeliveryArray;};
/***************************************************/
string FileHandlerTruck::getTruckName(){return trackName;};
/***************************************************/
unsigned int FileHandlerTruck::getSumOfBox(){return sumOfAllDelivery;};