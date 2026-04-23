#ifndef __RATIONAL_HPP
#define __RATIONAL_HPP

#include <cassert>
#include <istream>

class Rational {
public:
  Rational() : m_numerator(0), m_denominator(1) {}

  Rational(int numerator) : m_numerator(numerator), m_denominator(1) {}

  Rational(int numerator, int denominator) {
    assert(denominator != 0);

    m_numerator = numerator;
    m_denominator = denominator;
    normalise();
  }

  int numerator() const { return m_numerator; }
  int denominator() const { return m_denominator; }

  // Rational rat;
  // ++rat / rat++
  // --rat / rat--

  // 3/4 + 1 = (3 + 4*1)/4

  // int a = 10;
  // int b = ++a; // 11
  // int c = a++; // 11

  // префиксен operator++
  Rational &operator++() {
    m_numerator += m_denominator;
    normalise();
    return *this;
  }

  // постфиксен operator++
  Rational operator++(int) {
    Rational cpy(*this);
    ++(*this);
    return cpy;
  }

  Rational &operator+=(Rational const &other) {
    m_numerator = m_numerator * other.m_denominator + other.m_numerator * m_denominator;
    m_denominator *= other.m_denominator;

    normalise();

    return *this;
  }

  Rational operator+(Rational const &other) const {
    return Rational(*this) += other;
  }

  Rational &operator*=(Rational const &other) {
    m_numerator *= other.m_numerator;
    m_denominator *= other.m_denominator;

    normalise();

    return *this;
  }

  Rational operator*(Rational const &other) const {
    return Rational(*this) *= other;
  }

  // Rational rat;
  // rat() ~> double;

  // f(...)

  // викаме обекта като функция
  double operator()() const {
    return static_cast<double>(m_numerator) / m_denominator;
  }

  // Rational rat;
  // static_cast<double>(rat) ; (double)rat

  // оператор за преобразуване на типове
  operator double() const {
    // return (*this)();
    return static_cast<double>(m_numerator) / m_denominator;
  }

  // double x;
  // Rational rat;
  // rat + x ~> double;

  friend std::ostream &operator<<(std::ostream &os, Rational const &rat) {
    os << rat.m_numerator << '/' << rat.denominator();
    return os;
  }

  // Rational rat;
  // std::cin >> rat >> rat2;
  friend std::istream &operator>>(std::istream &is, Rational &rat) {
    is >> rat.m_numerator >> rat.m_denominator;
    return is;
  }

private:
  int m_numerator;
  int m_denominator;

  int gcd(int a, int b) {

    while (b != 0) {
      int t = b;
      b = a % b;
      a = t;
    }

    return a < 0 ? -a : a;
  }

  void normalise() {
    if (m_numerator == 0) {
      m_denominator = 1;
      return;
    }

    int g = gcd(m_numerator, m_denominator);
    m_numerator   /= g;
    m_denominator /= g;

    if (m_denominator < 0) {
      m_numerator   *= -1;
      m_denominator *= -1;
    }
  }
};

#endif // __RATIONAL_HPP
