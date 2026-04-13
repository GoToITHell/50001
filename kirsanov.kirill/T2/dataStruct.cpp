#include "dataStruct.h"
#include <iomanip>
#include <cmath>

namespace kirsanov
{

    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        // sentry проверяет состояние потока
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        DataStruct input;           // временный объект для чтения
        bool isKey1Read = false;    // флаги для проверки чтения всех полей
        bool isKey2Read = false;
        bool isKey3Read = false;

        in >> std::ws;
        in >> DelimetrIO{ '(' } >> DelimetrIO{ ':' }; // проверяем "(:"

        // Цикл чтения полей до тех пор, пока не прочитаны все три ключа
        while (in && !(isKey1Read && isKey2Read && isKey3Read))
        {
            std::string keyName = "";
            in >> KeyIO{ keyName };
            in >> std::ws;              // пропускаем пробелы после ключа

            if (in)
            {
                // Чтение key1 (беззнаковое целое с суффиксом)
                if (keyName == "key1" && !isKey1Read)
                {
                    in >> std::ws;
                    in >> ULLIO{ input.key1 };
                    isKey1Read = static_cast<bool>(in);
                }
                // Чтение key2 (комплексное число в формате #c(real imag))
                else if (keyName == "key2" && !isKey2Read)
                {
                    in >> std::ws;
                    in >> ComplexIO{ input.key2 };
                    isKey2Read = static_cast<bool>(in);
                }
                // Чтение key3 (строка в кавычках)
                else if (keyName == "key3" && !isKey3Read)
                {
                    in >> std::ws;
                    in >> StringIO{ input.key3 };
                    isKey3Read = static_cast<bool>(in);
                }
                else
                {
                    // Неизвестный ключ или повторное чтение
                    in.setstate(std::ios::failbit);
                }

                in >> DelimetrIO{ ':' }; // после значения должен быть ':'
            }
        }

        // Проверяем закрывающую скобку и что все поля прочитаны
        char c;
        in >> c;
        if (c == ')' && isKey1Read && isKey2Read && isKey3Read)
        {
            dest = std::move(input);  // перемещаем во избежание копирования
        }
        else
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    // Оператор вывода DataStruct в поток
    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }

        iofmtguard fmtguard(out);  //  сохраняем и восстанавливаем флаги форматирования

        // Вывод в фиксированном порядке: key1, key2, key3 (как требуется в задании)
        out << "(:key1 ";
        out << src.key1 << "ULL";   // ULL LIT с суффиксом ULL
        out << ":key2 #c("
            << std::fixed << std::setprecision(1)
            << src.key2.real() << " " << src.key2.imag() << ")";
        out << ":key3 \"" << src.key3 << "\":)";

        return out;
    }

    // Оператор сравнения для сортировки (компаратор)
    bool operator<(const DataStruct& lhs, const DataStruct& rhs)
    {
        // 1. Сравнение по возрастанию key1
        if (lhs.key1 != rhs.key1)
        {
            return lhs.key1 < rhs.key1;
        }

        // 2. Если key1 равны - сравнение по модулю комплексного числа key2
        if (std::abs(lhs.key2) != std::abs(rhs.key2))
        {
            return std::abs(lhs.key2) < std::abs(rhs.key2);
        }

        // 3. Если все поля равны - сравнение по длине строки key3
        return lhs.key3.size() < rhs.key3.size();
    }
}
