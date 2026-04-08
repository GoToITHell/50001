#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "DataStruct.h"

using namespace kirsanov;

int main()
{
    std::vector<DataStruct> data;
    std::stringstream buffer; //только корректные строки
    std::string line; //временное хранение ввода

    // фильтрация корректных строк
    while (std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        DataStruct temp;
        //проверка корректности строки
        if (iss >> temp)
        {
            buffer << line << '\n';
        }
    }

    // чтение через istream_iterator
    std::copy(
        std::istream_iterator<DataStruct>(buffer),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
    );

    // сортировка
    std::sort(data.begin(), data.end(),
        [](const DataStruct& a, const DataStruct& b)
        {
            //по key1
            if (a.key1 != b.key1)
                return a.key1 < b.key1;

            //по модулю комплексного
            if (std::abs(a.key2) != std::abs(b.key2))
                return std::abs(a.key2) < std::abs(b.key2);

            //по длине строки
            return a.key3.size() < b.key3.size();
        });

    // вывод
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}



