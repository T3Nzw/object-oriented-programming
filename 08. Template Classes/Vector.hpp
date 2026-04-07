#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <cstddef>
#include <iostream>
#include <stdexcept>

template<typename T>
class Vector {
private:
  class Iterator {
  public:
    // не притежаваме ресурса, който се сочи от m_curr
    Iterator(T *curr) : m_curr(curr) {}

    Iterator &operator++() {
      ++m_curr;
      return *this;
    }

    // ==
    bool operator!=(Iterator const &other) const {
      return m_curr != other.m_curr;
    }

    // *it = 4;
    T &operator*() {
      return *m_curr;
    }

    T const &operator*() const {
      return *m_curr;
    }

  private:
    T *m_curr;
  };

public:
  using iterator = Iterator;

  iterator begin() {
    return Iterator(m_arr);
  }

  Iterator end() {
    return Iterator(m_arr + m_size);
  }

  Iterator begin() const {
    return Iterator(m_arr);
  }

  Iterator end() const {
  return Iterator(m_arr + m_size);
  }

  bool empty() const {
    return m_size == 0;
  }

  operator bool() const {
    return !empty();
  }

  size_t size() const {
    return m_size;
  }

  void print(std::ostream &os=std::cout) const {
    for (size_t i = 0; i < m_size; ++i)
      os << m_arr[i] << ' ';
  }

  void push_back(T const &el) {
    if (m_size >= m_capacity) {
      resize();
    }

    m_arr[m_size++] = el;
  }

  T pop_back() {
    m_size--;
    // before resize: [1,2,3,4]
    // after resize: [1,2,3,4,.....]
    return m_arr[m_size];
  }

  T &operator[](size_t index) {
    return m_arr[index];
  }

  T const &operator[](size_t index) const {
    return m_arr[index];
  }

  T &at(size_t index) {
    if (index >= m_size) {
      throw std::out_of_range("index out of range");
    }
    return (*this)[index];
  }

  T const &at(size_t index) const {
    if (index >= m_size) {
      throw std::out_of_range("index out of range");
    }
    return (*this)[index];
  }

public:
  Vector() : m_arr(nullptr), m_size(0), m_capacity(0) {}

  Vector(Vector const &other) {
    copy(other);
  }

  Vector &operator=(Vector const &other) {
    if (this != &other) {
      free();
      copy(other);
    }
    return *this;
  }

  ~Vector() { free(); }

private:
  void copy(Vector const &other) {
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    m_arr = new T[m_capacity];
    for (size_t i = 0; i < m_size; ++i) {
      m_arr[i] = other.m_arr[i];
    }
  }

  void free() {
    delete[] m_arr;
  }

  void resize() {
    // m_capacity == 0, 0 * n = 0
    m_capacity = m_capacity > 0 ? m_capacity * 2 : 1;

    T *newArr = new T[m_capacity];
    for (size_t i = 0; i < m_size; ++i)
      newArr[i] = m_arr[i];

    delete[] m_arr;
    m_arr = newArr;
  }

private:
  T *m_arr;
  size_t m_size;
  size_t m_capacity;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, Vector<T> const &v) {
  v.print(os);
  return os;
}

#endif // __VECTOR_HPP
