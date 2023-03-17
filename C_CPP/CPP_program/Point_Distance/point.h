#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

class Point;
class Segment;

class Point
{
private:
    int x;
    int y;
public:
    Point(int,int);
    void Print();
    friend class Segment;
    Point operator+(Point&);
    Point operator-(Point&);
};

class Segment
{
private:
    Point start_point;
    Point end_point;
public:

    Segment(Point,Point);

    double GetLength();
    int Set_Start(Point P);
    int Set_End(Point P);
    static double Distance(Point a,Point b);
};
#endif // POINT_H_INCLUDED
