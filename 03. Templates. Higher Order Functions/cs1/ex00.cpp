#include <fstream>
#include <iostream>

template<typename T>
T max(T const &a, T const &b) {
  if (a < b) return b;
  return a;
}

template<typename T>
void print(T *arr, size_t n, std::ostream &os) {
  for (size_t i = 0; i < n; ++i)
    os << arr[i] << ' ';
}

template<typename T>
T *fill(size_t n, T const &x) {
  T *result = new T[n];

  for (size_t i = 0; i < n; ++i)
    result[i] = x;

  return result;
}

int main() {

  int arr[4]{1,2,3,4};
  print(arr, 4, std::cout);

  std::ofstream ofs("filename.txt", std::ios::out);
  if (ofs) {
    print(arr, 4, ofs);
    ofs.close();
  }

  int *arr2 = fill<int>(10, 1);

  delete[] arr2;

  return 0;
}
