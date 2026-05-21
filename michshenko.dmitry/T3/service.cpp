#include "service.hpp"
#include <limits>
#include <string>
#include <iostream>

void invalComm() {
    std::cout << "<INVALID COMMAND>" << std::endl;
}

bool isEmpty(std::vector<Polygon>& polys) {
    return polys.empty();
}

std::istream& operator>>(std::istream& in, Point& point) {
    char ch;
    if (in >> ch && ch == '(' &&
        in >> point.x >> ch && ch == ';' &&
        in >> point.y >> ch && ch == ')') {
        return in;
    }
    in.setstate(std::ios::failbit);
    return in;
}

std::istream& operator>>(std::istream& in, Polygon& pol) {
    size_t count = 0;
    pol.points.clear();

    if (!(in >> count) || count < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    for (size_t i = 0; i < count; ++i) {
        Point p;
        if (!(in >> p)) {
            in.setstate(std::ios::failbit);
            return in;
        }
        pol.points.push_back(p);
    }

    return in;
}
