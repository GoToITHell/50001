#include "algoritms.hpp"
#include "service.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>
#include <iterator>




    // Вспомогательная функция площади (формула Гаусса)

    double areaPolygons(const std::vector<Point>& points) {
        if (points.size() < 3) return 0.0;
        double sum = 0.0;
        size_t n = points.size();
        for (size_t i = 0; i < n; ++i) {
            const Point& p1 = points[i];
            const Point& p2 = points[(i + 1) % n];
            sum += static_cast<double>(p1.x * p2.y - p2.x * p1.y);
        }
        return std::abs(sum) / 2.0;
    }

    // Компараторы для MAX/MIN
    bool AreaComparator(const Polygon& a, const Polygon& b) {
        return areaPolygons(a.points) < areaPolygons(b.points);
    }
    bool VertexComparator(const Polygon& a, const Polygon& b) {
        return a.points.size() < b.points.size();
    }


    // Bounding Box helpers (для INFRAME)
    BoundingBox getBoundingBox(const Polygon& poly) {
        if (poly.points.empty()) return {0,0,0,0};
        auto minX = std::min_element(poly.points.begin(), poly.points.end(),
            [](const Point& a, const Point& b) { return a.x < b.x; });
        auto maxX = std::max_element(poly.points.begin(), poly.points.end(),
            [](const Point& a, const Point& b) { return a.x < b.x; });
        auto minY = std::min_element(poly.points.begin(), poly.points.end(),
            [](const Point& a, const Point& b) { return a.y < b.y; });
        auto maxY = std::max_element(poly.points.begin(), poly.points.end(),
            [](const Point& a, const Point& b) { return a.y < b.y; });
        return {static_cast<double>(minX->x), static_cast<double>(minY->y),
                static_cast<double>(maxX->x), static_cast<double>(maxY->y)};
    }

    BoundingBox getOverallBoundingBox(const std::vector<Polygon>& pols) {
        if (pols.empty()) return {0,0,0,0};
        std::vector<BoundingBox> boxes(pols.size());
        std::transform(pols.begin(), pols.end(), boxes.begin(),
            [](const Polygon& p) { return getBoundingBox(p); });
        auto minX = std::min_element(boxes.begin(), boxes.end(),
            [](const BoundingBox& a, const BoundingBox& b) { return a.minX < b.minX; });
        auto minY = std::min_element(boxes.begin(), boxes.end(),
            [](const BoundingBox& a, const BoundingBox& b) { return a.minY < b.minY; });
        auto maxX = std::max_element(boxes.begin(), boxes.end(),
            [](const BoundingBox& a, const BoundingBox& b) { return a.maxX < b.maxX; });
        auto maxY = std::max_element(boxes.begin(), boxes.end(),
            [](const BoundingBox& a, const BoundingBox& b) { return a.maxY < b.maxY; });
        return {minX->minX, minY->minY, maxX->maxX, maxY->maxY};
    }

    // функции-геттеры минимальных координат
    double getMinX(const BoundingBox& b) { return b.minX; }
    double getMinY(const BoundingBox& b) { return b.minY; }
    double getMaxX(const BoundingBox& b) { return b.maxX; }
    double getMaxY(const BoundingBox& b) { return b.maxY; }
    bool isEqual(double a, double b) { return a >= b; }
    bool isLessEqual(double a, double b) { return a <= b; }

    // Сравнение двух многоугольников
    bool isPolygonsEqual(const Polygon& a, const Polygon& b) {
        if (a.points.size() != b.points.size())
        {
            return false;
        }
        auto pointsEqual = [](const Point& p1, const Point& p2) {
            return p1.x == p2.x && p1.y == p2.y;
        };
        auto it = std::search(a.points.begin(), a.points.end(),
                              b.points.begin(), b.points.end(), pointsEqual);
        if (it != a.points.end()) {
            size_t offset = std::distance(a.points.begin(), it);
            return std::equal(a.points.begin(), it,
                              b.points.end() - offset, b.points.end(), pointsEqual);
        }
        Polygon rev = b;
        std::reverse(rev.points.begin(), rev.points.end());
        return std::equal(a.points.begin(), a.points.end(),
                          rev.points.begin(), rev.points.end(), pointsEqual);
    }




// Публичные функции варианта
double areaEvenOdd(const std::string& value, const std::vector<Polygon>& pols) {
    bool needEven = (value == "EVEN");
    return std::accumulate(pols.begin(), pols.end(), 0.0,
        [needEven](double sum, const Polygon& p) {
            if ((p.points.size() % 2 == 0) == needEven)
                return sum + areaPolygons(p.points);
            return sum;
        });
}

// средняя площадь
double areaMean(const std::vector<Polygon>& pols) {
    if (pols.empty())
    {
        return 0.0;
    }
    double total = std::accumulate(pols.begin(), pols.end(), 0.0,
        [](double s, const Polygon& p) { return s + areaPolygons(p.points); });
    return total / static_cast<double>(pols.size());
}

// площадь по количеству вершин
double areaNum(int value, const std::vector<Polygon>& pols) {
    return std::accumulate(pols.begin(), pols.end(), 0.0,
        [value](double s, const Polygon& p) {
            return (p.points.size() == static_cast<size_t>(value)) ? s + areaPolygons(p.points) : s;
        });
}

// максимальная площадь по вершинам
double maxAreaVertex(const std::string& value, const std::vector<Polygon>& pols) {
    if (pols.empty())
    {
        return 0.0;
    }
    if (value == "AREA") {
        auto it = std::max_element(pols.begin(), pols.end(), AreaComparator);
        return areaPolygons(it->points);
    }
    if (value == "VERTEXES") {
        auto it = std::max_element(pols.begin(), pols.end(), VertexComparator);
        return static_cast<double>(it->points.size());
    }
    return 0.0;
}

// минимальная площадь по вершинам
double minAreaVertex(const std::string& value, const std::vector<Polygon>& pols) {
    if (pols.empty())
    {
        return 0.0;
    }
    if (value == "AREA") {
        auto it = std::min_element(pols.begin(), pols.end(), AreaComparator);
        return areaPolygons(it->points);
    }
    if (value == "VERTEXES") {
        auto it = std::min_element(pols.begin(), pols.end(), VertexComparator);
        return static_cast<double>(it->points.size());
    }
    return 0.0;
}

//
int countVertexOddNum(const std::string& value, const std::vector<Polygon>& pols) {
    bool countEven = (value == "EVEN");
    return std::count_if(pols.begin(), pols.end(),
        [countEven](const Polygon& p) {
            return (p.points.size() % 2 == 0) == countEven;
        });
}

//
int countVertexOddNum(size_t value, const std::vector<Polygon>& pols) {
    if (value < 3) return 0;
    return std::count_if(pols.begin(), pols.end(),
        [value](const Polygon& p) { return p.points.size() == value; });
}
// функции варианта
// проверка на вхождение фигур в область
bool isInframe(const Polygon& pol, const std::vector<Polygon>& pols) {
    if (pols.empty())
    {
        return false;
    }
    BoundingBox overall = getOverallBoundingBox(pols);
    BoundingBox test = getBoundingBox(pol);
    using namespace std::placeholders;
    auto checkMinX = std::bind(isEqual, std::bind(getMinX, test), std::bind(getMinX, overall));
    auto checkMaxX = std::bind(isLessEqual, std::bind(getMaxX, test), std::bind(getMaxX, overall));
    auto checkMinY = std::bind(isEqual, std::bind(getMinY, test), std::bind(getMinY, overall));
    auto checkMaxY = std::bind(isLessEqual, std::bind(getMaxY, test), std::bind(getMaxY, overall));
    auto checkX = std::bind(std::logical_and<bool>(), checkMinX, checkMaxX);
    auto checkY = std::bind(std::logical_and<bool>(), checkMinY, checkMaxY);
    auto result = std::bind(std::logical_and<bool>(), checkX, checkY);
    return result();
}

// максимальная повторяющиеся последовательность
int maxSeq(const std::vector<Polygon>& pols, const Polygon& target) {
    struct State
    {
        int cur = 0, best = 0;
    };
    State res = std::accumulate(pols.begin(), pols.end(), State{},
        [&target](State s, const Polygon& p) {
            if (p.points.size() < 3)
            {
              return s;
            }
            if (isPolygonsEqual(p, target)) {
                s.cur++;
                if (s.cur > s.best) s.best = s.cur;
            } else {
                s.cur = 0;
            }
            return s;
        });
    return res.best;
}
