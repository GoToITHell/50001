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

    while (!std::cin.eof())
    {
        std::copy(std::istream_iterator<DataStruct>(std::cin), std::istream_iterator<DataStruct>(),std::back_inserter(data));
        if (!std::cin.eof())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
