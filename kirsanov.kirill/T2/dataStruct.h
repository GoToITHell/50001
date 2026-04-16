#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <complex>
#include <string>
#include "iotypes.h"
#include "iofmtguard.h"

namespace kirsanov
{
    // Структура данных согласно варианту 10 (ULL LIT + CMP LSP)
    struct DataStruct
    {
        unsigned long long key1;        // ULL LIT - беззнаковое целое
        std::complex<double> key2;      // CMP LSP - комплексное число
        std::string key3;               // строковое поле
    };

    // Перегрузка оператора ввода для DataStruct
    std::istream& operator>>(std::istream& in, DataStruct& dest);

    // Перегрузка оператора вывода для DataStruct
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);

    // Перегрузка оператора сравнения для сортировки
    bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}

#endif
