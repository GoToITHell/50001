#ifndef SHAPE_H
#define SHAPE_H

#include "point.hpp"

class Shape {

public:

// Деструктор
virtual ~Shape() = default; 

/* Виртуальные методы */
virtual double getArea() const = 0;
virtual Point getCenter() const = 0; 
virtual void move(double newX, double newY) = 0; 
virtual void scale(double k) = 0; 
virtual const char* getName() const = 0; 
virtual void print() const = 0; 

};

#endif

