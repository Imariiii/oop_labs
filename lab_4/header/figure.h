#pragma once

#include <ostream>
#include <cmath>

#include "./dynamicArray.h"

#define EPS pow(10, -3)

template <class T>
class Figure;

template<typename T>
std::ostream & operator<<(std::ostream & stream, const Figure<T> & fig);

template<typename T>
std::istream & operator>>(std::istream & stream, Figure<T> & fig);

template <class T>
class Figure
{
public:
    Figure();
    Figure(const DArray<std::pair<T, T>> & points);
    Figure(const std::initializer_list<std::pair<T, T>> & coord);

    ~Figure() noexcept;

    friend std::ostream & operator<< <>(std::ostream & stream, const Figure&);
    friend std::istream & operator>> <>(std::istream & stream, Figure&);

    virtual operator double() const = 0;
    virtual std::pair<T, T> calculateGeomCentr() const = 0;

    DArray<std::pair<T, T>> getArray();

    double calculateLengthOfSide() const;
    std::string getNameFigure() const;

protected:
    DArray<std::pair<T, T>> _points;
    std::string _name = "unnamed";
};

#include "../src/figure-src.h"