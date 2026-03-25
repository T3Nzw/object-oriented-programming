#ifndef __COMPLEX_HPP
#define __COMPLEX_HPP

#include <istream>
#include <ostream>

class Complex {
public:
  Complex(double real);
  Complex(double real, double imaginary);

public:
  // +
  // 7 + complex
  friend Complex operator+(Complex const &, Complex const &);
  // +=
  Complex &operator+=(Complex const &other);

  // -complex
  Complex operator-() const;

  // binaren -
  friend Complex operator-(Complex const &, Complex const &);
  // -=
  Complex &operator-=(Complex const &other);

  // *
  friend Complex operator*(Complex const &, Complex const &);
  // *=
  Complex &operator*=(Complex const &other);

  // ==
  // 7 == complex
  friend bool operator==(Complex const &, Complex const &);

  // <<
  friend std::ostream &operator<<(std::ostream &os, Complex const &);

  // >>
  // std::cin >> complex;
  friend std::istream &operator>>(std::istream &is, Complex &);

  // int x;
  // ++x; x++

  // ne mojem da predefinirame .
  // -> - mojem da go predefinirame
  // Complex *complex;
  // complex->m_real

private:
  double m_real;
  double m_imaginary;
};

#endif // __COMPLEX_HPP
