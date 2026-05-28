#ifndef __UNIQUE_PTR_HPP
#define __UNIQUE_PTR_HPP

#include <utility>

template<typename T>
class UniquePtr {
public:
  // *ptr = 10;
  // std::cout << *ptr;

  operator bool() const {
    return m_ptr;
  }

  T &operator*() {
    return *m_ptr;
  }

  T const &operator*() const {
    return *m_ptr;
  }

  // x->y  ~~> (*x).y
  // A *a;
  // a->foo();

  T *operator->() {
    return m_ptr;
  }

  T const *operator->() const {
    return m_ptr;
  }

  T *get() {
    return m_ptr;
  }

  T *release() {
    T *cpy = m_ptr;
    m_ptr = nullptr;
    return cpy;
  }

public:
  UniquePtr() : m_ptr(nullptr) {}

  UniquePtr(T *ptr) : m_ptr(ptr) {}

  UniquePtr(UniquePtr const &other)=delete;

  // UniquePtr && (rvalue референция) e тип
  // rvalue е value категория
  UniquePtr(UniquePtr &&other) noexcept {
    // other е локална променлива
    moveFrom(std::move(other));
  }

  UniquePtr &operator=(UniquePtr const &other)=delete;

  UniquePtr &operator=(UniquePtr &&other) noexcept {
    if (this != &other) {
      free();
      moveFrom(std::move(other));
    }
    return *this;
  }

  ~UniquePtr() {
    free();
  }

private:
  // int *ptr = new int;
  // std::bad_alloc

  // int *ptr2 = ptr;
  // ptr = nullptr;

  // void copy(UniquePtr const &);

  void moveFrom(UniquePtr &&other) noexcept {
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
  }

  void free() {
    delete m_ptr;
  }

private:
  T *m_ptr;
};

#endif
