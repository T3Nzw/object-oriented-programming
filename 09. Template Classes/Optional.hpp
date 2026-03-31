#ifndef __OPTIONAL_HPP
#define __OPTIONAL_HPP

// или имаме стойност, или нямаме
template<typename T>
class Optional {
public:
  bool hasValue() const {
    return m_elem;
  }

  T &getValue() {
    return *m_elem;
  }

  T const &getValue() const {
    return *m_elem;
  }

public:
  Optional();
  Optional(T const &data);
  Optional(Optional const &);
  Optional &operator=(Optional const &);
  ~Optional();

private:
  // само един елемент
  T *m_elem;
};

template<typename T>
Optional<T>::Optional() : m_elem(nullptr) {}

template<typename T>
Optional<T>::Optional(T const &data)
: m_elem(new T(data)) {}


#endif // __OPTIONAL_HPP
