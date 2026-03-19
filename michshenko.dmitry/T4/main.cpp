#include <iostream>
#include <vector>
#include <memory>

#include "CompositeShape.hpp"
#include "Rectangle.hpp"
#include "Square.hpp"


int main() {

    std::vector<std::unique_ptr<Shape>> shapesVector;

    // Простые фигуры
    shapesVector.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(5, 5)));
    shapesVector.push_back(std::make_unique<Rectangle>(Point(3, 3), Point(-3, -3)));
    shapesVector.push_back(std::make_unique<Square>(Point(2, -2), 4));
    shapesVector.push_back(std::make_unique<Square>(Point(-5, 3), 3.14));

    // Составная фигура
    auto compositeShape = std::make_unique<CompositeShape>();

    compositeShape->addShape(std::make_unique<Rectangle>(Point(-1, 0), Point(4, 3)));
    compositeShape->addShape(std::make_unique<Square>(Point(0, -1), 1));
    compositeShape->addShape(std::make_unique<Square>(Point(0, 1),  5.2));

    shapesVector.push_back(std::move(compositeShape));


std::cout<<"### print before scale ###"<<std::endl;
   for (const auto& shape : shapesVector) {
        shape->print();
        std::cout <<std::endl;
    }

for (size_t i = 0; i <shapesVector.size(); i++) {
shapesVector[i]->scale(4.0);
}

std::cout<<"### print after scale ###"<<std::endl;
   for (const auto& shape : shapesVector) {
        shape->print();
        std::cout <<std::endl;
    }

    return 0;
}
