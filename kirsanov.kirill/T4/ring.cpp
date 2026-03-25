#include "ring.h"

#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>

// Конструктор кольца
Ring::Ring(const Point& center, double outerR, double innerR)
: center_(center), outerR_(outerR), innerR_(innerR)
{
// Проверка корректности радиусов
if (outerR <= 0 || innerR <= 0 || innerR >= outerR)
{
throw std::invalid_argument("Incorrect ring radii");
}
}

// Площадь кольца
double Ring::getArea() const
{
const double PI = 3.141592653589793;
return PI * (outerR_ * outerR_ - innerR_ * innerR_);
}

// Центр кольца
Point Ring::getCenter() const
{
return center_;
}

// Перемещение
void Ring::move(double dx, double dy)
{
center_.x_ += dx;
center_.y_ += dy;
}

// Масштабирование
void Ring::scale(double k)
{
if (k <= 0)
{
throw std::invalid_argument("Incorrect scale");
}

outerR_ *= k;
innerR_ *= k;
}

// Имя фигуры
const char* Ring::getName() const
{
return "RING";
}

// Вывод информации
void Ring::printInfo() const
{
std::cout << std::fixed << std::setprecision(2);

std::cout << "[" << getName()
<< ", (" << center_.x_ << ", " << center_.y_ << ")"
<< ", " << getArea()
<< "]" << std::endl;
}
