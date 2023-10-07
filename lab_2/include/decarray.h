#pragma once

#include <string>
#include <iostream>

class DecArray
{ 
public:
   DecArray();
   
   virtual ~DecArray() noexcept;
private:
    size_t _size;
    unsigned char *_array;
};
