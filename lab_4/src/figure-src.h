#include "../header/figure.h"

template <class T>
Figure<T>::Figure() :
    _points() {}

template <class T>
Figure<T>::Figure(const DArray<std::pair<T, T>> & points) :
    _points(points) {}

template <class T>
Figure<T>::Figure(const std::initializer_list<std::pair<T, T>> & coord) : 
    _points(coord) {}

template <class T>
Figure<T>::~Figure() noexcept
{
}

template <class T>
std::ostream & operator<<(std::ostream & stream, const Figure<T> & fig)
{
    size_t size = fig._points.getSize();

    if (size == 0) {
        return stream << 0;
    }

    for (size_t i = 0; i < size; ++i) {
        stream << "Point " << i + 1 << "| ";
        stream << "Ox: "<< fig._points[i].first << ' ';
        stream << "Oy: "<< fig._points[i].second << std::endl;
    }

    return stream;
}

template <class T>
std::istream & operator>>(std::istream & stream, Figure<T> & fig)
{
    std::pair<T, T> tmp;
    std::cout << "Enter Ox: ";
    stream >> tmp.first;
    std::cout << "Enter Oy: ";
    stream >> tmp.second;

    fig._points.pushBack(tmp);

    return stream;
}

template <class T>
DArray<std::pair<T, T>> Figure<T>::getArray()
{
    return _points._array;
}

template <class T>
double Figure<T>::calculateLengthOfSide() const
{
    return sqrt(pow(this->_points[0].first - this->_points[1].first, 2) + 
        pow(this->_points[0].second - this->_points[1].second, 2));
}

template <class T>
std::string Figure<T>::getNameFigure() const
{
    return this->_name;
}
