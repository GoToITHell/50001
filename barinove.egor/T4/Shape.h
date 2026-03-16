#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include "Point.h"

struct BoundingRectangle {
    Point bottomLeft;
    Point topRight;
};

class Shape {
public:
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;
    virtual BoundingRectangle getBoundingRectangle() const = 0;

    virtual void printInfo() const {
        Point center = getCenter();
        printf("[%s, (%.2f, %.2f), %.2f]",
            getName().c_str(), center.x, center.y, getArea());
    }

    virtual ~Shape() {};
};

#endif 
