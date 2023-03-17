#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

//class Shape,Point,Rectangle,Circle,Square;

class Shape
{
public:
    virtual double Area() =0;
};

class Point
{
private:
    double x,y;
public:
    Point(double,double);
    void Print();
    Point operator+(const Point&);
    Point operator-(const Point&);

friend class Rectangle;
friend class Circle;
friend class Square;
};

class Rectangle:public Shape
{
protected:
    Point start_p,end_p;
public:
    Rectangle(const Point&,const Point&);
    double Area();
};

class Circle:public Shape
{
private:
    Point o;
    double r;
public:
    Circle(const Point&,double);
    double Area();
};

class Square:public Rectangle
{
public:
    Square(const Point&,const Point&);
    double Area();
};

#endif // SHAPE_H_INCLUDED
