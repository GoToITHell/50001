#include "rectangle.h"
#include <iostream>
#include <iomanip>

Rectangle::Rectangle(const Point& LBCorner, const Point& RTCorner) :
    leftBottomCorner(LBCorner), rightTopCorner(RTCorner) {
    if (leftBottomCorner.x >= rightTopCorner.x || leftBottomCorner.y >= rightTopCorner.y) {
        throw std::invalid_argument("Incorrect corners in rectangle constructor.");
    }
}

double Rectangle::getArea() const
{
    double a = rightTopCorner.x - leftBottomCorner.x;
    double b = rightTopCorner.y - leftBottomCorner.y;
    return a * b;
}

Point Rectangle::getCenter() const
{
    double xCenter = (rightTopCorner.x + leftBottomCorner.x) / 2;
    double yCenter = (rightTopCorner.y + leftBottomCorner.y) / 2;
    return Point(xCenter, yCenter);
}

void Rectangle::move(double moveX, double moveY)
{
    leftBottomCorner.x += moveX;
    leftBottomCorner.y += moveY;
    rightTopCorner.y += moveY;
    rightTopCorner.x += moveX;
}

void Rectangle::scale(double rate)
{
    if (rate <= 0) {
        throw std::invalid_argument("Incorrect scale.");
    }
    Point cntr = getCenter();

    leftBottomCorner.x = cntr.x - rate * (cntr.x - leftBottomCorner.x);
    leftBottomCorner.y = cntr.y - rate * (cntr.y - leftBottomCorner.y);
    rightTopCorner.x = cntr.x + rate * (rightTopCorner.x - cntr.x);
    rightTopCorner.y = cntr.y + rate * (rightTopCorner.y - cntr.y);
}

const char* Rectangle::getName() const
{
    return FIGURE_NAME;
}

void Rectangle::printInfo() const
{
    Point cntr = getCenter();
    std::cout << std::setprecision(2) << std::fixed << getName()
    << ", (" << cntr.x << ", " << cntr.y << "), " << getArea();
}
