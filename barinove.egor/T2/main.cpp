#include "DataStruct.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <limits>

int main() {
    std::vector<DataStruct> data;
    DataStruct temp;

    while (std::cin) {
        if (std::cin >> temp) {
            data.push_back(temp);
        }
        else if (!std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }

    std::sort(data.begin(), data.end(), compare);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
