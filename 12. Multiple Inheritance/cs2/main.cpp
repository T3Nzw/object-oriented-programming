#include <array>
#include <iostream>
#include <iterator>
#include "Array.hpp"

template<typename T, typename U>
struct Pair {
  T first;
  U second;
};

using Metres = double;
typedef double Metres2;

template<typename T>
using HomPair = Pair<T, T>;

// template<typename T>
// typdef Pair<T, T> HomPair2;

void foo(int *arr) {
  std::cout << sizeof(arr) << '\n';
}

void foo(std::array<int, 3> const &arr) {
  std::cout << sizeof(arr) << '\n';
}

template<typename T, std::size_t N>
void swap(T (&arr1)[N], T (&arr2)[N]) {
  for (std::size_t i = 0; i < N; ++i) {
    std::swap(arr1[i], arr2[i]);
  }
}

int main() {

  std::array<int, 3> arr;
  foo(arr);

  int x;
  std::cin >> x;

  int y = x;

  Array<int, 3> arr2;

  HomPair<int> p{1,1};

  int arr3[5], arr4[5];
  swap(arr3, arr4);

  return 0;
}
