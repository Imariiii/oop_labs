#pragma once

#include "figure.h"

template <class T>
double calcualteAllArea(const DArray<std::unique_ptr<Figure<T>>> & arrayFig); 

template <class T>
void printCoordGeomCenter(const DArray<Figure<T>*> & arrayFig, size_t index);

template <class T>
void printAllCoordGeomCenter(const DArray<Figure<T>*> & arrayFig);

template <class T>
void printAllCoordArraysFigure(const DArray<Figure<T>*> & arrayFig);

#include "../src/functionDArray-src.h"