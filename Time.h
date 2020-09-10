#ifndef TIME_H
#define TIME_H
#include <iostream>
#include <exception>
class Time{
    private:
        static const unsigned int MIN_IN_HOUR=60;
        unsigned int hour;//the hour in the day -> 24-hour clock
        unsigned int minutes;
        public:
        class TimeException : public std::exception{};
        Time();//default c'tor
        Time(const std::string&);//c'tor
        Time(const Time&)=default;//copy c'tor
        Time(Time&&)=default;//move c'tor
        Time& operator=(const Time&)=default;//operator=
        Time& operator=(Time&&)=default;//move operator=
        ~Time()=default;//d'tor
        static bool isTimeValid(const Time&);//return true if the time is valid -> the date and the hour is valid
        unsigned int operator-(const Time& rhs) const;//calculates the difference between two Time objects -> return the difference in minuts -> if rhs is earlier throw an exception
        //getters
        unsigned int getHour() const;
        unsigned int getMinutes() const;
        friend std::istream& operator>>(std::istream&,Time&);//read time object
        friend std::ostream& operator<<(std::ostream&,const Time&);//print time object
        friend bool operator<(const Time &lhs, const Time &rhs);//if lhs is earlier return true
        friend bool operator>(const Time &lhs, const Time &rhs);//if rhs is earlier return true
        friend bool operator==(const Time &lhs, const Time &rhs);//return true if lhs==rhs
        friend bool operator<=(const Time &lhs, const Time &rhs);//return true if lhs<=rhs
};
#endif