#ifndef SHAPE_H
#define SHAPE_H
#include "point.h"

class Shape {
public:
    virtual ~Shape() {};
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double moveX, double moveY) = 0;
    virtual void scale(double rate) = 0;
    virtual const char* getName() const = 0;
    virtual void printInfo() const = 0;
};

#endif
