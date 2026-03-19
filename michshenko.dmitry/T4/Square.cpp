#include "Square.hpp"
#include <iomanip>


double Square::getArea() const {

    if (side_ < 0){
        throw std::runtime_error("incorrect side");
    }

    return side_ * side_;
}

Point Square::getCenter() const {
    return Point(bottomLeftCorner_.x_ + side_ / 2, bottomLeftCorner_.y_ + side_ / 2);
}

void Square::move(double newX, double newY) {
    bottomLeftCorner_.x_ += newX;
    bottomLeftCorner_.y_ += newY;
}

void Square::scale(double k) {
    if (k < 0) {
        throw std::runtime_error("incorrect k");
    }

    Point center = getCenter();

    side_ *= k;
    bottomLeftCorner_.x_ = center.x_ - side_ / 2;
    bottomLeftCorner_.y_ = center.y_ - side_ / 2;
}

const char* Square::getName() const {
    return "SQUARE";
}

void Square::print() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[" << getName() << ",\t("<< getCenter().x_ << ", " << getCenter().y_ << "),\t"<< getArea() << "]" << std::endl;

}
