#include <stdio.h>
#include <iostream>
#include "point.h"

using namespace std;

int main()
{
    Point a(1,1);
    Point b(2,3);
    Point c(0,0);

    Segment seg(a,b);

    double dis = Segment::Distance(a,b);

    Segment seg_a = seg;
    seg_a.Set_Start(c);

    double seg_len = seg.GetLength();
    double seg_a_len = seg_a.GetLength();
    printf("两点的距离为：%lf\n线段seg长度为：%lf\n",dis,seg_len);
    printf("线段seg_a长度为：%lf\n",seg_a_len);
    printf("a(1,1) b(2,3)两点之和： ");
    (a+b).Print();
    printf("a(1,1) b(2,3)两点之差： ");
    (a-b).Print();
    return 0;
}
