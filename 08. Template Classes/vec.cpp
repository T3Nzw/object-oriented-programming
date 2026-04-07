#include "Vector.hpp"

struct A {};

int main() {

  Vector<A> va;
  std::cout << va << '\n';

  Vector<int> v;
  for (int i = 0; i < 10; ++i)
    v.push_back(i);

  std::cout << v << '\n';

  while (v) {
    std::cout << v.pop_back() << ' ';
  }

  Vector<int> v2;

  try {
    std::cout << v2.at(0) << '\n';
  }
  catch (...) {
    std::cout << "no such element\n";
  }

  std::cout << "fnewjifnwi\n";

  return 0;
}
