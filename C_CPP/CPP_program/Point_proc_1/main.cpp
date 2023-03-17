#include <iostream>
#include "point.h"
using namespace std;

int main(int argc,char *argv[])
{
    Point point(0,0);
    point.Print();
    return 0;
}

Point::Point(int a,int b)
{
    x=a;
    y=b;
}

void Point::Print()
{
    cout << "(" <<x<<","<<y<< ")" <<endl;
}
