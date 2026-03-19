#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "Shape.hpp"
#include <vector>
#include <memory>

class CompositeShape : public Shape {


    private:
    std::vector<std::unique_ptr<Shape>> shapes_; 

    public:
    
    /* КОНСТРУКТОРЫ */

    CompositeShape() = default; 
    CompositeShape(const CompositeShape& rhs) = delete;
    CompositeShape(CompositeShape&& rhs) = delete;
    CompositeShape& operator=(const CompositeShape& rhs) = delete;
    CompositeShape& operator=(CompositeShape&& rhs) = delete;
    ~CompositeShape() = default;

    /* МЕТОДЫ */

    virtual double getArea() const override;
    virtual Point getCenter() const override; 
    virtual void move(double newX, double newY) override; 
    virtual void scale(double k) override; 
    virtual const char* getName() const override; 
    virtual void print() const override; 
    void addShape(std::unique_ptr<Shape> shape); 
 
};

#endif
