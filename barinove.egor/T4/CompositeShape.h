#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H
#include "Shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> Shapes;
public:
    void addShape(std::unique_ptr<Shape> shape);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    void printInfo() const override;
    BoundingRectangle getBoundingRectangle() const override;

    CompositeShape();
    CompositeShape(std::unique_ptr<Shape> shape);
    ~CompositeShape() override;
};

#endif
