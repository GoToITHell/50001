#include "Ring.h"
#include "Point.h"

constexpr double PI = 3.14159265358979323846;

double Ring::getArea() const {
    return PI * (outerRadius * outerRadius - innerRadius * innerRadius);
}
Point Ring::getCenter() const {
    return center;
}
void Ring::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}
void Ring::scale(double factor) {
    outerRadius *= factor;
    innerRadius *= factor;
}
std::string Ring::getName() const {
    return "RING";
}

BoundingRectangle Ring::getBoundingRectangle() const {
    return {
        Point(center.x - outerRadius, center.y - outerRadius),
        Point(center.x + outerRadius, center.y + outerRadius)
    };
}

Ring::Ring(Point center, double outerRadius, double innerRadius):
    center(center), outerRadius(outerRadius) , innerRadius(innerRadius) {
    if (innerRadius > outerRadius) std::swap(innerRadius, outerRadius);
}
Ring::~Ring(){}
