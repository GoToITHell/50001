#ifndef SHAPE_HPP
#define SHAPE_HPP
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "exceptions.hpp"
#include "point.h"

class Shape
{
public:
    virtual ~Shape() {}
    virtual double getArea() = 0;
    virtual Point getCenter() = 0;
    virtual bool move(double x, double y) = 0;
    virtual bool scale(size_t k) = 0;
    virtual std::string getName() = 0;
    virtual std::vector<Point> getBox() = 0; // возвращает левую нижнюю и правую верхнюю вершины прямоугольника, ограничивающего фигуру
    virtual bool print(bool forComposite) = 0; // при false просто выводит информацию фигуры,
    //при true дает информацию без скобок для составной фигуры
};

#endif
