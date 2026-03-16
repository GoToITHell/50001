#include "Rectangle.h"
#include "Point.h"

double Rectangle::getArea() const {
    return (topRight.x - bottomLeft.x) * (topRight.y - bottomLeft.y);
}
Point Rectangle::getCenter() const {
    return Point((topRight.x + bottomLeft.x) / 2, (topRight.y + bottomLeft.y) / 2);
}
void Rectangle::move(double dx, double dy) {
    topRight.x += dx;
    topRight.y += dy;
    bottomLeft.x += dx;
    bottomLeft.y += dy;
}
void Rectangle::scale(double factor) {
    Point center = getCenter();
    topRight.x = center.x + (topRight.x - center.x) * factor;
    topRight.y = center.y + (topRight.y - center.y)* factor;
    bottomLeft.x = center.x + (bottomLeft.x - center.x) * factor;
    bottomLeft.y = center.y + (bottomLeft.y - center.y) * factor;
}
std::string Rectangle::getName() const {
    return "RECTANGLE";
}


BoundingRectangle Rectangle::getBoundingRectangle() const{ return { bottomLeft, topRight }; }

Rectangle::Rectangle(Point bottomLeft, Point topRight ):bottomLeft(bottomLeft), topRight(topRight){}
Rectangle::~Rectangle() {}
