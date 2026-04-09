#include "dataStruct.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

int main()
{
    using bahurov::DataStruct;

    std::vector<DataStruct> data;
    
    std::stringstream buf;
    std::string currentLine;
    while (std::getline(std::cin, currentLine))
    {
        std::istringstream iss(currentLine);
        DataStruct cur;
        if (iss >> cur)
        {
            buf << currentLine << '\n';
        }
    }

    std::copy(
        std::istream_iterator<DataStruct>(buf),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
    );

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
