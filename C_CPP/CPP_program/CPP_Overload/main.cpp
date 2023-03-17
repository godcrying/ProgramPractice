#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

double Area(double length,double width){
    //矩形面积
    return length*width;
}
double Area(double R)
{
    //圆面积
    return 3.14*pow(R,2);
}
double Area(double above,double below,double height)
{
    //梯形面积
    return (above+below)*height/2.0;
}

int main()
{
    printf("长方形6*5的面积为：%f\n",Area(6,5));
    printf("半径为3的圆的面积为：%f\n",Area(3));
    printf("梯形面积为：%f\n",Area(3,5,2));
    return 0;
}
