#include "../header/triangle.h"

template <class T>
Triangle<T>::Triangle()
{
    this->_name = "Triangle";
}

template <class T>
Triangle<T>::Triangle(const DArray<std::pair<T, T>> & points)
{
    if (points.getSize() != 3) {
        throw std::length_error("Error! Triangle Constructor: invalid number of coordinates");
    } else if (!checkValidPointsTriangle(points)) {
        throw std::invalid_argument("Error! Triangle Constructor: invalid points");
    } else {
        this->_points = points;
        this->_name = "Triangle";
    }
}

template <class T>
Triangle<T>::Triangle(const std::initializer_list<std::pair<T, T>> & points) 
{
    DArray<std::pair<T, T>> tmp(points);
    if (points.size() != 3) {
        throw std::length_error("Error! Triangle Constructor: invalid number of coordinates");
    } else if (!checkValidPointsTriangle(tmp)) {
        throw std::invalid_argument("Error! Triangle Constructor: invalid points");
    } else {
        this->_points = points;
        this->_name = "Triangle";
    }
}

template <class T>
Triangle<T>::Triangle(const Triangle<T> & other) noexcept
{
    this->_points = other._points;
    this->_name = "Triangle";
}

template <class T>
Triangle<T>::Triangle(Triangle<T> && other) noexcept
{
    std::swap(this->_points, other._points);
    std::swap(this->_name, other._name);
}


template <class T>
Triangle<T>::~Triangle() noexcept
{
}

template <class T>
std::istream & operator>>(std::istream & stream, Triangle<T> & tr)
{
    if (tr._points.getSize() != 0) {
        std::length_error("Error! operator>>: this Triangle already has points");
    } else {
        DArray<std::pair<T,T>> points;
        std::pair<T, T> tmp;
        int numbOfTop = 3;

        for (size_t i = 0; i < numbOfTop; ++i) {
            std::cout << "Point " << i + 1 << " ";
            std::cout << "Enter Ox: ";
            stream >> tmp.first;
            std::cout << "\t";
            std::cout << "Enter Oy: ";
            stream >> tmp.second;

            points.pushBack(tmp);
        }

        if(tr.checkValidPointsTriangle(points)) {
            tr._points = std::move(points);
            tr._name = "Triangle";
        } else {
            throw std::length_error("Error! Triangle operator>>: invalid points");
        }
    }

    return stream;
}

template <class T>
std::pair<T, T> Triangle<T>::calculateGeomCentr() const
{
    std::pair<T, T> tmp;

    for (size_t i = 0; i < this->_points.getSize(); ++i) {
        tmp.first += this->_points[i].first;
        tmp.second += this->_points[i].second;
    }

    tmp.first /= this->_points.getSize();
    tmp.second /= this->_points.getSize();

    return tmp;
}

template <class T> 
Triangle<T>::operator double() const
{
    T lenSide = this->calculateLengthOfSide();

    return ((pow(lenSide, 2) * sqrt(3)) / 4);
}

template <class T>
void Triangle<T>::operator=(const Triangle<T> & other)
{
    this->_points = other._points;
    this->_name = "Triangle";
}

template <class T>
void Triangle<T>::operator=(Triangle<T> && other)
{
    std::swap(this->_points, other._points);
    std::swap(this->_name, other._name);
}

template <class T>
bool Triangle<T>::operator==(const Triangle<T> & other) const
{
    if (this->calculateLengthOfSide() != other.calculateLengthOfSide()) {
        return false;       
    }

    return true;
}

template <class T>
bool Triangle<T>::checkValidPointsTriangle(const DArray<std::pair<T, T>> & points)
{
    bool allSidesEqual = true;

    for (int i = 0; i < 3; i++) {
        int nextIndex = (i + 1) % 3;
        
        double sideLength1 = (sqrt(pow(points[nextIndex].first - points[i].first, 2) +
                                 pow(points[nextIndex].second - points[i].second, 2)));
        double sideLength2 = (sqrt(pow(points[(nextIndex + 1) % 3].first - points[nextIndex].first, 2) +
                                 pow(points[(nextIndex + 1) % 3].second - points[nextIndex].second, 2)));

        if ((!(abs(sideLength2 - sideLength1) < EPS))) {
            allSidesEqual = false;
            break;
        }

    }

    return allSidesEqual ;
}