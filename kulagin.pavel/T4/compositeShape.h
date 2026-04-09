#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H
#include "shape.h"
#include "point.h"
#include <vector>
#include <memory>

class CompositeShape : Shape
{
public:
    CompositeShape() {};
    CompositeShape(std::unique_ptr<Shape> shape);
    void addShape(std::unique_ptr<Shape> shape);

    double getArea() const override;
    Point getCenter() const override;
    void move(double moveX, double moveY) override;
    void scale(double rate) override;
    const char* getName() const override;

    void printInfo() const override;
private:
    std::vector<std::unique_ptr<Shape>> shapes;
    const char* FIGURE_NAME = "COMPOSITE";
};

#endif
