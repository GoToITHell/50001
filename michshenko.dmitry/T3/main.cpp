#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <iterator>
#include <fstream>
#include <sstream>
#include <cctype>

#include "algoritms.hpp"
#include "service.hpp"
#include "Polygon.hpp"


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

    std::vector<Polygon> polygonsList;

    // Чтение фигур из файла
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

    // Построчное чтение команд из stdin
    std::string line;
    while (std::getline(std::cin, line)) {

        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string command;
        iss >> command;
        if (command.empty()) {
            continue;
        }

        // Площадь
        if (command == "AREA") {
            std::string value;
            iss >> value;

            if (value == "ODD" || value == "EVEN") {
                std::cout << std::fixed << std::setprecision(1) << areaEvenOdd(value, polygonsList) << std::endl;
            }
            else if (value == "MEAN") {
                if (polygonsList.empty()) {
                    invalComm();
                } else {
                    std::cout << std::fixed << std::setprecision(1) << areaMean(polygonsList) << std::endl;
                }
            }
            else {
                bool isNumber = true;
                for (char c : value) {
                    if (!std::isdigit(c))
                    {
                        isNumber = false;
                        break;
                    }
                }
                if (isNumber) {
                    int num = std::stoi(value);
                    if (num >= 3) {
                        std::cout << std::fixed << std::setprecision(1)<< areaNum(num, polygonsList) << std::endl;
                    } else {
                        invalComm();
                    }
                } else {
                    invalComm();
                }
            }
        }

        // минимальное и максимальное значения
        else if (command == "MAX" || command == "MIN") {
            if (polygonsList.empty()) {
                invalComm();
                continue;
            }
            std::string value;
            iss >> value;

            if (command == "MAX") {
                if (value == "AREA") {
                    std::cout << std::fixed << std::setprecision(1)<< maxAreaVertex("AREA", polygonsList) << std::endl;
                }
                else if (value == "VERTEXES") {
                    std::cout << static_cast<int>(maxAreaVertex("VERTEXES", polygonsList)) << std::endl;
                }
                else {
                    invalComm();
                }
            }
            else {
                if (value == "AREA") {
                    std::cout << std::fixed << std::setprecision(1)<< minAreaVertex("AREA", polygonsList) << std::endl;
                }
                else if (value == "VERTEXES") {
                    std::cout << static_cast<int>(minAreaVertex("VERTEXES", polygonsList)) << std::endl;
                }
                else {
                    invalComm();
                }
            }
        }

        // количество
        else if (command == "COUNT") {
            std::string value;
            iss >> value;

            if (value == "EVEN" || value == "ODD") {
                std::cout << countVertexOddNum(value, polygonsList) << std::endl;
            }
            else {
                bool isNumber = true;
                for (char c : value) {
                    if (!std::isdigit(c))
                    {
                        isNumber = false;
                        break;
                    }
                }
                if (isNumber) {
                    int num = std::stoi(value);
                    if (num >= 3) {
                        std::cout << countVertexOddNum(static_cast<size_t>(num), polygonsList) << std::endl;
                    } else {
                        invalComm();
                    }
                } else {
                    invalComm();
                }
            }
        }

        // Влезает ли фигуры в бласть
        else if (command == "INFRAME") {
            std::string polygonStr;
            std::getline(iss, polygonStr);
            size_t first = polygonStr.find_first_not_of(" \t");
            if (first != std::string::npos) {
                polygonStr = polygonStr.substr(first);
            } else {
                invalComm();
                continue;
            }

            std::istringstream polyIss(polygonStr);
            Polygon poly;
            if (!(polyIss >> poly)) {
                invalComm();
            } else {
                bool result = isInframe(poly, polygonsList);
                std::cout << (result ? "TRUE" : "FALSE") << std::endl;
            }
        }

        //Максимальная последовательность
        else if (command == "MAXSEQ") {
            std::string polygonStr;
            std::getline(iss, polygonStr);
            size_t first = polygonStr.find_first_not_of(" \t");
            if (first != std::string::npos) {
                polygonStr = polygonStr.substr(first);
            } else {
                invalComm();
                continue;
            }

            std::istringstream polyIss(polygonStr);
            Polygon target;
            if (!(polyIss >> target)) {
                invalComm();
            } else {
                int result = maxSeq(polygonsList, target);
                std::cout << result << std::endl;
            }
        }

        // иначе
        else {
            invalComm();
        }
    }

    return 0;
}
