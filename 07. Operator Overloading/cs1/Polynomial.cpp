#include "Polynomial.hpp"

Polynomial::Polynomial(unsigned n) {
  m_degree = (n < 1) ? 1 : n;
  m_coeffs = new Monomial[m_degree];
}

Polynomial::Polynomial(Polynomial const &other) {
  copy(other);
}

Polynomial &Polynomial::operator=(Polynomial const &other) {
  if (this != &other) {
    free();
    copy(other);
  }
  return *this;
}

Polynomial::~Polynomial() { free(); }

void Polynomial::copy(Polynomial const &other) {
  m_degree = other.m_degree;

  m_coeffs = new Monomial[m_degree];
  for (unsigned i = 0; i < m_degree; ++i) {
    m_coeffs[i] = other.m_coeffs[i];
  }
}

void Polynomial::free() {
  // delete[] m_name;
  delete[] m_coeffs;
}
