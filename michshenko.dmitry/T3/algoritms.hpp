#ifndef ALGORITMS_HPP
#define ALGORITMS_HPP

#include <string>
#include <vector>
#include "Polygon.hpp"

// AREA
double areaEvenOdd(const std::string& value, const std::vector<Polygon>& pols);
double areaMean(const std::vector<Polygon>& pols);
double areaNum(int value, const std::vector<Polygon>& pols);

// MAX / MIN
double maxAreaVertex(const std::string& value, const std::vector<Polygon>& pols);
double minAreaVertex(const std::string& value, const std::vector<Polygon>& pols);

// COUNT
int countVertexOddNum(const std::string& value, const std::vector<Polygon>& pols);
int countVertexOddNum(size_t value, const std::vector<Polygon>& pols);

// INFRAME / MAXSEQ
bool isInframe(const Polygon& pol, const std::vector<Polygon>& pols);
int maxSeq(const std::vector<Polygon>& pols, const Polygon& target);

#endif
