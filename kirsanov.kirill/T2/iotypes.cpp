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

        std::string tmp;
        // Читаем посимвольно, пока символ может быть частью числа ULL
        // (цифры, u, U, l, L) - это позволяет остановиться на разделителе ':'
        while (in && (std::isdigit(static_cast<unsigned char>(in.peek())) ||
            in.peek() == 'u' || in.peek() == 'U' ||
            in.peek() == 'l' || in.peek() == 'L'))
        {
            tmp.push_back(in.get());
        }

        if (tmp.empty())
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        bool valid = false;
        unsigned long long value = 0;

        // Проверяем суффикс "ull"
        if (tmp.size() >= 3)
        {
            std::string suffix = tmp.substr(tmp.size() - 3);
            for (char& c : suffix) c = std::tolower(c);  // к нижнему регистру

            if (suffix == "ull")
            {
                try
                {
                    value = std::stoull(tmp.substr(0, tmp.size() - 3));
                    valid = true;
                }
                catch (...) {}
            }
        }

        // Если нет суффикса - пробуем как обычное число
        if (!valid)
        {
            try
            {
                value = std::stoull(tmp);
                valid = true;
            }
            catch (...) {}
        }

        if (valid)
        {
            dest.ref = value;
        }
        else
        {
            in.setstate(std::ios::failbit);
        }

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
