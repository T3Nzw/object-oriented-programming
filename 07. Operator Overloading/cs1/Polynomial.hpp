#ifndef __POLYNOMIAL_HPP
#define __POLYNOMIAL_HPP

#include "Complex.hpp"

struct Monomial {
  Complex coeff;

  Monomial() : coeff(0,0) {}
};

class Polynomial {
public:
  // operator[](size_t index)
  // funkcionalni obekti
  Complex operator()(Complex const &) const;

  Monomial &operator[](unsigned power) {
    return m_coeffs[power];
  }

public:
  Polynomial(unsigned degree);
  Polynomial(Polynomial const &);
  Polynomial &operator=(Polynomial const &);
  ~Polynomial();

private:
  void copy(Polynomial const &other);
  void free();

private:
  // char *m_name;
  Monomial *m_coeffs;
  unsigned m_degree;
};

#endif // __POLYNOMIAL_HPP
