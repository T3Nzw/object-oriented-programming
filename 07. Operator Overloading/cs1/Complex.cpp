#include "Complex.hpp"
#include <istream>
#include <ostream>
#include <cmath>

Complex::Complex(double real)
: Complex(real, 0) {}

Complex::Complex(double real, double imaginary)
: m_real(real), m_imaginary(imaginary) {}

Complex &Complex::operator+=(Complex const &other) {
  m_real += other.m_real;
  m_imaginary += other.m_imaginary;
  return *this;
}

Complex operator+(Complex const &lhs, Complex const &rhs) {
  Complex result(lhs);
  result += rhs;
  return result;
}

Complex Complex::operator-() const {
  Complex result(*this);
  result.m_real *= -1;
  result.m_imaginary *= -1;
  return result;
}

Complex &Complex::operator-=(Complex const &other) {
  *this += -other;
  // operator+=(-other);
  return *this;
}

std::ostream &operator<<(std::ostream &os, Complex const &other) {
  os << other.m_real;
  os << (other.m_imaginary >= 0 ? "+" : "-");
  os << std::fabs(other.m_imaginary);
  os << "i";
  return os;
}

std::istream &operator>>(std::istream &is, Complex &other) {
  is >> other.m_real >> other.m_imaginary;
  return is;
}
