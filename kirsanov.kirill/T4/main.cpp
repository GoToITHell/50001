#include "rectangle.h"
#include "ring.h"
#include "compositeShape.h"
#include <vector>
#include <memory>
#include <iostream>


int main()
{
    std::vector<std::unique_ptr<Shape>> figures;

    // Создание составной фигуры
    auto comp = std::make_unique<CompositeShape>();

    comp->addShape(
        std::make_unique<Rectangle>(Point(1, 2), Point(5, 7))
    );

    comp->addShape(
        std::make_unique<Ring>(Point(2, 3), 5, 2)
    );

    figures.push_back(std::move(comp));

    // Добавляем отдельные фигуры
    figures.push_back(
        std::make_unique<Rectangle>(Point(0, 1), Point(4, 6))
    );

    figures.push_back(
        std::make_unique<Ring>(Point(3, 4), 6, 1)
    );

    // Вывод до масштабирования
    std::cout << "Before scale:\n";

    for (const auto& f : figures)
        f->printInfo();

    // Масштабирование в 2 раза
    for (auto& f : figures)
        f->scale(2);

    // Вывод после масштабирования
    std::cout << "\nAfter scale:\n";

    for (const auto& f : figures)
        f->printInfo();

    return 0;
}
