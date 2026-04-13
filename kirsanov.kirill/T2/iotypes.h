#ifndef IOTYPES_H
#define IOTYPES_H

#include "iofmtguard.h"
#include <iostream>
#include <string>
#include <complex>

namespace kirsanov
{
    // Структура для проверки символов-разделителей
    struct DelimetrIO
    {
        char exp;  // ожидаемый символ
    };

    // Структура для чтения ULL LIT (беззнаковое целое)
    struct ULLIO
    {
        unsigned long long& ref;  // ссылка на поле для записи
    };

    // Структура для чтения CMP LSP (комплексного числа)
    struct ComplexIO
    {
        std::complex<double>& ref;  // ссылка на поле для записи
    };

    // Структура для чтения строки в кавычках
    struct StringIO
    {
        std::string& ref;  // ссылка на поле для записи
    };

    // Структура для чтения имени ключа (key1, key2, key3)
    struct KeyIO
    {
        std::string& ref;  // ссылка на строку для записи
    };

    // Перегрузки операторов ввода
    std::istream& operator>>(std::istream& in, DelimetrIO&& dest);
    std::istream& operator>>(std::istream& in, ULLIO&& dest);
    std::istream& operator>>(std::istream& in, ComplexIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, KeyIO&& dest);
}

#endif
