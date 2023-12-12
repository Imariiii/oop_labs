#include "../header/functionDArray.h"

template <class T>
double calcualteAllArea(const DArray<Figure<T>*> & arrayFig)
{
    double result = 0;
    
    for (size_t i = 0; i < arrayFig.getSize(); ++i) {
        result += (double) *arrayFig[i];
    }

    return result;
}

template <class T>
void printCoordGeomCenter(const DArray<Figure<T>*> & arrayFig, size_t index)
{
    if (index < 0 || index >= arrayFig.getSize()) {
        throw std::length_error("Error! printCoordGeomCentr: invalid index");
    }

    std::pair<T, T> coord;
    coord = arrayFig[index]->calculateGeomCentr();

    std::cout << "Ox: " << coord.first << " ";
    std::cout << "Oy: " << coord.second << std::endl;
}

template <class T>
void printAllCoordGeomCenter(const DArray<Figure<T>*> & arrayFig)
{
    for (size_t i = 0; i < arrayFig.getSize(); ++i) {
        std::cout << "\n    | " << arrayFig[i]->getNameFigure() << " center |\n";
        std::cout << "\t";
        printCoordGeomCenter(arrayFig, i);
    }
}

template <class T>
void printAllCoordArraysFigure(const DArray<Figure<T>*> & arrayFig)
{
    for (size_t i = 0; i < arrayFig.getSize(); ++i) {
        std::cout << "\n    |" <<  arrayFig[i]->getNameFigure() << " |\n";
        std::cout << *arrayFig[i] << std::endl;    
    }
}