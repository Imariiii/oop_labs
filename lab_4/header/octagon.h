#pragma once

#include "./figure.h"

template <class T>
class Octagon;

template<typename T>
std::istream & operator>>(std::istream & stream, Octagon <T> & hex);

template <class T>
class Octagon final : public Figure<T>
{
public:
    Octagon();
    Octagon(const DArray<std::pair<T, T>> & points);
    Octagon(const std::initializer_list<std::pair<T, T>> & points);
    Octagon(const Octagon<T> & other) noexcept;
    Octagon(Octagon<T> && other) noexcept;

    friend std::istream & operator>> <>(std::istream & stream, Octagon&);

    ~Octagon() noexcept;

    std::pair<T, T> calculateGeomCentr() const;
    operator double() const;

    void operator=(const Octagon<T> & other);
    void operator=(Octagon<T> && other);

    bool operator==(const Octagon<T> & other) const;

private:
    bool checkValidPointsOctagon(const DArray<std::pair<T, T>> & points);
};

#include "../src/octagon-src.h"