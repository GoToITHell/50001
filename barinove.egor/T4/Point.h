#ifndef POINT_H
#define POINT_H

struct Point {
    double x;
    double y;

    Point() :x(0), y(0) {};
    Point(double a, double b) :x(a), y(b) {};
};

#endif
