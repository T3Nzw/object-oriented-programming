#include <ios>
#include <iostream>
#include <limits>

int main() {

  // изчистване състоянието на поток при прочитане на невалиден вход
  int x;
  std::cin >> x;

  while (!std::cin.good()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> x;
  }

  std::cout << x << '\n';

  std::cout << (char)std::cin.peek();

  char c;
  std::cin.get(c);
  std::cout.put(c).put('g').put('t');

  return 0;
}
