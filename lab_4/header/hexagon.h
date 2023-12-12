#pragma once

#include "./figure.h"

template <class T>
class Hexagon;

template<typename T>
std::istream & operator>>(std::istream & stream, Hexagon <T> & hex);

template <class T>
class Hexagon final : public Figure<T>
{
public:
    Hexagon();
    Hexagon(const DArray<std::pair<T, T>> & points);
    Hexagon(const std::initializer_list<std::pair<T, T>> & points);
    Hexagon(const Hexagon<T> & other) noexcept;
    Hexagon(Hexagon<T> && other) noexcept;

    friend std::istream & operator>> <>(std::istream & stream, Hexagon&);

    ~Hexagon() noexcept;

    std::pair<T, T> calculateGeomCentr() const;
    operator double() const;

    void operator=(const Hexagon<T> & other);
    void operator=(Hexagon<T> && other);

    bool operator==(const Hexagon<T> & other) const;

private:
    bool checkValidPointsHexagon(const DArray<std::pair<T, T>> & points);
};

#include "../src/hexagon-src.h"