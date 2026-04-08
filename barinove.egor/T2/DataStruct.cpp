#include "DataStruct.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
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
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, ULLHexIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    iofmtguard guard(in);
    char c1, c2;
    in >> c1 >> c2;
    if (c1 == '0' && (c2 == 'x' || c2 == 'X')) {
        in >> std::hex >> dest.ref;
    }
    else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, ComplexIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    double re = 0.0, im = 0.0;
    in >> DelimiterIO{ '#' } >> DelimiterIO{ 'c' } >> DelimiterIO{ '(' } >> re >> im >> DelimiterIO{ ')' };

    if (in) {
        dest.ref = std::complex<double>(re, im);
    }
    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& operator>> (std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    DataStruct input;
    using sep = DelimiterIO;
    using ull = ULLHexIO;
    using cmp = ComplexIO;
    using str = StringIO;
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    in >> sep{ '(' } >> sep{ ':' };
    if (!in) return in;

    while (in) {
        in >> std::ws;
        if (in.peek() == ')') {
            in >> sep{ ')' };
            break;
        }

        std::string key;
        in >> key;
        if (!in) break;

        if (key == "key1") {
            in >> ull{ input.key1 };
            hasKey1 = true;
        }
        else if (key == "key2") {
            in >> cmp{ input.key2 };
            hasKey2 = true;
        }
        else if (key == "key3") {
            in >> str{ input.key3 };
            hasKey3 = true;
        }
        else {
            in.setstate(std::ios::failbit);
        }

        if (!in) break;

        in >> sep{ ':' };
    }

    if (hasKey1 && hasKey2 && hasKey3) {
        dest = std::move(input);
    }
    else {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }
    iofmtguard fmtguard(out);
    out << "(:";
    out << "key1 " << "0x" << std::hex << std::uppercase << src.key1 << ':';
    out << std::nouppercase;
    out << "key2 " << "#c(" << std::fixed << std::setprecision(1) << src.key2.real() << ' ' << src.key2.imag() << "):";
    out << "key3 " << '\"' << src.key3 << '\"';
    out << ":)";
    return out;
}

bool compare(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    if (std::abs(a.key2) != std::abs(b.key2)) {
        return std::abs(a.key2) < std::abs(b.key2);
    }
    return a.key3.length() < b.key3.length();
}

iofmtguard::iofmtguard(std::basic_ios< char >& s) :
    s_(s),
    width_(s.width()),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
{
}

iofmtguard::~iofmtguard()
{
    s_.width(width_);
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}
