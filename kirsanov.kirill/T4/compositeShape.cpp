#include "compositeShape.h"
#include <iostream>
#include <iomanip>

// Добавление фигуры в контейнер
void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{
shapes_.push_back(std::move(shape));
}


// Суммарная площадь всех фигур
double CompositeShape::getArea() const
{
double sum = 0;

for (const auto& s : shapes_)
sum += s->getArea();

return sum;
}


// Центр составной фигуры — среднее центров
Point CompositeShape::getCenter() const
{
double sx = 0;
double sy = 0;

for (const auto& s : shapes_)
{
Point c = s->getCenter();
sx += c.x_;
sy += c.y_;
}

return Point(sx / shapes_.size(), sy / shapes_.size());
}


// Перемещение всех фигур
void CompositeShape::move(double dx, double dy)
{
for (auto& s : shapes_)
s->move(dx, dy);
}


// Масштабирование всех фигур
void CompositeShape::scale(double k)
{
for (auto& s : shapes_)
s->scale(k);
}


// Название фигуры
const char* CompositeShape::getName() const
{
return NAME;
}


// Вывод информации о составной фигуре
void CompositeShape::printInfo() const
{
std::cout << std::fixed << std::setprecision(2);

Point c = getCenter();

std::cout << "[" << getName()
<< ", (" << c.x_ << ", " << c.y_ << ")"
<< ", " << getArea() << "]\n";
}
