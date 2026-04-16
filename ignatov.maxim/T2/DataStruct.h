#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <string>

namespace ignatov
{
    struct DataStruct
    {
        double key1 = 0.0;
        long long key2 = 0;
        std::string key3;
    };

    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
    bool dataStructComparator(const DataStruct& left, const DataStruct& right);
}

#endif/* DATA_STRUCT_H */
