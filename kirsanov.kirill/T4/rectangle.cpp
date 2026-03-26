#include "rectangle.h"
#include <iostream>
#include <iomanip>

// Конструктор
Rectangle::Rectangle(const Point& lb, const Point& rt)
    : lb_(lb), rt_(rt) {
}


// Площадь
double Rectangle::getArea() const
{
    return (rt_.x_ - lb_.x_) * (rt_.y_ - lb_.y_);
}


// Центр — середина диагонали
Point Rectangle::getCenter() const
{
    return Point(
        (lb_.x_ + rt_.x_) / 2,
        (lb_.y_ + rt_.y_) / 2
    );
}


// Перемещение — сдвигаем обе вершины
void Rectangle::move(double dx, double dy)
{
    lb_.x_ += dx;
    lb_.y_ += dy;
    rt_.x_ += dx;
    rt_.y_ += dy;
}


// Масштабирование относительно центра
void Rectangle::scale(double k)
{
    Point c = getCenter();

    lb_.x_ = c.x_ - (c.x_ - lb_.x_) * k;
    lb_.y_ = c.y_ - (c.y_ - lb_.y_) * k;
    rt_.x_ = c.x_ + (rt_.x_ - c.x_) * k;
    rt_.y_ = c.y_ + (rt_.y_ - c.y_) * k;
}


// Название фигуры
const char* Rectangle::getName() const
{
    return NAME;
}


// Вывод информации о прямоугольнике
void Rectangle::printInfo() const
{
    std::cout << std::fixed << std::setprecision(2);

    Point c = getCenter();

    std::cout << "[" << getName()
        << ", (" << c.x_ << ", " << c.y_ << ")"
        << ", " << getArea() << "]\n";
}
