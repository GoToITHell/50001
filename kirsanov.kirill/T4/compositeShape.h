#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "shape.h"
#include <vector>
#include <memory>


class CompositeShape :public Shape
{
public:
    //Добавление фигуры
    void addShape(std::unique_ptr<Shape>shape);

    //Суммарная площадь
    double getArea() const override;

    //Центр составной фигуры
    Point getCenter() const override;

    //Перемещение всех фигур
    void move(double dx, double dy) override;

    //Масштабирование всех фигур
    void scale(double k) override;

    //Название
    const char* getName() const override;

    //Выводинформации
    void printInfo() const override;

private:
    std::vector<std::unique_ptr<Shape>>shapes_;

    static constexpr const char* NAME = "COMPOSITE";
};

#endif
