#ifndef __WINDOW_HPP
#define __WINDOW_HPP

#include <cstddef>
#include <ostream>
#include <vector>

template<typename T>
class Window {
public:
  std::vector<T> const &current() const {
    return window;
  }

  Window &operator++() {
    shift();
    return *this;
  }

  Window operator++(int) {
    Window cpy;
    ++cpy;
    return cpy;
  }

public:
  Window(std::size_t k, std::vector<T> elements)
  : index(0), k(k), elements(elements) {

    std::size_t min = std::min(k, elements.size());
    for (std::size_t i = index; i < min; ++i)
      window.push_back(elements[i]);

  }

private:
  void shift() {
    window.erase(window.begin());

    if (index + k < elements.size())
      window.push_back(elements[index + k]);

    index++;
  }

private:
  std::size_t index;
  std::size_t k;
  std::vector<T> elements;
  std::vector<T> window;
};

template<typename T>
inline std::ostream &operator<<(std::ostream &os, Window<T> const &window) {
  for (T const &el : window.current())
    os << el << ' ';
  return os;
}

#endif
