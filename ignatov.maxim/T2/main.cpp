#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <limits>
#include "DataStruct.h"

int main()
{
    using ignatov::DataStruct;

    std::vector<DataStruct> data;

    std::istream& input = std::cin;

    while (!input.eof()) {
        std::copy(
            std::istream_iterator<DataStruct>(input),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );

        if (input.fail() && !input.eof()) {
            input.clear();
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::sort(data.begin(), data.end(), ignatov::dataStructComparator);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
