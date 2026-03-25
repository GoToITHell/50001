#include <iomanip>

#include "compositeShape.h"

int main()
{
    try
    {
        std::cout << std::fixed << std::setprecision(2);
        // контейнер фигур
        std::vector<std::unique_ptr<Shape>> shapes;
        for (int i = 0; i < 4; i++)
        {
            shapes.push_back(std::make_unique<Rectangle>(Point(1 - i, 3 + i), Point(15 - i, 13 - i)));
        }
        // создание и заполнение составной фигуры
        auto composite = std::make_unique<CompositeShape>();
        for (int i = 0; i < 3; i++)
        {
            composite->addShape(std::make_unique<Ring>(Point(i, 10 - i), 11 - i, 2 + i));
        }
        shapes.push_back(std::move(composite));
        // вывод фигур
        for (int i = 0; i < 5; i++)
        {
            shapes[i]->print(false);
            shapes[i]->scale(2);
        }
        // вывод фигур, увеличенных в 2 раза
        for (int i = 0; i < 5; i++)
        {
            shapes[i]->print(false);
        }
    }
    catch (const std::bad_alloc& ba)
    {
        std::cerr << ba.what() << std::endl;
        return -1;
    }
    catch (const std::invalid_argument& ia)
    {
        std::cerr << ia.what() << std::endl;
        return 1;
    }
}
