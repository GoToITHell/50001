#ifndef STRUCTURES_IO_H
#define STRUCTURES_IO_H
#include <string>
#include <iostream>

namespace ignatov
{
    struct DelimiterIO
    {
        char expected;
    };

    struct DoubleIO
    {
        double& reference;
    };

    struct LongLongIO
    {
        long long& reference;
    };

    struct StringIO
    {
        std::string& reference;
    };

    struct KeyIO
    {
        std::string& reference;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, DoubleIO&& dest);
    std::istream& operator>>(std::istream& in, LongLongIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, KeyIO&& dest);
}

#endif /* STRUCTURES_IO_H */
