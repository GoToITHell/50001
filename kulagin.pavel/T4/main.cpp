#include "shape.h"
#include "point.h"
#include "rectangle.h"
#include "rhombus.h"
#include "compositeShape.h"
#include <iostream>

int main() {
    try {
        auto c1 = std::make_unique<CompositeShape>();
        c1->addShape(std::make_unique<Rhombus>(Point(4, 10), 5, 7));
        c1->addShape(std::make_unique<Rectangle>(Point(3, 3), Point(5, 10)));
        c1->addShape(std::make_unique<Rhombus>(Point(6, 21), 4, 4));
        c1->addShape(std::make_unique<Rectangle>(Point(6, 2), Point(8, 11)));
        c1->addShape(std::make_unique<Rhombus>(Point(10, 17), 1, 6));
        c1->printInfo();

        std::cout << std::endl;
        c1->scale(3);
        c1->printInfo();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what();
        return 1;
    }
    return 0;
}
