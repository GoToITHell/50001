#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"

//Базовый класс дл явсех геометрических фигур
class Shape
{
public:
    virtual ~Shape() = default; //виртуальный деструктор

    //Вычисление площади фигуры
    virtual double getArea() const = 0;

    //Получение центра фигуры
    virtual Point getCenter() const = 0;

    //Перемещение фигуры на dx и dy
    virtual void move(double dx, double dy) = 0;

    //Масштабирование относительно центра
    virtual void scale(double k) = 0;

    //Получение названия фигуры
    virtual const char* getName() const = 0;

    //Вывод информации о фигуре
    virtual void printInfo() const = 0;
};

#endif
