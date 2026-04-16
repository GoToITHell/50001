#include "iotypes.h"
#include <cctype>

namespace kirsanov
{
    // ПРОВЕРКА СИМВОЛА-РАЗДЕЛИТЕЛЯ
    std::istream& operator>>(std::istream& in, DelimetrIO&& dest)
    {
        // Сохраняем флаги и отключаем пропуск пробелов
        iofmtguard fmtguard(in);
        in >> std::noskipws;  // Не пропускаем пробелы

        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        char c = '\0';
        in >> c;
        if (in && (c != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    // ЧТЕНИЕ ULL LIT (беззнаковое целое)
    std::istream& operator>>(std::istream& in, ULLIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        unsigned long long value;
        in >> value;

        if (!in)
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        char c1, c2, c3;
        in >> c1 >> c2 >> c3;

        if (std::tolower(c1) != 'u' ||
            std::tolower(c2) != 'l' ||
            std::tolower(c3) != 'l')
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        dest.ref = value;
        return in;
    }

    // ЧТЕНИЕ КОМПЛЕКСНОГО ЧИСЛА (CMP LSP)
    std::istream& operator>>(std::istream& in, ComplexIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        char c = '\0';
        in >> std::ws >> c;
        if (c != '#')
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        in >> c;
        if (c != 'c')
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        in >> c;
        if (c != '(')
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        double real = 0.0, imag = 0.0;
        in >> real >> imag;

        in >> std::ws >> c;
        if (c != ')')
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        dest.ref = { real, imag };
        return in;
    }

    // ЧТЕНИЕ СТРОКИ В ДВОЙНЫХ КАВЫЧКАХ
    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        // std::getline с разделителем '"' читает строку между кавычками
        return std::getline(in >> DelimetrIO{ '"' }, dest.ref, '"');
    }

    // ЧТЕНИЕ ИМЕНИ КЛЮЧА (key1, key2, key3)
    std::istream& operator>>(std::istream& in, KeyIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        dest.ref.clear();

        // Читаем ключ: буквы и цифры (key1, key2, key3)
        while (in && std::isalnum(static_cast<unsigned char>(in.peek())))
        {
            dest.ref.push_back(in.get());
        }

        // Проверяем, что прочитан один из допустимых ключей
        bool isKeyCorrect = (dest.ref == "key1" ||
            dest.ref == "key2" ||
            dest.ref == "key3");

        if (!(in && isKeyCorrect))
        {
            in.setstate(std::ios::failbit);
        }

        return in;
    }
}
