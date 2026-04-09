#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"
#include "point.h"

class Rectangle : public Shape {
public:
    Rectangle(const Point& LBCorner, const Point& RTCorner);

    double getArea() const override;
    Point getCenter() const override;
    void move(double moveX, double moveY) override;
    void scale(double rate) override;
    const char* getName() const override;

    void printInfo() const override;

private:
    Point leftBottomCorner;
    Point rightTopCorner;
    const char* FIGURE_NAME = "RECTANGLE";
};

#endif
