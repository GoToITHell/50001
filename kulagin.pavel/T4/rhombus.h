#ifndef RHOMBUS_H
#define RHOMBUS_H
#include "shape.h"
#include "point.h"

class Rhombus : public Shape
{
public:
    Rhombus(const Point& cntr, double diagX, double diagY);

    double getArea() const override;
    Point getCenter() const override;
    void move(double moveX, double moveY) override;
    void scale(double rate) override;
    const char* getName() const override;

    void printInfo() const override;

private:
    Point center;
    double diagonalX;
    double diagonalY;
    const char* FIGURE_NAME = "RHOMBUS";
};

#endif
