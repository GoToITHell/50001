#include "iotypes.h"

namespace bahurov
{
    // ѕерегрузка оператора ввода дл¤ структуры DelimetrIO
    std::istream& operator>>(std::istream& in, DelimetrIO&& dest)
    {
        iofmtguard fmtguard(in);

        in >> std::noskipws;

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

    // ѕерегрузка оператора ввода дл¤ структуры CharIO
    std::istream& operator>>(std::istream& in, CharIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        char c = '0';
        in >> DelimetrIO{ '\'' } >> c >> DelimetrIO{ '\'' };
        if (in)
        {
            dest.ref = c;
        }
        else
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    // ѕерегрузка оператора ввода дл¤ структуры RationalIO
    std::istream& operator>>(std::istream& in, RationalIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        long long numerator = 0;
        unsigned long long denominator = 0;

        in >> DelimetrIO{ '(' } >> DelimetrIO{ ':' } >> DelimetrIO{ 'N' } >> DelimetrIO{ ' ' } >> numerator;
        in >> DelimetrIO{ ':' } >> DelimetrIO{ 'D' } >> DelimetrIO{ ' ' } >> denominator >> DelimetrIO{ ':' } >> DelimetrIO{ ')' };

        if (in && denominator != 0)
        {
            dest.ref = std::make_pair(numerator, denominator);
        }
        else
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    // ѕерегрузка оператора ввода дл¤ структуры StringIO
    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        // „итаем строку до закрывающей кавычки
        return std::getline(in >> DelimetrIO{ '"' }, dest.ref, '"');
    }

    // ѕерегрузка оператора ввода дл¤ структуры KeyIO
    std::istream& operator>>(std::istream& in, KeyIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        // „итаем символы, пока впереди буквы или цифры (std::isalnum)
        while (in && std::isalnum(in.peek()))
        {
            // »звлекаем символ из потока и добавл¤ем его в строку
            dest.ref.push_back(in.get());
        }

        bool isKeyCorrect = dest.ref == "key1" || dest.ref == "key2" || dest.ref == "key3";
        if (!(in && isKeyCorrect))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
}
