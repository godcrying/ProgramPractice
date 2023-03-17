#include <stdio.h>
#include <iostream>
#include <math.h>
#include "point.h"

Point::Point(int a,int b):x(a),y(b){};
Segment::Segment(Point a,Point b):start_point(a),end_point(b){};

void Point::Print()
{
    printf("(%d,%d)\n",x,y);
}

double Segment::Distance(Point a,Point b)
{
    return sqrt(pow((a.x-b.x),2)+pow((a.y-b.y),2));
}

double Segment::GetLength()
{
    return Distance(start_point,end_point);
}

//设置起始，终止点
int Segment::Set_Start(Point P)
{
    start_point=P;
    return 0;
}
int Segment::Set_End(Point P)
{
    end_point=P;
    return 0;
}

//重载运算符（+ -）
Point Point::operator+(Point& p)
{
    Point temp = *this;
    temp.x = x + p.x;
    temp.y = y + p.y;
    return  temp;
}
Point Point::operator-(Point& p)
{
    Point temp = *this;
    temp.x = x - p.x;
    temp.y = y - p.y;
    return  temp;
}
