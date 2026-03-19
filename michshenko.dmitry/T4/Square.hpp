#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <iostream>
#include "Shape.hpp"

class Square : public Shape {  

private:
    Point bottomLeftCorner_;  
    double side_;       

public:

    /* КОНСТРУКТОРЫ */
    Square(const Square& other) = delete;
    Square(Square&& other) = delete;
    Square& operator=(const Square& other) = delete;
    Square& operator=(Square&& other) = delete;

    Square(Point bottomLeftCorner, double side) : bottomLeftCorner_(bottomLeftCorner), side_(side) {}
    ~Square() = default;

    /* МЕТОЫ */
    virtual double getArea() const override;
    virtual Point getCenter() const override; 
    virtual void move(double newX, double newY) override; 
    virtual void scale(double k) override; 
    virtual const char* getName() const override; 
    virtual void print() const override; 
};

#endif
