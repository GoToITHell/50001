#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <complex>
#include <iostream>

namespace kirsanov
{
    struct DataStruct
    {
        unsigned long long key1;
        std::complex<double> key2;
        std::string key3;
    };

    bool parseULL(const std::string& str, unsigned long long& value);
    bool parseComplex(const std::string& str, std::complex<double>& value);

    std::istream& operator>>(std::istream& in, DataStruct& data);
    std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}
#endif
