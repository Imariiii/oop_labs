#include "../header/hexagon.h"

template <class T>
Hexagon<T>::Hexagon()
{
    this->_name = "Hexagon";
}

template <class T>
Hexagon<T>::Hexagon(const DArray<std::pair<T, T>> & points)
{
    if (points.getSize() != 6) {
        throw std::length_error("Error! Hexagon Constructor: invalid number of coordinates");
    } else if (!checkValidPointsHexagon(points)) {
        throw std::invalid_argument("Error! Hexagon Constructor: invalid points");
    } else {
        this->_points = points;
        this->_name = "Hexagon";
    }
}

template <class T>
Hexagon<T>::Hexagon(const std::initializer_list<std::pair<T, T>> & points) 
{
    DArray<std::pair<T, T>> tmp(points);
    if (points.size() != 6) {
        throw std::length_error("Error! Hexagon Constructor: invalid number of coordinates");
    } else if (!checkValidPointsHexagon(tmp)) {
        throw std::invalid_argument("Error! Hexagon Constructor: invalid points");
    } else {
        this->_points = points;
        this->_name = "Hexagon";
    }
}

template <class T>
Hexagon<T>::Hexagon(const Hexagon<T> & other) noexcept
{
    this->_points = other._points;
    this->_name = "Hexagon";
}

template <class T>
Hexagon<T>::Hexagon(Hexagon<T> && other) noexcept
{
    std::swap(this->_points, other._points);
    std::swap(this->_name, other._name);
}


template <class T>
Hexagon<T>::~Hexagon() noexcept
{
}

template <class T>
std::istream & operator>>(std::istream & stream, Hexagon<T> & hex)
{
    if (hex._points.getSize() != 0) {
        std::length_error("Error! operator>>: this Hexagon already has points");
    } else {
        DArray<std::pair<T,T>> points;
        std::pair<T, T> tmp;
        int numbOfTop = 6;

        for (size_t i = 0; i < numbOfTop; ++i) {
            std::cout << "Point " << i + 1 << " ";
            std::cout << "Enter Ox: ";
            stream >> tmp.first;
            std::cout << "\t";
            std::cout << "Enter Oy: ";
            stream >> tmp.second;

            points.pushBack(tmp);
        }

        if(hex.checkValidPointsHexagon(points)) {
            hex._points = std::move(points);
            hex._name = "Hexagon";
        } else {
            throw std::length_error("Error! Hexagon operator>>: invalid points");
        }
    }

    return stream;
}

template <class T>
std::pair<T, T> Hexagon<T>::calculateGeomCentr() const
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
Hexagon<T>::operator double() const
{
    double lenSide = this->calculateLengthOfSide();
    return ((3 * sqrt(3) * pow(lenSide, 2)) / 2);
}

template <class T>
void Hexagon<T>::operator=(const Hexagon<T> & other)
{
    this->_points = other._points;
    this->_name = "Hexagon";
}

template <class T>
void Hexagon<T>::operator=(Hexagon<T> && other)
{
    std::swap(this->_points, other._points);
    std::swap(this->_name, other._name);
}

template <class T>
bool Hexagon<T>::operator==(const Hexagon<T> & other) const
{
    if (this->calculateLengthOfSide() != other.calculateLengthOfSide()) {
        return false;       
    }

    return true;
}

template <class T>
bool Hexagon<T>::checkValidPointsHexagon(const DArray<std::pair<T, T>> & points)
{
    bool allSidesEqual = true;

    for (int i = 0; i < 6; i++) {
        int nextIndex = (i + 1) % 6;
        
        double sideLength1 = (sqrt(pow(points[nextIndex].first - points[i].first, 2) +
                                 pow(points[nextIndex].second - points[i].second, 2)));
        double sideLength2 = (sqrt(pow(points[(nextIndex + 1) % 6].first - points[nextIndex].first, 2) +
                                 pow(points[(nextIndex + 1) % 6].second - points[nextIndex].second, 2)));
        
        double angle1 = atan2(points[nextIndex].second - points[i].second,
                                 points[nextIndex].first - points[i].first);
        double angle2 = atan2(points[(nextIndex + 1) % 6].second - points[nextIndex].second,
                                 points[(nextIndex + 1) % 6].first - points[nextIndex].first);
                                 
        if ((!(abs(sideLength2 - sideLength1) < EPS)) && (!(fabs(angle1 - angle2) < EPS))) {
            allSidesEqual = false;
            break;
        }

    }

    return allSidesEqual ;
}
