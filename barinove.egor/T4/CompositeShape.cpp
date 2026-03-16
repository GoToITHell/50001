#include "CompositeShape.h"
#include <limits>

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    Shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double result = 0;
    for (size_t i = 0; i < Shapes.size(); i++) {
        result += Shapes[i]->getArea();
    }
    return result;
}

Point CompositeShape::getCenter() const {
    BoundingRectangle boundingRectangle = getBoundingRectangle();
    return Point((boundingRectangle.bottomLeft.x + boundingRectangle.topRight.x) / 2,
        (boundingRectangle.bottomLeft.y + boundingRectangle.topRight.y) / 2);
}

void CompositeShape::move(double dx, double dy) {
    for (size_t i = 0; i < Shapes.size(); i++) {
        Shapes[i]->move(dx,dy);
    }
}

void CompositeShape::scale(double factor) {
    Point compositeCenter = getCenter();
    for (size_t i = 0; i < Shapes.size(); i++) {
        Point shapeCenter = Shapes[i]->getCenter();
        double dx = (shapeCenter.x - compositeCenter.x) * (factor - 1);
        double dy = (shapeCenter.y - compositeCenter.y) * (factor - 1);
        Shapes[i]->move(dx,dy);
        Shapes[i]->scale(factor);
    }
}

void CompositeShape::printInfo() const {
    Point center = getCenter();
    printf("[COMPOSITE, (%.2f, %.2f), %.2f:\n", center.x, center.y, getArea());

    for (size_t i = 0; i < Shapes.size(); i++) {
        printf("  ");

        Point shapeCenter = Shapes[i]->getCenter();
        printf("%s, (%.2f, %.2f), %.2f",
            Shapes[i]->getName().c_str(),
            shapeCenter.x, shapeCenter.y,
            Shapes[i]->getArea());

        if (i < Shapes.size() - 1) {
            printf(",\n");
        }
        else {
            printf("\n");
        }
    }

    printf("]");
}

BoundingRectangle CompositeShape::getBoundingRectangle() const {
    if (Shapes.empty()) {
        return { Point(0, 0), Point(0, 0) };
    }

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();

    for (const auto& shape : Shapes) {
        BoundingRectangle box = shape->getBoundingRectangle();

        minX = std::min(minX, box.bottomLeft.x);
        minY = std::min(minY, box.bottomLeft.y);
        maxX = std::max(maxX, box.topRight.x);
        maxY = std::max(maxY, box.topRight.y);
    }

    return { Point(minX, minY), Point(maxX, maxY) };
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

CompositeShape::CompositeShape(): Shapes() {}
CompositeShape::CompositeShape(std::unique_ptr<Shape> shape) {
    if (shape) {
        Shapes.push_back(std::move(shape));
    }
}
CompositeShape::~CompositeShape() {}
