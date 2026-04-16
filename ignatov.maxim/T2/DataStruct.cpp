#include <iostream>
#include <iomanip>
#include "iofmtguard.h"
#include "StructuresIO.h"
#include "DataStruct.h"

namespace ignatov
{
    bool dataStructComparator(const DataStruct& left, const DataStruct& right)
    {
        if (left.key1 != right.key1) {
            return left.key1 < right.key1;
        }
        if (left.key2 != right.key2) {
            return left.key2 < right.key2;
        }
        return left.key3.length() < right.key3.length();
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input;
        {
            using sep = DelimiterIO;
            using key = KeyIO;
            using dbl = DoubleIO;
            using ll = LongLongIO;
            using str = StringIO;
            in >> sep{ '(' };
            in >> sep{ ':' };
            std::string keyName;
            bool hasKey1 = false;
            bool hasKey2 = false;
            bool hasKey3 = false;
            while (in && (!hasKey1 || !hasKey2 || !hasKey3)) {
                in >> key{ keyName };

                if (keyName == "key1" && !hasKey1) {
                    in >> dbl{ input.key1 };
                    hasKey1 = true;
                }
                else if (keyName == "key2" && !hasKey2) {
                    in >> ll{ input.key2 };
                    hasKey2 = true;
                }
                else if (keyName == "key3" && !hasKey3) {
                    in >> str{ input.key3 };
                    hasKey3 = true;
                }
                else {
                    in.setstate(std::ios::failbit);
                }
            }

            in >> sep{ ')' };
        }
        if (in)
        {
            dest = std::move(input);
        }

        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(:";
        out << "key1 " << std::fixed << std::setprecision(1) << src.key1 << "d:";
        out << "key2 " << src.key2 << "ll:";
        out << "key3 \"" << src.key3 << "\":)";
        return out;
    }
}
