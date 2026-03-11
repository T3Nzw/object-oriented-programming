#include <iostream>

template<typename T, typename U>
using UnaryFunction = U(*)(T);

// map има свойството, че запазва размера на контейнера
template<typename T, typename U>
U *map(UnaryFunction<T, U> f, T *arr, size_t n) {
  U *result = new U[n];

  for (size_t i = 0; i < n; ++i)
    result[i] = f(arr[i]);

  return result;
}

// по принцип е най-безопасно да не се връщат масиви,
// а обекти, които съдържат масив, размер и капацитет (вектори)

template<typename T>
void print(T *arr, size_t n) {
  for (size_t i = 0; i < n; ++i)
    std::cout << arr[i] << ' ';
}

int main() {

  int arr[]{1,2,3,4};

  // имаме предвид, че map винаги връща динамично заделен масив!
  int *doubled = map<int, int>([](int x) { return x*2; }, arr, 4);
  print(doubled, 4);

  std::cout << '\n';

  char *toASCII = map<int, char>([](int x) { return static_cast<char>(x + '0'); }, arr, 4);
  print(toASCII, 4);

  delete[] doubled;
  delete[] toASCII;

  return 0;
}
