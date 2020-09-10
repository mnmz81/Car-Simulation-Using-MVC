#ifndef INC_3_POINT_H
#define INC_3_POINT_H
#include <iostream>
class Point {
    private:
        float x;
        float y;
    /*Functions*/
        float getNorma()const;
    public:
    /**c'tor and d'tor*/
        Point();
        Point(float x,float y);
        Point(const Point& temp);
        Point(Point&& temp);
        Point(const std::string& s);
        ~Point();
    /*getter and setter*/
        float getX() const;
        int getXint() const;
        float getY() const;
        int getYint() const;
        std::pair<float,float> get() const;//return both x and y
        std::pair<int,int> getInt() const;//return both x and y in int
        void setX(float);
        void setY(float);
        /*Override operator*/
        Point& operator=(const Point& rhs);
        Point& operator=(Point&& rhs);
        // friend bool operator<(const Point& lhs,const Point& rhs);
        // friend bool operator>(const Point& lhs,const Point& rhs);
        // friend bool operator!=(const Point& lhs,const Point& rh
        float operator-(const Point& p) const;
        /*Functions*/
        void moveDeltaX(float delta);//move x by delta
        void moveDeltaY(float delta);//move y by delta

};
bool operator==(const Point& lhs,const Point& rhs);
std::ostream& operator<<(std::ostream&, const Point&);
bool operator<=(const Point& lhs,const Point& rhs);//return true if lhs.x<=rhs.x && lhs.y<=rhs.y
bool operator>=(const Point& lhs,const Point& rhs);//return true if lhs.x>=rhs.x && lhs.y>=rhs.y
#endif //INC_3_POINT_H
