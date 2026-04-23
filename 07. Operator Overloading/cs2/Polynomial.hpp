#ifndef __POLYNOMIAL_HPP
#define __POLYNOMIAL_HPP

#include <istream>
#include <ostream>
#include <utility>
#include <algorithm>

// при шаблони на класове няма как да имаме разделна компилация
template<typename CoeffType, typename VariableType>
class Polynomial {
public:
  CoeffType &operator[](std::size_t index);

  CoeffType const &operator[](std::size_t index) const {
    return m_coeffs[index];
  }

  // тук не приемаме x по референция, защото
  // така или иначе ще трябва да направим
  // негово копие, за да направим x *= x
  VariableType operator()(VariableType x) const {
    VariableType result = m_coeffs[0];
    for (std::size_t i = 1; i < m_size; ++i) {
      result += m_coeffs[i] * x;
      x *= x;
    }
    return result;
  }

  Polynomial &operator+=(Polynomial const &other) {
    resizeTo(std::max(m_size, other.m_size));

    for (std::size_t i = 0; i < other.m_size; ++i) {
      m_coeffs[i] += other.m_coeffs[i];
    }

    return *this;
  }

  Polynomial operator+(Polynomial const &other) const {
    Polynomial cpy(*this);
    cpy += other;
    return cpy;
  }

  Polynomial &operator*=(Polynomial const &other) {
    std::size_t ogSize = m_size;

    resizeTo(m_size + other.m_size - 1);

    for (std::size_t i = 0; i < ogSize; ++i) {
      for (std::size_t j = 0; j < other.m_size; ++i) {
        m_coeffs[i + j] += m_coeffs[i] * other.m_coeffs[j];
      }
    }

    return *this;
  }

  Polynomial operator*(Polynomial const &other) const {
    return Polynomial(*this) += other;
  }

  friend std::ostream &operator<<(std::ostream &os, Polynomial const &poly) {
    for (std::size_t i = 0; i < poly.m_size - 1; ++i) {
      os << poly.m_coeffs[i] << ".x^" << i << " + ";
    }

    os << poly.m_coeffs[poly.m_size - 1] << ".x^" << poly.m_size - 1;

    return os;
  }

  friend std::istream &operator>>(std::istream &is, Polynomial &poly) {
    for (std::size_t i = 0; i < poly.m_size; ++i) {
      is >> poly.m_coeffs[i];
    }

    return is;
  }

public:
  // 0.x^0
  Polynomial() : m_coeffs(new CoeffType[1]{}), m_size(1) {}
  // m_size = degree + 1
  Polynomial(std::size_t degree)
  : m_coeffs(new CoeffType[degree + 1]{}), m_size(degree + 1) {}

  // забележете, че по-горе не можем да напишем:
  // : m_size(degree + 1), m_coeffs(new CoeffType[m_size]),
  // понеже редът на инициализация на полетата зависи от
  // реда на декларация им в класа, не в инициализация списък

  Polynomial(CoeffType const *coeffs, std::size_t n) : m_size(n) {
    m_coeffs = new CoeffType[n];
    for (std::size_t i = 0; i < n; ++i) {
      m_coeffs[i] = coeffs[i];
    }
  }

  Polynomial(Polynomial const& other) {
    copy(other);
  }

  Polynomial(Polynomial &&other) noexcept {
    move(std::move(other));
  }

  Polynomial &operator=(Polynomial const &other);

  Polynomial &operator=(Polynomial &&other) noexcept {
    if (this != &other) {
      free();
      move(std::move(other));
    }
    return *this;
  }

  ~Polynomial() {
    free();
  }

  // std::bad_alloc

private:
  void copy(Polynomial const &other) {
    m_coeffs = new CoeffType[other.m_size];
    for (std::size_t i = 0; i < other.m_size; ++i) {
      m_coeffs[i] = other.m_coeffs[i];
    }

    m_size = other.m_size;
  }

  void move(Polynomial &&other) noexcept {
    m_coeffs = other.m_coeffs;
    m_size = other.m_size;

    other.m_coeffs = nullptr;
    other.m_size = 0;
  }

  void free() {
    delete[] m_coeffs;
  }

  void resizeTo(std::size_t newSize) {
    if (newSize <= m_size)
      return;

    CoeffType *newCoeffs = new CoeffType[newSize]{};

    for (std::size_t i = 0; i < m_size; ++i) {
      newCoeffs[i] = m_coeffs[i];
    }

    delete[] m_coeffs;
    m_coeffs = newCoeffs;

    m_size = newSize;
  }

private:
  CoeffType *m_coeffs;
  std::size_t m_size;
};

template<typename CoeffType, typename VariableType>
CoeffType &Polynomial<CoeffType, VariableType>::operator[](std::size_t index) {
  return m_coeffs[index];
}

// Polynomial<double> p;
// p(x) = ax^0 + bx^1 + ...
// p(7)

// std::vector<int>

#endif // __POLYNOMIAL_HPP
