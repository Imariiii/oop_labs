#pragma once

#include <initializer_list>
#include <limits>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <memory>

template <class T>
class DArray 
{
public:
    DArray();
    DArray(const std::initializer_list<T> & coord);
    DArray(const DArray & other);
    DArray(DArray&& other) noexcept;

    ~DArray() noexcept;

    void pushBack(const T & element);
    void deleteToIndex(size_t index);

    T & operator[](size_t index) const;

    size_t getSize() const;

    void operator=(const DArray & other);
    void operator=(DArray&& other);

    bool operator==(const DArray & other) const;

private:
    size_t _size = 0;
    size_t _capacity = 0;
    std::unique_ptr<T[]> _array;
};

#include "../src/dynamicArray-src.h"