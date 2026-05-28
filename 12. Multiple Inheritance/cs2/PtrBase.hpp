#ifndef __PTR_BASE_HPP
#define __PTR_BASE_HPP

template<typename T>
class PtrBase {
public:
  PtrBase() : m_cblock(nullptr) {}
  PtrBase(T *data)
  : m_cblock(new ControlBlock{data, 0, 0}) {}

private:

  struct ControlBlock {
    T *data;
    unsigned sharedRefs;
    unsigned weakRefs;
  };

  ControlBlock *m_cblock;
};

#endif // __PTR_BASE_HPP
