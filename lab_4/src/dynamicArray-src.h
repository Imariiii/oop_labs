#include "../header/dynamicArray.h"

template <class T>
DArray<T>::DArray() : _size(0), _capacity(1) 
{
    _array = std::make_unique<T[]>(_capacity);
} 

template <class T>
DArray<T>::DArray(const std::initializer_list<T> & coord)
{
    _size = coord.size();
    _capacity = coord.size();
    _array = std::make_unique<T[]>(_capacity);

    size_t i = 0;
    for (T el : coord) {
        _array[i++] = el;
    }
}

template <class T>
DArray<T>::DArray(const DArray & other)
{
    this->_array = std::make_unique<T[]>(other._capacity);
    for (size_t i = 0; i < other.getSize(); ++i) {
        _array[i] = other._array[i];
    }
    this->_size = other._size;
    this->_capacity = other._capacity;  
}

template <class T>
DArray<T>::DArray(DArray&& other) noexcept
{
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_array, other._array);
}

template <class T>
DArray<T>::~DArray() noexcept
{
    _size = 0;
    _capacity = 0;
    _array = nullptr;
}

template <class T>
void DArray<T>::pushBack(const T & element)
{ 
    if (_size >= _capacity) {
        _capacity *= 2;
        std::unique_ptr<T[]> newArray = std::make_unique<T[]>(_capacity);

        for (size_t i = 0; i < _size; ++i) {
            newArray[i] = this->_array[i];
        }

        this->_array = std::move(newArray);
    }
    
    this->_array[_size++] = element;
}

template <class T>
void DArray<T>::deleteToIndex(size_t index)
{
    if (index < 0 || index >= _size) {
        throw std::length_error("Error! DArray deleteToIndex: Invalid index for deletion.");
    }

    for (size_t i = index; i < _size - 1; ++i) {
        this->_array[i] = this->_array[i + 1];
    }

    --_size;
}

template <class T>
T & DArray<T>::operator[](size_t index) const
{
    if (index >= _size) {
        throw std::range_error("Error! DArray operator[]: Invalid index");
    }

    return _array[index];
}

template <class T>
void DArray<T>::operator=(const DArray & other)
{
    this->_array = std::make_unique<T[]>(other._capacity);
    for (size_t i = 0; i < other.getSize(); ++i) {
        _array[i] = other._array[i];
    }
    this->_size = other._size;
    this->_capacity = other._capacity;  
}


template <class T>
void DArray<T>::operator=(DArray&& other)
{
    std::swap(_size, other._size);
    std::swap(_array, other._array);
    std::swap(_capacity, other._capacity);
}

template <class T>
bool DArray<T>::operator==(const DArray & other) const
{
    if (_size != other._size) {
        return false;
    }

    for (size_t i = 0; i < _size; ++i) {
        if (_array[i] != other._array[i]) {
            return false;
        }
    }

    return true;
}

template <class T>
size_t DArray<T>::getSize() const
{
    return _size;
}