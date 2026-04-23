#include <cmath>
#include <iomanip>
#include <string>
#include <limits>
#include <sstream>

#include "dataStruct.hpp"
#include "iofmtguard.hpp"

namespace michshenko {

    // оператор ввода
    std::istream& operator>> (std::istream& in, DataStruct& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        DataStruct input;

        // флаги чтения
        bool isKey1 = false;
        bool isKey2 = false;
        bool isKey3 = false;

        in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };

        while (in && !(isKey1 && isKey2 && isKey3)) {
            in >> std::ws;
            if (in.peek() == ')') {
                in >> DelimiterIO{ ')' };
                break;
            }

            std::string keyValue;
            in >> keyValue;
            if (!in) {
                break;
            };

            if (keyValue == "key1") {
                in >> DoubleIO{ input.key1 }; // double
                isKey1 = true;
            }
            else if (keyValue == "key2") {
                in >> CharIO{ input.key2 };  // char
                isKey2 = true;
            }
            else if (keyValue == "key3") {
                in >> StringIO{ input.key3 }; // string
                isKey3 = true;
            }
            else {
                in.setstate(std::ios::failbit); // error
            }

            if (!in) {
                break;
            }

            in >> DelimiterIO{ ':' };
        }

        if (isKey1 && isKey2 && isKey3) {
            dest = std::move(input);
        }
        else {
            in.setstate(std::ios::failbit);
        }

        return in;
    }

    std::string formatDoubleLit(double value) {
        std::ostringstream out;

        double intpart;

        if (std::fabs(std::modf(value, &intpart)) < std::numeric_limits<double>::epsilon()) {
            out << std::fixed << std::setprecision(1) << value;
        }
        else {
            out << std::defaultfloat << value;
        }

        return out.str();
    }

    // поток вывода
    std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }
        iofmtguard fmtguard(out);

        out << "(:key1 "<<formatDoubleLit(src.key1) << "d:";
        out << "key2 '" << src.key2 <<"':";
        out << "key3 " << '\"' << src.key3 << '\"';
        out << ":)";
        return out;
    }

    // символ разделитель
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        char c = '0';
        in >> c;
        if (in && (c != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    // перегрузка double
    std::istream& operator>>(std::istream& in, DoubleIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        iofmtguard guard(in);

        char d;
        in >> d;

        if (d  == 'd' || d == 'D')
        {
            in >> dest.ref;
        }
        else
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    // перегрузка для литерала
    std::istream& operator>>(std::istream& in, CharIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        char c = '\0';
        in >> DelimiterIO{ '\'' }  >> c >> DelimiterIO{ '\'' };

        if (in)
        {
            dest.ref = c;
        }
        return in;
    }

    // перегрузка для строки
    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    // компоратор
    bool comparator(const DataStruct& firstStruct, const DataStruct& secondStruct)
    {
        if (firstStruct.key1 != secondStruct.key1)
        {
            return firstStruct.key1 < secondStruct.key1;
        }
        if (firstStruct.key2 != secondStruct.key2)
        {
            return std::abs(firstStruct.key2) < std::abs(secondStruct.key2);
        }
        return firstStruct.key3.length() < secondStruct.key3.length();
    }

}
