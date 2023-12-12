#include "./header/figure.h"
#include "./header/hexagon.h"
#include "./header/triangle.h"
#include "./header/octagon.h"
#include "./header/functionDArray.h"

int main()
{

    Hexagon<double> hex;
    std::cout << "Enter sqagon: " << std::endl;
    std::cin >> hex;
    Triangle<double> tr;
    std::cout << "Enter triangle: " << std::endl;
    std::cin >> tr;
    Octagon<double> oc;
    std::cout << "Enter octagon: " << std::endl;
    std::cin >> oc;
    
    DArray<Figure<double>*> array{&hex, &tr, &oc};
    printAllCoordArraysFigure(array);
    std::cout << "Sum of areas figures in array: " 
        << calcualteAllArea(array) << std::endl;
    printAllCoordGeomCenter(array);
    
    
    return 0;
}