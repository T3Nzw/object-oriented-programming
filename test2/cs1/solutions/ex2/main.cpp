#include <iostream>
#include "Window.hpp"

int main() {

  Window<int> window(3, {1,2,3,4,5,6,7,8,9,10});

  std::cout << window << "| ";
  ++window;
  std::cout << window << "| ";
  ++window;
  std::cout << window;

  return 0;
}
