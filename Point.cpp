#include "Point.h"
using namespace std;
#include <cmath>
#include <sstream>
/***********************************************************************private methods ******************************************************************************/
float Point::getNorma() const { return sqrt(x * x + y * y); }
/***********************************************************************public methods ******************************************************************************/
Point::Point() : x(0), y(0) {}
/***************************************/
Point::Point(float x_, float y_) : x(x_), y(y_) {}
/***************************************/
Point::Point(const Point &temp) : x(temp.x), y(temp.y) {}
/***************************************/
Point::Point(Point &&temp) : x(move(temp.x)), y(move(temp.y)) {}
/***************************************/
Point::~Point() {}
/***************************************/
Point::Point(const string& s):x(0),y(0){
    stringstream stream(s);
    char chars;//read '(' ',' ')'
    stream>>chars>>x;//read '(' and x
    stream>>chars>>y;// read ',' and y
}
/***************************************/
Point &Point::operator=(const Point &rhs)
{
    if (this == &rhs)
        return *this;
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}
/***************************************/
Point &Point::operator=(Point &&rhs)
{
    if (this == &rhs)
        return *this;
    this->x = move(rhs.x);
    this->y = move(rhs.y);
    return *this;
}
/***************************************/
void Point::moveDeltaX(float delta){x+=delta;}
/***************************************/
void Point::moveDeltaY(float delta){x+=delta;}
/***************************************/





/***********************************************************************getters/setters ******************************************************************************/
float Point::getX() const{ return x; }
int Point::getXint() const{ return static_cast<int>(x); }
float Point::getY() const { return y; }
int Point::getYint() const{ return static_cast<int>(y); }
pair<float, float> Point::get() const{ return pair<float,float>(x,y); } //return both x and y
pair<int, int> Point::getInt() const { return pair<int,int>(static_cast<int>(x),static_cast<int>(y));}  //return both x and y in int
void Point::setX(float x) { this->x=x; }
void Point::setY(float y) { this->y=y; }
// /***************************************/
 bool operator==(const Point& lhs,const Point& rhs){
     return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
  }
// /***************************************/
// bool operator<(const Point &lhs, const Point &rhs){
//     return lhs.getNorma()<rhs.getNorma();
//  }
// /***************************************/
// bool operator>(const Point &lhs, const Point &rhs) {
//     return lhs.getNorma()>rhs.getNorma();
//  }
// /***************************************/
// bool operator!=(const Point &lhs, const Point &rhs) {
//     return lhs.x != rhs.x || lhs.y != lhs.y;;
//  }
// /***************************************/
// bool operator<=(const Point &lhs, const Point &rhs) {
//     return lhs.getNorma()<=rhs.getNorma();;
//  }
// /***************************************/
// bool operator>=(const Point &lhs, const Point &rhs){
//     return lhs.getNorma()>=rhs.getNorma();;
//  }
// /***************************************/
float Point::operator-(const Point& p) const{
    return sqrt(pow(int(x-p.x),2)-pow(int(y-p.y),2));
}
/***********************************************************************global methods ******************************************************************************/

bool operator<=(const Point& lhs,const Point& rhs)//return true if lhs.x<=rhs.x && lhs.y<=rhs.y   
{
    return lhs.getXint()<=rhs.getXint() && lhs.getYint()<=rhs.getYint();
}
bool operator>=(const Point& lhs,const Point& rhs){//return true if lhs.x>=rhs.x && lhs.y>=rhs.y
    return lhs.getXint()>=rhs.getXint() && lhs.getYint()>=rhs.getYint();
}

ostream &operator<<(ostream &out, const Point &tmp)
{
    auto pair = tmp.get();
    return out <<"("<< pair.first <<", "<<pair.second<<")";
}

