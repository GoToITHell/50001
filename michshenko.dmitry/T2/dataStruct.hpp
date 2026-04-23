#ifndef  DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>

#include "iofmtguard.hpp"

namespace michshenko {

    struct DataStruct
    {
        double key1;
        char key2;
        std::string key3;
    };

    struct DelimiterIO
    {
        char exp;
    };

    struct DoubleIO
    {
        double& ref;
    };

    struct CharIO
    {
        char& ref;
    };

    struct StringIO
    {
        std::string& ref;
    };

    // компоратор
    bool comparator(const DataStruct& firstStruct, const DataStruct& secondStruct);

    // перегрузки потоков
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, DoubleIO&& dest);
    std::istream& operator>>(std::istream& in, CharIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}
#endif
