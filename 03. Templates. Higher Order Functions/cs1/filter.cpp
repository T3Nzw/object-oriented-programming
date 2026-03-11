#include <cstddef>
#include <iostream>

template<typename T>
using Predicate = bool(*)(T);

// брой на елементите, които удовлетворяват дадения предикат
template<typename T>
size_t count(Predicate<T> pred, T *arr, size_t n) {
  size_t result = 0;

  for (size_t i = 0; i < n; ++i)
    if (pred(arr[i]))
      result++;

  return result;
}

// отново, тук е най-удобно, ако масивът и размерът са обединени в структура
template<typename T>
T *filter(Predicate<T> pred, T *arr, size_t n, size_t &newSize) {

  newSize = count(pred, arr, n);
  T *result = new T[newSize];

  for (size_t i = 0, fi = 0; i < n; ++i) {
    if (pred(arr[i]))
      result[fi++] = arr[i];
  }

  return result;
}

template<typename T>
void print(T *arr, size_t n) {
  for (size_t i = 0; i < n; ++i)
    std::cout << arr[i] << ' ';
}

int main() {

  int arr[]{1,2,3,4,5,6,7,8,9,10};

  size_t evenSize;
  int *evens = filter<int>([](int x) { return x%2 == 0; }, arr, 10, evenSize);

  print(evens, evenSize);

  delete[] evens;

  return 0;
}
