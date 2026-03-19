#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP


#include <iostream>
#include "Shape.hpp"


class Rectangle : public Shape {

    private:
    
    Point topRightCorner_;
    Point bottomLeftCorner_;

    public:

    /* КОНСТРУКТОРЫ */

    Rectangle(const Rectangle& other) = delete;
    Rectangle(Rectangle&& other) = delete;
    Rectangle& operator=(const Rectangle& other) = delete;
    Rectangle& operator=(Rectangle&& other) = delete;

    Rectangle(Point top, Point bottom) : topRightCorner_(top), bottomLeftCorner_(bottom) {}
    ~Rectangle() = default;

    /* МЕТОДЫ */

    virtual double getArea() const override;
    virtual Point getCenter() const override; 
    virtual void move(double newX, double newY) override; 
    virtual void scale(double k) override; 
    virtual const char* getName() const override; 
    virtual void print() const override; 


};


#endif

