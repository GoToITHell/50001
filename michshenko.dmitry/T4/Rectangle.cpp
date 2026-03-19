#include "Rectangle.hpp"
#include <iomanip>

double Rectangle::getArea() const {
    return (topRightCorner_.x_ - bottomLeftCorner_.x_) * (topRightCorner_.y_ - bottomLeftCorner_.y_);
}


Point Rectangle::getCenter() const {
    return Point((topRightCorner_.x_ + bottomLeftCorner_.x_)/ 2, (topRightCorner_.y_ + bottomLeftCorner_.y_) / 2);
}


void Rectangle::move(double newX, double newY) {
    topRightCorner_.x_  += newX;
    topRightCorner_.y_ += newY;
    bottomLeftCorner_.x_ += newX;
    bottomLeftCorner_.y_ += newY;
}


void Rectangle::scale(double k) {

    if (k<0) {
    throw std::runtime_error("incorrect k");
    }

    Point center = getCenter();
    topRightCorner_.x_ = center.x_ + (topRightCorner_.x_ - center.x_) * k;
    topRightCorner_.y_ = center.y_ + (topRightCorner_.y_ - center.y_)* k;
    bottomLeftCorner_.x_ = center.x_ + (bottomLeftCorner_.x_ - center.x_) * k;
    bottomLeftCorner_.y_ = center.y_ + (bottomLeftCorner_.y_ - center.y_) * k;
}


const char* Rectangle::getName() const {
    return "RECTANGLE";
}

void Rectangle::print() const {

std::cout << std::fixed << std::setprecision(2);
std::cout << "[" << getName() << ",\t("<< getCenter().x_ << ", " << getCenter().y_ << "),\t"<< getArea() << "]" << std::endl;

} 
