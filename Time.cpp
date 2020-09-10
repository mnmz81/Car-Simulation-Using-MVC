#include "Time.h"
#include <sstream>
#include <exception>
using namespace std;
/**************************************************************** public methods *******************************************************************/
Time::Time() :hour(0),minutes(0){} //empty c'tor  00:00
/*************************************************************************************/
Time::Time(const string& time)//c'tor
{
    stringstream in(time);
    in>>hour;
    in.ignore(1,':');
    in>>minutes;
    if(!isTimeValid(*this))
        throw TimeException();
}
/*************************************************************************************/
unsigned int Time::operator-(const Time& rhs) const//calculates the difference between two Time objects -> return the difference in minuts -> if this is earlier throw an exception
{
    if(*this<rhs)
        throw TimeException();
    return (minutes - rhs.minutes)+(hour - rhs.hour)*MIN_IN_HOUR;
}
/*************************************************************************************/
unsigned int Time::getHour() const{ return hour; }
/*************************************************************************************/
unsigned int Time::getMinutes() const { return minutes; }
/**************************************************************** static methods *******************************************************************/
bool Time::isTimeValid(const Time& time)//return true if the time is valid -> the date and the hour is valid
{
    return (time.minutes<60);
}
/**************************************************************** friend methods *******************************************************************/
istream& operator>>(istream& in,Time& t)//read time object
{
    in>>t.hour;
    in.ignore(1,':');
    in>>t.minutes;
    if(!Time::isTimeValid(t))
        throw Time::TimeException();
    return in;   
}
/*************************************************************************************/
ostream& operator<<(ostream& out,const Time& t)//print time object
{
    stringstream s;
    (t.hour<10)? s<<'0'<<t.hour:s<<t.hour;
    s<<':';
    (t.minutes<10)? s<<'0'<<t.minutes:s<<t.minutes;
    return out<<s.str();
}
/*************************************************************************************/
bool operator<(const Time &lhs,const Time &rhs)//if lhs is earlier return true
{
    return (rhs>lhs);
}
/*************************************************************************************/
bool operator==(const Time &lhs,const Time &rhs)//return true if lhs==rhs
{
    return !(rhs>lhs) && !(lhs>rhs);
}
/*************************************************************************************/
bool operator>(const Time &lhs,const Time &rhs)//if rhs is earlier return true
{
    return (lhs.hour>rhs.hour || (lhs.hour==rhs.hour && lhs.minutes>rhs.minutes) );
}
/*************************************************************************************/
bool operator<=(const Time &lhs,const Time &rhs)//if lhs is earlier return true
{
    return (rhs>lhs) || (lhs==rhs);
}
/*************************************************************************************/