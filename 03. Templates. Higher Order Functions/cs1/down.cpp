#include <iostream>

enum class Ordering { LT, EQ, GT };

template<typename T>
struct Down {
  T value;
};

template<typename T>
Ordering compare(T const &value1, T const &value2) {
  if (value1 < value2)       return Ordering::LT;
  else if (value1 == value2) return Ordering::EQ;
  else                       return Ordering::GT;
}

template<typename T>
Ordering compare(Down<T> const &d1, Down<T> const &d2) {
  switch (compare(d1.value, d2.value)) {
    case Ordering::LT: return Ordering::GT;
    case Ordering::EQ: return Ordering::EQ;
    case Ordering::GT: return Ordering::LT;
  }

  throw "what?";
}

template<typename T>
void sort(T *arr, size_t n) {
  for (size_t i = 1; i < n; ++i) {

    T key = arr[i];
    long long j = i - 1;

    while (j >= 0 && compare(key, arr[j]) == Ordering::LT) {
      arr[j+1] = arr[j];
      j--;
    }

    arr[j+1] = key;
  }
}

template<typename T, typename U>
U *map(U (*f)(T), T *arr, size_t n) {
  U *result = new U[n];

  for (size_t i = 0; i < n; ++i)
    result[i] = f(arr[i]);

  return result;
}

int main() {

  int arr[]{1,2,3,4,5,6,7,8,9,10};
  Down<int> *dint = map<int, Down<int> >([](int x) { return Down<int>{x}; }, arr, 10);

  sort(dint, 10);

  for (size_t i = 0; i < 10; ++i)
    std::cout << dint[i].value << ' ';

  delete[] dint;

  return 0;
}
