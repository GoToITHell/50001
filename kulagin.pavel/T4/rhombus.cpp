#include "rhombus.h"
#include <iostream>
#include <iomanip>

Rhombus::Rhombus(const Point& cntr, double diagX, double diagY) :
    center(cntr), diagonalX(diagX), diagonalY(diagY) {
    if (diagX <= 0 || diagY <= 0) {
        throw std::invalid_argument("Incorrect diagonals in rhombus constructor.");
    }
}

double Rhombus::getArea() const
{
    double S = (diagonalX * diagonalY) / 2.0;
    return S;
}

Point Rhombus::getCenter() const
{
    return center;
}

void Rhombus::move(double moveX, double moveY)
{
    center.x += moveX;
    center.y += moveY;
}

void Rhombus::scale(double rate)
{
    if (rate <= 0) {
        throw std::invalid_argument("Incorrect scale.");
    }
    diagonalX *= rate;
    diagonalY *= rate;
}

const char* Rhombus::getName() const
{
    return FIGURE_NAME;
}

void Rhombus::printInfo() const
{
    Point cntr = getCenter();
    std::cout << std::setprecision(2) << std::fixed << getName()
    << ", (" << cntr.x << ", " << cntr.y << "), " << getArea();
}
