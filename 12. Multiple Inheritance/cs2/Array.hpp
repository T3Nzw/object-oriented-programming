#ifndef __ARRAY_HPP
#define __ARRAY_HPP

#include <cstddef>
#include <utility>

template<typename T, std::size_t SIZE>
class Array {
public:
  using elem_type = T;
  typedef T elem_type2;

public:
  T &operator[](std::size_t index) {
    return m_arr[index];
  }

  T const &operator[](std::size_t index) const {
    return m_arr[index];
  }

  std::size_t size() const {
    return SIZE;
  }

  void swap(Array &other) {
    std::swap(m_arr, other.m_arr);
  }

  // arr1.swap(arr2);

public:
  Array() : m_arr() {}

private:
  T m_arr[SIZE];
};

#endif // __ARRAY_HPP
