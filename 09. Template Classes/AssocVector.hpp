#ifndef __ASSOC_VECTOR_HPP
#define __ASSOC_VECTOR_HPP

#include "Optional.hpp"
#include "Vector.hpp"
#include <cstddef>

template<typename T, typename U>
struct Pair {
  T first;
  U second;
};

template<typename T, typename U>
bool operator==(Pair<T, U> const &p1, Pair<T, U> const &p2) {
  return p1.first == p2.first;
}

template<typename K, typename V>
class AssocVector {
public:
  bool hasKey(K const &key) const {
    return lookup(key).hasValue();
  }

  void addPair(Pair<K,V> const &pair) {
    for (size_t i = 0; i < vec.size(); ++i) {
      if (vec[i] == pair) {
        vec[i].second = pair.second;
        return;
      }
    }
    vec.push_back(pair);
  }

  Optional<V> lookup(K const &key) const {
    for (size_t i = 0; i < vec.size(); ++i) {
      if (vec[i].first == key)
        return Optional<V>(vec[i].second);
    }
    return Optional<V>();
  }

private:
  Vector<Pair<K,V> > vec;
};

#endif // __ASSOC_VECTOR_HPP
