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

  // унарен operator-
  Rational operator-() const {
    return Rational(-m_numerator, m_denominator);
  }

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

  Rational &operator--() {
    m_numerator -= m_denominator;
    normalise();
    return *this;
  }

  Rational operator--(int) {
    Rational cpy(*this);
    --*this;
    return cpy;
  }

  Rational &operator+=(Rational const &other) {
    m_numerator = m_numerator * other.m_denominator + other.m_numerator * m_denominator;
    m_denominator *= other.m_denominator;

    normalise();

    return *this;
  }

  // това НЕ работи за нещо от вида 4 + rat, като rat има тип Rational,
  // тъй като лявата страна на оператора задължително трябва да е обект на
  // класа Rational (не може да се преобразува до такъв имплицитно).
  // затова единият вариант е да имплементираме по-долната friend функция
  Rational operator+(Rational const &other) const {
    return Rational(*this) += other;
  }

  friend Rational operator+(int x, Rational const &other) {
    return Rational(x) += other;
  }

  Rational &operator*=(Rational const &other) {
    m_numerator *= other.m_numerator;
    m_denominator *= other.m_denominator;

    normalise();

    return *this;
  }

  // бихме могли да направим същото нещо и с operator* (или operator-, operator/ и т.н.)

  /*
  Rational operator*(Rational const &other) const {
    return Rational(*this) *= other;
  }

  friend Rational operator*(int x, Rational const &other) {
    return Rational(x) *= other;
  }
  */

  // но бихме могли да обединим двете функции в една приятелска,
  // която позволява всеки от двата аргумента да бъде имплицитно
  // преобразуван до нещо от тип Rational (поне единият аргумент
  // трябва да има тип Rational!), т.е. можем да правим:
  // 1. rat1 + rat2
  // 2. rat1 + x
  // 3. x + rat1
  // където rat1 и rat2 са от тип Rational, а x - от тип int
  // (или тип, който може да бъде преобразуван до int)

  friend Rational operator*(Rational const &lhs, Rational const &rhs) {
    return Rational(lhs) *= rhs;
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

  // оператор за преобразуване на типове;
  // бяхме казали, че може да доведе до проблеми:
  // 1. ако имаме rat от тип Rational и x от тип double
  //    и предефиниран оператор + за Rational,
  //    то ще получим неяснота (ambiguity) при оценката на следния израз:
  //    rat + x (или x + rat), защото и operator+(double, double),
  //    и operator+(Rational const &, Rational const &) могат
  //    да бъдат използвани при оценката на горния израз.
  // 2. неявни преобразувания на Rational до double,
  //    които могат да доведат до различни проблеми (напр. горния)
  // п.с. ако тествате кода, закоментирайте този оператор, защото по-горе
  // са имплементирани operator+, operator* и т.н., така че може
  // да получите проблем като първия :) по принцип това нещо не бихме го имплементирали
  // с такъв оператор, а например - double toDouble() const метод, като това ни задължава
  // да го извикаме експлицитно (т.е. получаваме type safety)
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
