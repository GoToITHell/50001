#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <limits>

#include "algoritms.hpp"
#include "Polygon.hpp"
#include "service.hpp"

// Вспомогательная функция, чтобы разбить строку на слова
static std::vector<std::string> split(const std::string& line) {
    std::istringstream iss(line);
    return { std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>() };
}


static void invalidCommand() {
    std::cout << "<INVALID COMMAND>" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "ERROR: incorrect input" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "ERROR: cannot open file" << std::endl;
        return 1;
    }

    // Чтение фигур из файла (
    std::vector<Polygon> polygonsList;
    while (!input.eof()) {
        std::copy(
            std::istream_iterator<Polygon>(input),
            std::istream_iterator<Polygon>(),
            std::back_inserter(polygonsList)
        );
        if (input.fail() && !input.eof()) {
            input.clear();
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::vector<std::string> words = split(line);
        if (words.empty()) continue;

        const std::string& cmd = words[0];

        try {
            // Площадь
            if (cmd == "AREA") {
                if (words.size() != 2)
                {
                    throw std::runtime_error("");
                }
                const std::string& arg = words[1];

                if (arg == "ODD" || arg == "EVEN") {
                    std::cout << std::fixed << std::setprecision(1) << areaEvenOdd(arg, polygonsList) << std::endl;
                }
                else if (arg == "MEAN") {
                    if (polygonsList.empty())
                    {
                        throw std::runtime_error("");
                    }
                    std::cout << std::fixed << std::setprecision(1)<< areaMean(polygonsList) << std::endl;
                }
                else {
                    int vertexCount = std::stoi(arg);
                    if (vertexCount < 3)
                    {
                        throw std::runtime_error("");
                    }
                    std::cout << std::fixed << std::setprecision(1)<< areaNum(vertexCount, polygonsList) << std::endl;
                }
            }
            // MAX/MIN
            else if (cmd == "MAX" || cmd == "MIN") {
                if (words.size() != 2)
                {
                    throw std::runtime_error("");
                }
                if (polygonsList.empty())
                {
                    throw std::runtime_error("");
                }

                const std::string& arg = words[1];
                if (cmd == "MAX") {
                    if (arg == "AREA") {
                        std::cout << std::fixed << std::setprecision(1)<< maxAreaVertex("AREA", polygonsList) << std::endl;
                    } else if (arg == "VERTEXES") {
                        std::cout << static_cast<int>(maxAreaVertex("VERTEXES", polygonsList)) << std::endl;
                    } else
                    {
                        throw std::runtime_error("");
                    }
                } else {
                    if (arg == "AREA") {
                        std::cout << std::fixed << std::setprecision(1)<< minAreaVertex("AREA", polygonsList) << std::endl;
                    } else if (arg == "VERTEXES") {
                        std::cout << static_cast<int>(minAreaVertex("VERTEXES", polygonsList)) << std::endl;
                    } else
                    {
                        throw std::runtime_error("");
                    }
                }
            }
            // Количество
            else if (cmd == "COUNT") {
                if (words.size() != 2)
                {
                    throw std::runtime_error("");
                }
                const std::string& arg = words[1];

                if (arg == "EVEN" || arg == "ODD") {
                    std::cout << countVertexOddNum(arg, polygonsList) << std::endl;
                } else {
                    int vertexCount = std::stoi(arg);
                    if (vertexCount < 3)
                    {
                        throw std::runtime_error("");
                    }
                    std::cout << countVertexOddNum(static_cast<size_t>(vertexCount), polygonsList) << std::endl;
                }
            }
            // Влезают ли фигуры в область
            else if (cmd == "INFRAME") {
                if (words.size() < 2)
                {
                    throw std::runtime_error("");
                }
                std::string polygonStr;
                for (size_t i = 1; i < words.size(); ++i) {
                    if (i != 1) polygonStr += " ";
                    polygonStr += words[i];
                }
                std::istringstream iss(polygonStr);
                Polygon poly;
                if (!(iss >> poly))
                {
                    throw std::runtime_error("");
                }

                char leftover;
                if (iss >> leftover)
                {
                    throw std::runtime_error("");
                }

                bool res = isInframe(poly, polygonsList);
                std::cout << (res ? "<TRUE>" : "<FALSE>") << std::endl;
            }
            // МАксимальна последовательность
            else if (cmd == "MAXSEQ") {
                if (words.size() < 2)
                {
                    throw std::runtime_error("");
                }
                std::string polygonStr;
                for (size_t i = 1; i < words.size(); ++i) {
                    if (i != 1) polygonStr += " ";
                    polygonStr += words[i];
                }
                std::istringstream iss(polygonStr);
                Polygon target;
                if (!(iss >> target))
                {
                    throw std::runtime_error("");
                }
                char leftover;
                if (iss >> leftover)
                {
                    throw std::runtime_error("");
                }
                std::cout << maxSeq(polygonsList, target) << std::endl;
            }
            // иначе
            else {
                throw std::runtime_error("");
            }
        }
        catch (const std::exception&) {
            invalidCommand();
        }
    }

    return 0;
}
