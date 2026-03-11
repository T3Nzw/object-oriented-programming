#include <iostream>

template<typename T>
using Predicate = bool(*)(T);

template<typename T>
long long findBy(Predicate<T> pred, T *arr, size_t n) {
  for (size_t i = 0; i < n; ++i)
    if (pred(arr[i]))
      return i;

  return -1;
}

int main() {

  int arr[]{1,2,3,4,5,6,7};

  long long index = findBy<int>([](int x) { return x%2 == 0; }, arr, sizeof(arr)/sizeof(int));
  if (index > 0)
    std::cout << arr[index] << '\n';

  long long index2 = findBy<int>([](int x) { return x > 3; }, arr, sizeof(arr)/sizeof(int));
  if (index2 > 0)
    std::cout << arr[index2] << '\n';

  return 0;
}
