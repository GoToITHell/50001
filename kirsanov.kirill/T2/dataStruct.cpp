#include "dataStruct.h"
#include <iomanip>
#include <cmath>
namespace kirsanov
{
    // ОПЕРАТОР ВВОДА
    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        // sentry проверяет состояние потока и управляет пропуском пробелов
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        DataStruct input;           // временный объект для чтения
        bool isKey1Read = false;    // флаги для проверки чтения всех полей
        bool isKey2Read = false;
        bool isKey3Read = false;

        // Проверяем открывающую скобку и двоеточие "(:"
        in >> DelimetrIO{ '(' } >> DelimetrIO{ ':' };

        // Цикл чтения полей до тех пор, пока не прочитаны все три ключа
        while (in && !(isKey1Read && isKey2Read && isKey3Read))
        {
            std::string keyName = "";
            in >> KeyIO{ keyName };     // читаем имя ключа (key1, key2 или key3)

            // После ключа должен быть ровно один пробел (по заданию)
            if (in >> DelimetrIO{ ' ' })
            {
                // Чтение key1 (беззнаковое целое с суффиксом ull)
                if (keyName == "key1" && !isKey1Read)
                {
                    in >> ULLIO{ input.key1 };
                    isKey1Read = static_cast<bool>(in);
                }
                // Чтение key2 (комплексное число в формате #c(real imag))
                else if (keyName == "key2" && !isKey2Read)
                {
                    in >> ComplexIO{ input.key2 };
                    isKey2Read = static_cast<bool>(in);
                }
                // Чтение key3 (строка в двойных кавычках)
                else if (keyName == "key3" && !isKey3Read)
                {
                    in >> StringIO{ input.key3 };
                    isKey3Read = static_cast<bool>(in);
                }
                else
                {
                    // Неизвестный ключ или повторное чтение
                    in.setstate(std::ios::failbit);
                }

                // После значения должен быть разделитель ':'
                in >> DelimetrIO{ ':' };
            }
        }

        // Проверяем закрывающую скобку и что все поля прочитаны
        if ((in >> DelimetrIO{ ')' }) && isKey1Read && isKey2Read && isKey3Read)
        {
            dest = std::move(input);  // перемещаем во избежание копирования
        }
        else
        {
            in.setstate(std::ios::failbit);  // ошибка формата
        }

        return in;
    }

    // ОПЕРАТОР ВЫВОДА
    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }

        iofmtguard fmtguard(out);

        out << "(:key1 ";
        out << src.key1 << "ull";
        out << ":key2 #c("
            << std::fixed << std::setprecision(1)
            << src.key2.real() << " " << src.key2.imag() << ")";
        out << ":key3 \"" << src.key3 << "\":)";

        return out;
    }

    // ОПЕРАТОР СРАВНЕНИЯ ДЛЯ СОРТИРОВКИ
    bool operator<(const DataStruct& lhs, const DataStruct& rhs)
    {
        // 1. Сравнение по возрастанию key1
        if (lhs.key1 != rhs.key1)
        {
            return lhs.key1 < rhs.key1;
        }

        // 2. Если key1 равны - сравнение по модулю комплексного числа key2
        double lhsAbs = std::abs(lhs.key2);
        double rhsAbs = std::abs(rhs.key2);

        if (lhsAbs != rhsAbs)
        {
            return lhsAbs < rhsAbs;
        }

        // 3. Если все поля равны - сравнение по длине строки key3
        return lhs.key3.size() < rhs.key3.size();
    }
}
