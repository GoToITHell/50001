#ifndef IOFMTGUARD_H
#define IOFMTGUARD_H

#include <ios>

namespace kirsanov {

    class iofmtguard
    {
    public:
        explicit iofmtguard(std::basic_ios<char>& s);
        ~iofmtguard();

    private:
        std::basic_ios<char>& s_; //поток
        std::streamsize width_; //ширина поля вывода
        char fill_; //символ заполнения
        std::streamsize precision_;
        std::ios::fmtflags fmt_; //флаши форматирования
    };
}
#endif
