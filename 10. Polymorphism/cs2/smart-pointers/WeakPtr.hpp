#ifndef __WEAK_PTR_HPP
#define __WEAK_PTR_HPP

#include "PtrBase.hpp"

template<typename T> class SharedPtr;

template<typename T>
class WeakPtr : public PtrBase<T> {
public:
  bool valid() const {
    return this->getSharedRefs() != 0;
  }

  SharedPtr<T> lock() const {
    throw 1;
  }

public:
  WeakPtr()=default;

  WeakPtr(SharedPtr<T> const &sp)
  : PtrBase<T>(sp) {
    this->incWeakRefs();
  }

  WeakPtr(WeakPtr const &data)
  : PtrBase<T>(data) {
    this->incWeakRefs();
  }

  WeakPtr(WeakPtr &&other) noexcept
  : PtrBase<T>(std::move(other)) {}

  WeakPtr &operator=(WeakPtr const &other) {
    if (this != &other) {
      PtrBase<T>::operator=(other);
      this->incWeakRefs();
    }
    return *this;
  }

  WeakPtr &operator=(WeakPtr &&other) noexcept {
    if (this != &other) {
      PtrBase<T>::operator=(std::move(other));
    }
    return *this;
  }

  ~WeakPtr() {
    this->decWeakRefs();
  }
};


#endif
