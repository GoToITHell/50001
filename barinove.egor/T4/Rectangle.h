#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"

class Rectangle : public Shape {
private:
    Point bottomLeft;
    Point topRight;
public:
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    BoundingRectangle getBoundingRectangle() const override;

    Rectangle(Point bottomLeft, Point topRight);
    ~Rectangle() override;
};

#endif
