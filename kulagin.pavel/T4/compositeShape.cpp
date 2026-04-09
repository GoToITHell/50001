#include "compositeShape.h"
#include "point.h"
#include <vector>
#include <memory>
#include <limits>
#include <iostream>
#include <iomanip>

CompositeShape::CompositeShape(std::unique_ptr<Shape> shape)
{
    shapes.push_back(std::move(shape));
}

void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{
    shapes.push_back(std::move(shape));
}

const char* CompositeShape::getName() const
{
    return FIGURE_NAME;
}

double CompositeShape::getArea() const
{
    double S = 0;
    for (size_t i = 0; i < shapes.size(); i++) {
        S += shapes[i]->getArea();
    }
    return S;
}

void CompositeShape::move(double moveX, double moveY)
{
    for (size_t i = 0; i < shapes.size(); i++) {
        shapes[i]->move(moveX, moveY);
    }
}

Point CompositeShape::getCenter() const
{
    if (shapes.empty()) {
        throw "Composite shape is empty.";
    }
    double maxX = std::numeric_limits<double>::min();
    double maxY = maxX;
    double minX = std::numeric_limits<double>::max();
    double minY = minX;
    for (size_t i = 0; i < shapes.size(); i++) {
        Point cntr = shapes[i]->getCenter();
        maxX = std::max(maxX, cntr.x);
        maxY = std::max(maxY, cntr.y);
        minX = std::min(minX, cntr.x);
        minY = std::min(minY, cntr.y);
    }
    return Point((maxX + minX) / 2.0, (maxY + minY) / 2.0);
}

void CompositeShape::scale(double rate)
{
    if (rate <= 0) {
        throw "Incorrect scale.";
    }
    Point cntr = getCenter();
    for (size_t i = 0; i < shapes.size(); i++) {
        Point shapeCntr = shapes[i]->getCenter();
        double moveX = (shapeCntr.x - cntr.x) * (rate - 1);
        double moveY = (shapeCntr.y - cntr.y) * (rate - 1);
        shapes[i]->move(moveX, moveY);
        shapes[i]->scale(rate);
    }
}

void CompositeShape::printInfo() const
{
    Point cntr = getCenter();
    std::cout << std::setprecision(2) << std::fixed << "[" << getName()
        << ", (" << cntr.x << ", " << cntr.y << "), " << getArea() << ":";
    for (size_t i = 0; i < shapes.size(); i++) {
        std::cout << "\n  ";
        shapes[i]->printInfo();
    }
    std::cout << "\n]" << std::endl;
}
