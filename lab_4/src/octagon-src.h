#include "../header/octagon.h"

template <class T>
Octagon<T>::Octagon()
{
    this->_name = "Octagon";
}

template <class T>
Octagon<T>::Octagon(const DArray<std::pair<T, T>> & points)
{
    if (points.getSize() != 8) {
        throw std::length_error("Error! Octagon Constructor: invalid number of coordinates");
    } else if (!checkValidPointsOctagon(points)) {
        throw std::invalid_argument("Error! Octagon Constructor: invalid points");
    } else {
        this->_points = points;
        this->_name = "Octagon";
    }
}

template <class T>
Octagon<T>::Octagon(const std::initializer_list<std::pair<T, T>> & points) 
{
    DArray<std::pair<T, T>> tmp(points);
    if (points.size() != 8) {
        throw std::length_error("Error! Octagon Constructor: invalid number of coordinates");
    } else if (!checkValidPointsOctagon(tmp)) {
        throw std::invalid_argument("Error! Octagon Constructor: invalid points");
    } else {
        this->_points = points;
        this->_name = "Octagon";
    }
}

template <class T>
Octagon<T>::Octagon(const Octagon<T> & other) noexcept
{
    this->_points = other._points;
    this->_name = "Octagon";
}

template <class T>
Octagon<T>::Octagon(Octagon<T> && other) noexcept
{
    std::swap(this->_points, other._points);
    std::swap(this->_name, other._name);
}


template <class T>
Octagon<T>::~Octagon() noexcept
{
}

template <class T>
std::istream & operator>>(std::istream & stream, Octagon<T> & oc)
{
    if (oc._points.getSize() != 0) {
        std::length_error("Error! operator>>: this Octagon already has points");
    } else {
        DArray<std::pair<T,T>> points;
        std::pair<T, T> tmp;
        int numbOfTop = 8;

        for (size_t i = 0; i < numbOfTop; ++i) {
            std::cout << "Point " << i + 1 << " ";
            std::cout << "Enter Ox: ";
            stream >> tmp.first;
            std::cout << "\t";
            std::cout << "Enter Oy: ";
            stream >> tmp.second;

            points.pushBack(tmp);
        }

        if(oc.checkValidPointsOctagon(points)) {
            oc._points = std::move(points);
            oc._name = "Octagon";
        } else {
            throw std::length_error("Error! Octagon operator>>: invalid points");
        }
    }

    return stream;
}

template <class T>
std::pair<T, T> Octagon<T>::calculateGeomCentr() const
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
Octagon<T>::operator double() const 
{
    double lenSide = this->calculateLengthOfSide();

    return (2 * pow(lenSide, 2) * (1 + sqrt(2)));
}

template <class T>
void Octagon<T>::operator=(const Octagon<T> & other)
{
    this->_points = other._points;
    this->_name = "Octagon";
}

template <class T>
void Octagon<T>::operator=(Octagon<T> && other)
{
    std::swap(this->_points, other._points);
    std::swap(this->_name, other._name);
}

template <class T>
bool Octagon<T>::operator==(const Octagon<T> & other) const
{
    if (this->calculateLengthOfSide() != other.calculateLengthOfSide()) {
        return false;       
    }

    return true;
}

template <class T>
bool Octagon<T>::checkValidPointsOctagon(const DArray<std::pair<T, T>> & points)
{
    bool allSidesEqual = true;

    for (int i = 0; i < 8; i++) {
        int nextIndex = (i + 1) % 8;
        
        double sideLength1 = (sqrt(pow(points[nextIndex].first - points[i].first, 2) +
                                 pow(points[nextIndex].second - points[i].second, 2)));
        double sideLength2 = (sqrt(pow(points[(nextIndex + 1) % 8].first - points[nextIndex].first, 2) +
                                 pow(points[(nextIndex + 1) % 8].second - points[nextIndex].second, 2)));
        
        double angle1 = atan2(points[nextIndex].second - points[i].second,
                                 points[nextIndex].first - points[i].first);
        double angle2 = atan2(points[(nextIndex + 1) % 8].second - points[nextIndex].second,
                                 points[(nextIndex + 1) % 8].first - points[nextIndex].first);
                                 
        if ((!(abs(sideLength2 - sideLength1) < EPS)) && (!(fabs(angle1 - angle2) < EPS))) {
            allSidesEqual = false;
            break;
        }

    }

    return allSidesEqual ;
}
