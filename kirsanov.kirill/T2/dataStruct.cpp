#include "dataStruct.h"
#include "iofmtguard.h"
#include <sstream>
#include <iomanip>

namespace kirsanov {

    //PARSERS
    bool parseULL(const std::string& str, unsigned long long& value)
    {
        if (str.size() < 3 || str.substr(str.size() - 3) != "ull")
            return false;

        try
        {
            value = std::stoull(str.substr(0, str.size() - 3));
        }
        catch (...)
        {
            return false;
        }
        return true;
    }

    bool parseComplex(const std::string& str, std::complex<double>& value)
    {
        if (str.find("#c(") != 0 || str.back() != ')')
            return false;

        std::string inside = str.substr(3, str.size() - 4);
        std::istringstream iss(inside);

        double real, imag;
        if (!(iss >> real >> imag))
            return false;

        value = { real, imag };
        return true;
    }

    //INPUT
    std::istream& operator>>(std::istream& in, DataStruct& data)
    {
        std::string content;

        if (!std::getline(in, content))
            return in;

        if (content.empty() || content.front() != '(' || content.back() != ')')
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        std::istringstream iss(content.substr(1, content.size() - 2));

        std::string token;
        bool has1 = false, has2 = false, has3 = false;

        //разбиение строки по ключам
        while (std::getline(iss, token, ':'))
        {
            if (token.empty())
                continue;

            //проверка, что кавычки закрыты
            //если нечетное количество, значит строка разбита неверно
            if (std::count(token.begin(), token.end(), '"') % 2 != 0)
            {
                std::string extra;
                while (std::getline(iss, extra, ':'))
                {
                    token += ":" + extra;
                    if (std::count(extra.begin(), extra.end(), '"') % 2 != 0)
                        break;
                }
            }
            
            std::istringstream field(token);
            std::string key, value;

            //получение ключа и значения
            field >> key;

            std::getline(field, value);

            if (!value.empty() && value[0] == ' ')
            {
                value.erase(0, 1); // убрать пробел
            }

            if (key == "key1")
            {
                unsigned long long v;
                if (!parseULL(value, v))
                {
                    in.setstate(std::ios::failbit);
                    break;
                }
                data.key1 = v;
                has1 = true;
            }
            else if (key == "key2")
            {
                std::complex<double> c;
                if (!parseComplex(value, c))
                {
                    in.setstate(std::ios::failbit);
                    break;
                }
                data.key2 = c;
                has2 = true;
            }
            else if (key == "key3")
            {
                if (value.size() < 2 || value.front() != '"' || value.back() != '"')
                {
                    in.setstate(std::ios::failbit);
                    break;
                }
                data.key3 = value.substr(1, value.size() - 2);
                has3 = true;
            }
        }

        //проверка наличия всех ключей
        if (!has1 || !has2 || !has3)
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        return in;
    }


    //  OUTPUT
    std::ostream& operator<<(std::ostream& out, const DataStruct& d)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }

        iofmtguard fmtguard(out);

        out << "(:key1 ";
        out << d.key1 << "ull";
        out << ":key2 #c(" 
            << std::fixed<< std::setprecision(1) 
            <<d.key2.real() << " " << d.key2.imag() << ")";
        out << ":key3 \"" << d.key3 << "\":)";

        return out;
    }
}
