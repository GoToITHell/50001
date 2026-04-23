#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>

#include "dataStruct.hpp"
#include "iofmtguard.hpp"

int main() {

    using michshenko::DataStruct;
    using michshenko::comparator;

    std::vector<DataStruct> data;
    DataStruct temp;

    while (std::cin) {
        if (std::cin >> temp)
        {
            data.push_back(temp);
        }
        else if (!std::cin.eof())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            break;
        }
    }

    std::sort(data.begin(), data.end(), comparator);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
