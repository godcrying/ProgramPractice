#include <iostream>
#include "shape.h"
using namespace std;

int main()
{
    Point a(1,1);
    Point b(2,3);
    Point c(6,6);
    Point d(2,2);

    Rectangle rec(a,b);
    Square squr(a,d);
    Circle cir(c,2);

    cout << "矩形面积为：" << rec.Area() << endl;
    cout << "正方形面积为：" << squr.Area() << endl;
    cout << "圆的面积为：" << cir.Area() << endl;

    return 0;
}
