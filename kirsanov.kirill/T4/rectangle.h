#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"


class Rectangle:public Shape
{
public:
//Конструктор с параметрами
Rectangle(const Point &lb,const Point &rt);

//Площадь прямоугольника
double getArea() const override;

//Центр—пересечение диагоналей
Point getCenter() const override;

//Перемещение фигуры
void move(double dx,double dy) override;

//Масштабирование относительно центра
void scale(double k) override;

//Название фигуры
const char* getName() const override;

//Вывод информации
void printInfo() const override;

private:
Point lb_;//левый нижний угол
Point rt_;//правый верхний угол

static constexpr const char* NAME="RECTANGLE";
};

#endif
