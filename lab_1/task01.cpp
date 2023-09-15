#include <iostream>
#include "max_n.h"

int main() {
  ull devider, bound;
  std::cout << "enter devider: ";
  std::cin  >> devider;
  std::cout << "enter bound: ";
  std::cin  >> bound;


  std::cout << "result: " << max_n(devider, bound) << std::endl;

  return 0;
}