#include "triangle.h"

Triangle::Triangle() : Figure() {}

Triangle::Triangle(const std::vector<Point> & points) {
    if (points.size() != 3) {
        throw std::range_error("Invalid number of coordinates");
    } else if (!valid(points)){
        throw std::range_error("Triangle Constructor: invalid points");
    } else {
        _points = points;
    }
}

Triangle::Triangle(const Triangle &other) {
    _points = other._points;
}

Triangle::Triangle(const Triangle &&other) {
    _points = std::move(other._points);
}


bool Triangle::valid(const std::vector<Point> &p) const{
    double l1 = p[0].distance(p[1]), l2 = p[0].distance(p[2]), l3 = p[0].distance(p[2]);
    return fabs(l1 - l2) < EPSILON && fabs(l2 - l3) < EPSILON && fabs(l1 - l3) < EPSILON;
}

Triangle::operator double() const {
    if ((*this)._points.size() == 0) {
        throw std::range_error("Can't get square of empty");
    }
    return std::pow(this->_points[0].distance(this->_points[1]), 2) * std::pow(3, 0.5) / 4;
}

bool Triangle::isEqual(const Figure &other) const {
    if (_points.size() == 0 || other.getPoints().size() == 0) {
        throw std::range_error("Can't compare empty figures");
    }
    return fabs(other.getPoints()[0].distance(other.getPoints()[1]) - _points[0].distance(_points[1])) < EPSILON;
}

Point Triangle::getCenter() const {
    if ((*this).getPoints().size() == 0) {
        throw std::range_error("Can't get center of empty");
    }
    Point tmp = getAv(this->_points);
    return tmp;
}

void Triangle::print(std::ostream& os) const{
    if (_points.size() == 0) {
        throw std::logic_error("Can't print empty figure");
    }
    for (size_t i = 0; i < 3; i++) {
        os << _points[i];
    }
}

Triangle &Triangle::operator=(const Triangle &other) {
    _points = other._points;
    return *this;
}

Triangle &Triangle::operator=(const Triangle &&other) {
    _points = std::move(other._points);
    return *this;
}

void Triangle::input(std::istream &is) {
    std::vector<Point> tmp_v;
    Point tmp;
    for (size_t i = 0; i < 3; ++i) {
        is >> tmp;
        tmp_v.push_back(tmp);
    }
    if (!valid(tmp_v)) {
        throw std::range_error("Square Constructor: invalid points");
    } else {
        _points = tmp_v;
    }
}