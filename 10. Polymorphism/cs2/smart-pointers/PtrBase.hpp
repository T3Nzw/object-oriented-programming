#ifndef __PTR_BASE_HPP
#define __PTR_BASE_HPP

// обикновено двата класа WeakPtr и SharedPtr имат различна
// семантика за притежание над ресурсите, така че не се прави наследяване.
// тук го демонстрираме, за да видим как работи наследяването на шаблони на класове

#include <utility>

template<typename T>
class PtrBase {
public:
  // T *ptr = nullptr;
  // ptr->foo();

  // int *x = nullptr;
  // *x

  T &operator*() {
    // if (!m_controlBlock || !m_controlBlock->ptr)
    //   throw std::runtime_error("pointer is null");
    return *m_controlBlock->ptr;
  }

  T const &operator*() const {
    return *m_controlBlock->ptr;
  }

  T *operator->() {
    if (m_controlBlock)
      return m_controlBlock->ptr;

    return nullptr;
  }

  T const *operator->() const {
    if (m_controlBlock)
      return m_controlBlock->ptr;

    return nullptr;
  }

  // pb.get()
  // pb.operator->()

  T *get() const {
    return m_controlBlock->ptr;
  }

  operator T*() const {
    return get();
  }

  unsigned getSharedRefs() const {
    if (!m_controlBlock)
      return 0;

    return m_controlBlock->sharedRefs;
  }

  unsigned getWeakRefs() const {
    if (!m_controlBlock)
      return 0;

    return m_controlBlock->weakRefs;
  }

public:
  PtrBase() : m_controlBlock(nullptr) {}

  PtrBase(PtrBase const &other) {
    copy(other);
  }

  PtrBase(PtrBase &&other) noexcept {
    move(std::move(other));
  }

  PtrBase &operator=(PtrBase const &other) {
    if (this != &other) {
      free();
      copy(other);
    }
    return *this;
  }

  PtrBase &operator=(PtrBase &&other) noexcept {
    if (this != &other) {
      free();
      move(std::move(other));
    }
    return *this;
  }

  ~PtrBase() {
    free();
  }

protected:
  PtrBase(T const &data)
  : m_controlBlock(new ControlBlock{new T(data),0,0}) {}

  PtrBase(T *data)
  : m_controlBlock(new ControlBlock{data,0,0}) {}


protected:
  void copy(PtrBase const &other) {
    // shallow copy
    m_controlBlock = other.m_controlBlock;
  }

  void move(PtrBase &&other) noexcept {
    m_controlBlock = other.m_controlBlock;
    other.m_controlBlock = nullptr;
  }

  void free() {
    if (getSharedRefs() == 0 && getWeakRefs() == 0)
      delete m_controlBlock;
  }

  void incSharedRefs() {
    if (!m_controlBlock)
      return;

    m_controlBlock->sharedRefs++;
  }

  void decSharedRefs() {
    if (!m_controlBlock || m_controlBlock->sharedRefs == 0)
      return;

    m_controlBlock->sharedRefs--;
  }

  void incWeakRefs() {
    if (!m_controlBlock)
      return;

    m_controlBlock->weakRefs++;
  }

  void decWeakRefs() {
    if (!m_controlBlock || m_controlBlock->weakRefs == 0)
      return;

    m_controlBlock->weakRefs--;
  }

protected:
  struct ControlBlock {
    T *ptr;
    unsigned sharedRefs;
    unsigned weakRefs;
  } *m_controlBlock;
};

#endif
