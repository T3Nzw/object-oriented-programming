#include "Matrix.hpp"
#include "Polynomial.hpp"
#include "Rational.hpp"
#include "UniquePtr.hpp"
#include <iostream>

struct A {
  void print() const {
    std::cout << "A\n";
  }
};

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

  // помислете защо това води до проблем и как може да го оправите :)
  // std::cout << poly2(1) << '\n';

  UniquePtr<int> iPtr = makeUnique(19);

  std::cout << *iPtr << '\n';

  A *a = new A;
  a->print();
  delete a;

  // следното е невалидно :D
  // и се счита за дефиниция на функционален указател
  // (т.нар. most vexing parse)
  UniquePtr<A> aptr(A());

  UniquePtr<A> aPtr(A{});
  UniquePtr<A> apTr2 = makeUnique(A());

  aPtr->print();

  return 0;
}
