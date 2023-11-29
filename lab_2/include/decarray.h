#pragma once

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <ostream>

class Decimal {
private:
    unsigned char* digits;
    size_t size;

    void removeZeros();

public:
    Decimal();
    Decimal(const size_t& n, unsigned char value = 0);
    Decimal(const std::initializer_list<unsigned char> &values);
    Decimal(const std::string& str);
    Decimal(const Decimal& other);
    Decimal(Decimal&& move) noexcept;

    virtual ~Decimal() noexcept;

    Decimal& operator=(const Decimal& other);
    Decimal operator+(const Decimal& other) const;
    Decimal operator-(const Decimal& other) const;
    Decimal& operator+=(const Decimal& value);
    Decimal& operator-=(const Decimal& value);
    Decimal& operator++();
    Decimal operator++(int);
    Decimal& operator--();
    Decimal operator--(int);

    bool operator==(const Decimal& other) const;
    bool operator!=(const Decimal& other) const;
    bool operator<(const Decimal& other) const;
    bool operator>(const Decimal& other) const;
    bool operator<=(const Decimal& other) const;
    bool operator>=(const Decimal& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Decimal& t);

    void print() const;
    size_t getSize() const;
    std::string toString() const;

};