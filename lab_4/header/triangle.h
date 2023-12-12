#pragma once

#include "./figure.h"

template <class T>
class Triangle;

template<typename T>
std::istream & operator>>(std::istream & stream, Triangle<T> & hex);

template <class T>
class Triangle final : public Figure<T>
{
public:
    Triangle();
    Triangle(const DArray<std::pair<T, T>> & points);
    Triangle(const std::initializer_list<std::pair<T, T>> & points);
    Triangle(const Triangle<T> & other) noexcept;
    Triangle(Triangle<T> && other) noexcept;

    friend std::istream & operator>> <>(std::istream & stream, Triangle&);

    ~Triangle() noexcept;

    std::pair<T, T> calculateGeomCentr() const;
    operator double() const;

    void operator=(const Triangle<T> & other);
    void operator=(Triangle<T> && other);

    bool operator==(const Triangle<T> & other) const;

private:
    bool checkValidPointsTriangle(const DArray<std::pair<T, T>> & points);
};

#include "../src/triangle-src.h"