#include <iostream>

template<typename T>
void print(T x) {
  T y = x;
  std::cout << x;
}

void print(double x) {
  double y = x;
  std::cout << x;
}

void print(int x) {
  int y = x;
  std::cout << x;
}

template<typename T>
struct DynArray {
  T *arr;
  unsigned size, capacity;
};

template<typename T, typename U>
struct Pair {
  T first;
  U second;
};

template<typename T>
constexpr T PI = 3.14;

int main() {

  // print<double>(4);
  // print<int>(4);

  DynArray<int> dyn;

  Pair<int, char> p{1, 'c'};
  Pair<int, int> p2{4, 5};

  std::cout << PI<double> << ' ' << PI<int>;

  return 0;
}
