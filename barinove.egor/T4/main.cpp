#include <iostream>
#include <memory>
#include <vector>
#include "Rectangle.h"
#include "Ring.h"
#include "CompositeShape.h"

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    // Добавляем 4 простые фигуры
    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
    shapes.push_back(std::make_unique<Ring>(Point(5, 5), 3, 1));
    shapes.push_back(std::make_unique<Rectangle>(Point(-3, -2), Point(-1, 1)));
    shapes.push_back(std::make_unique<Ring>(Point(-4, 3), 2, 0.5));

    // Создаём составную фигуру
    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point(1, 1), Point(3, 2)));
    composite->addShape(std::make_unique<Ring>(Point(2, 1.5), 1, 0.3));
    shapes.push_back(std::move(composite));

    // Вывод до масштабирования
    std::cout << "Befor scale:\n";
    for (const auto& shape : shapes) {
        shape->printInfo();
        std::cout << "\n";
    }

    for (auto& shape : shapes) {
        shape->scale(2.0);
    }

    // Вывод после масштабирования
    std::cout << '\n' << "After scale:\n";
    for (const auto& shape : shapes) {
        shape->printInfo();
        std::cout << "\n";
    }

    return 0;
}
