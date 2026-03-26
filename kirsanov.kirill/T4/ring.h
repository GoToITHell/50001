#ifndef RING_H
#define RING_H

#include "shape.h"

class Ring : public Shape
{
public:
    // Конструктор с параметрами
    Ring(const Point& c, double outerR, double innerR);

    // Площадь кольца
    double getArea() const override;

    // Центр кольца
    Point getCenter() const override;

    // Перемещение
    void move(double dx, double dy) override;

    // Масштабирование радиусов
    void scale(double k) override;

    // Название фигуры
    const char* getName() const override;

    // Вывод информации
    void printInfo() const override;

private:
    Point center_; // центр кольца
    double outerR_; // внешний радиус
    double innerR_; // внутренний радиус

    static constexpr const char* NAME = "RING";
};

#endif
