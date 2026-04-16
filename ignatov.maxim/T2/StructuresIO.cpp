#include <iomanip>
#include <cstring>
#include "StructuresIO.h"
#include "iofmtguard.h"

namespace ignatov
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (c != dest.expected))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DoubleIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        std::string number;
        std::getline(in, number, ':');

        bool hasNumBeforeDot = false;
        bool hasDot = false;
        bool hasNumAfterDot = false;
        for (char c : number)
        {
            if (!hasDot && isdigit(c)) {
                hasNumBeforeDot = true;
            }
            if (c == '.')
            {
                hasDot = true;
            }
            if (hasDot && isdigit(c)) {
                hasNumAfterDot = true;
                break;
            }
        }

        bool isValidNumber = hasNumAfterDot && hasDot && hasNumAfterDot;
        if (!isValidNumber)
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        char* end = nullptr;
        double value = std::strtod(number.c_str(), &end);

        if (!end || strcmp(end, "d") == 0 && strcmp(end, "D") == 0)
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        dest.reference = value;
        return in;
    }

    std::istream& operator>>(std::istream& in, LongLongIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        std::string number;
        std::getline(in, number, ':');
        if (!in)
        {
            return in;
        }

        char* end = nullptr;
        long long value = std::strtoll(number.c_str(), &end, 10);

        if (!end || strcmp(end, "ll") != 0 && strcmp(end, "LL") != 0)
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        dest.reference = value;
        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::getline(in >> DelimiterIO{ '"' }, dest.reference, '"');
        return in >> DelimiterIO{ ':' };
    }

    std::istream& operator>>(std::istream& in, KeyIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::getline(in, dest.reference, ' ');
        if (in && !(dest.reference == "key1" ||
            dest.reference == "key2" || dest.reference == "key3")) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string data = "";
        if ((in >> StringIO{ data }) && (data != dest.expected))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
}
