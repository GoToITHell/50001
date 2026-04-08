#include "dataStruct.h"
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    using bahurov::DataStruct;

    std::vector<DataStruct> data;

    // Если использовать std::copy для чтения записей из потока,
    // то некорректные записи не будут игнорироваться

    /*std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
    );*/

    // Читаем записи из потока std::cin
    while (!std::cin.eof())
    {
        DataStruct current;
        if (std::cin >> current)
        {
            data.push_back(current);
        }
        else if (!std::cin.eof() && std::cin.fail())
        {
            // Сбрасываем текущее состояние потока
            std::cin.clear();
            // Удаляем из потока максимально возможное кол-во символов до '\n'
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Сортируем записи через std::sort, используя собственный компаратор
    std::sort(data.begin(), data.end());

    // Выводим отсортированные записи в поток std::cout
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
