#include "Matrix.hpp"
#include "Polynomial.hpp"
#include "Rational.hpp"
#include <cstddef>
#include <iostream>

int main() {

  Matrix<3,4> m;
  for (std::size_t i = 0; i < 3; ++i) {
    for (std::size_t j = 0; j < 4; ++j) {
      m[i][j] = i * j;
    }
  }

  std::cout << m[2][3] << '\n';

  Polynomial<double, double> poly1(2);
  std::cin >> poly1;

  std::cout << poly1 << '\n';

  std::cout << "p(2) = " << poly1(2) << '\n';

  Polynomial<Rational, double> poly2(2);
  std::cin >> poly2;

  std::cout << poly2 << '\n';

  // TODO:
  // std::cout << poly2(1) << '\n';

  return 0;
}
