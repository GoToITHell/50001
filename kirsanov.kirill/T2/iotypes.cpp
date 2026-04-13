#include "iotypes.h"
#include <cctype>

namespace kirsanov
{
    // Проверка символа-разделителя
    std::istream& operator>>(std::istream& in, DelimetrIO&& dest)
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
            in.setstate(std::ios::failbit);  // не тот символ - ошибка
        }
        return in;
    }

    // Чтение ULL LIT (беззнакового целого с суффиксом u11 или ULL)
    std::istream& operator>>(std::istream& in, ULLIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        std::string tmp;
        // Читаем посимвольно, пока символ может быть частью числа ULL
        // (цифры, u, U, l, L) - это позволяет остановиться на ':'
        while (in && (std::isdigit(static_cast<unsigned char>(in.peek())) ||
            in.peek() == 'u' || in.peek() == 'U' ||
            in.peek() == 'l' || in.peek() == 'L'))
        {
            tmp.push_back(in.get());
        }

        bool valid = false;
        unsigned long long value = 0;

        // Проверяем суффиксы: ULL, ull
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
                catch (...) {}  // std::stoull может выбросить исключение
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
            in.setstate(std::ios::failbit);  // не удалось распарсить
        }

        return in;
    }

    // Чтение комплексного числа в формате #c(real imag)
    std::istream& operator>>(std::istream& in, ComplexIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        char c;
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
        in >> real >> imag;  // читаем действительную и мнимую части

        in >> std::ws >> c;
        if (c != ')')
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        dest.ref = { real, imag };
        return in;
    }

    // Чтение строки в двойных кавычках
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

    // Чтение имени ключа (key1, key2, key3)
    std::istream& operator>>(std::istream& in, KeyIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        dest.ref.clear();

        // Пропускаем пробелы перед ключом
        while (in && std::isspace(static_cast<unsigned char>(in.peek())))
        {
            in.get();
        }

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
