#include <iostream>
#include <stdexcept>

// може (и е по-добре) да се дефинира в заглавен файл

class Calculator {
public:
  static double add(double x, double y);
  static double sub(double x, double y);
  static double mul(double x, double y);
  static double div(double x, double y);

  // и други функции, които могат да бъдат полезни
};

double Calculator::add(double x, double y) {
  return x + y;
}

double Calculator::sub(double x, double y) {
  return x - y;
}

double Calculator::mul(double x, double y) {
  return x * y;
}

double Calculator::div(double x, double y) {
  if (y == 0)
    throw std::invalid_argument("cannot divide by 0");

  return x / y;
}
