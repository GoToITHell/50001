#ifndef RING_H
#define RING_H
#include "Shape.h"

class Ring : public Shape {
private:
    Point center;
    double outerRadius;
    double innerRadius;
public:
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    BoundingRectangle getBoundingRectangle() const override;

    Ring(Point center, double outerRadius, double innerRadius);
    ~Ring() override;
};

#endif

