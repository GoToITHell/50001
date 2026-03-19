#include "CompositeShape.hpp"
#include <iostream>
#include <iomanip>
#include <limits>


double CompositeShape::getArea() const {
    double sumAreas = 0;
    for (size_t i =0; i < shapes_.size(); i++) {
        sumAreas += shapes_[i]->getArea();
    }
    return sumAreas;
}

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    shapes_.push_back(std::move(shape));
}



Point CompositeShape::getCenter() const {
    if (shapes_.empty())
    {
        throw std::runtime_error("List is empty");
    }

    double MAX_DOUBLE = std::numeric_limits<double>::max(); 
    double MIN_DOUBLE = std::numeric_limits<double>::lowest(); 

    double minX = MAX_DOUBLE;
    double minY = MAX_DOUBLE;
    double maxX = MIN_DOUBLE;
    double maxY = MIN_DOUBLE;

    for (size_t i =0; i < shapes_.size(); i++) {
        Point centerShape = shapes_[i]->getCenter();

        maxX = std::max(maxX, centerShape.x_);
        minX = std::min(minX, centerShape.x_);
        maxY = std::max(maxY, centerShape.y_);
        minY = std::min(minY, centerShape.y_);

    }
    return Point((minX + maxX) / 2, (minY + maxY) / 2);
}



void CompositeShape::scale(double k) {
   if (k < 0) {
        throw std::runtime_error("incorrect k");
    }

    Point centerOfCompositeShape = getCenter();
    for (size_t i =0; i < shapes_.size(); i++) {
        Point centerOfShape = shapes_[i]->getCenter(); 
        double newX = centerOfShape.x_ - centerOfCompositeShape.x_; 
        double newY = centerOfShape.y_ - centerOfCompositeShape.y_; 
        shapes_[i]->move(newX * (k - 1), newY * (k - 1)); 
        shapes_[i]->scale(k);
    }
}



void CompositeShape::move(double newX, double newY) {
    for (size_t i =0; i < shapes_.size(); i++)
    {
        shapes_[i]->move(newX, newY);
    }
}



const char* CompositeShape::getName() const {
    return "COMPOSITE";
}



void CompositeShape::print() const {



        std::cout << std::fixed << std::setprecision(2);
        std::cout << "[" << getName() << ",\t(" << getCenter().x_ << ", " << getCenter().y_ << "),\t" << getArea() << ":" << std::endl;
        for (size_t i =0; i < shapes_.size(); i++) {
            std::cout << " ";
            shapes_[i]->print();
        }
        std::cout << "]" << std::endl;
    }
