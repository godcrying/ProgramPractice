#include <iostream>
#include "shape.h"
#include <math.h>

//构造
Point::Point(double x,double y):x(x),y(y){};
Rectangle::Rectangle(const Point& a,const Point& b):start_p(a),end_p(b){};
Circle::Circle(const Point& o,double r):o(o),r(r){};
Square::Square(const Point& a,const Point& b):Rectangle(a,b){};

//方法
void Point::Print()
{
    std::cout << "(" << x << "," << y << ")" << std::endl;
}

double Rectangle::Area()
{
    return abs(start_p.x - end_p.x)*abs(start_p.y - end_p.y);
}

double Circle::Area()
{
    return M_PI*pow(r,2);
}

double Square::Area()
{
    return pow((start_p.x - end_p.x),2);
}
