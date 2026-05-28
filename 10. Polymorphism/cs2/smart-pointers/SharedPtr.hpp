#ifndef __SHARED_PTR_HPP
#define __SHARED_PTR_HPP

#include "PtrBase.hpp"

template<typename T> class SharedPtr;

template<typename T, typename... Args>
inline SharedPtr<T> makeShared(Args&&... args) {
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
class SharedPtr : public PtrBase<T> {
public:
  SharedPtr()=default;

  explicit SharedPtr(T const &data)
  : PtrBase<T>(data) {
    this->incSharedRefs();
  }

  explicit SharedPtr(T *data)
  : PtrBase<T>(data) {
    this->incSharedRefs();
  }

  SharedPtr(SharedPtr const &other)
  : PtrBase<T>(other) {
    this->incSharedRefs();
  }

  SharedPtr(SharedPtr &&other) noexcept
  : PtrBase<T>(std::move(other)) {}

  SharedPtr &operator=(SharedPtr const &other) {
    if (this != &other) {
      free();
      PtrBase<T>::operator=(other);
      this->incSharedRefs();
    }
    return *this;
  }

  SharedPtr &operator=(SharedPtr &&other) noexcept {
    if (this != &other) {
      free();
      PtrBase<T>::operator=(std::move(other));
    }
    return *this;
  }

  ~SharedPtr() {
    free();
  }

private:
  void free() {
    this->decSharedRefs();

    if (this->m_controlBlock && this->getSharedRefs() == 0)
      delete this->m_controlBlock->ptr;
  }
};

#endif
