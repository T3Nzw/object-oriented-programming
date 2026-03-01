#include <climits>
#include <cmath>
#include <iostream>

constexpr double EPSILON = 1e-12;

int cmp(double a, double b) {
  double diff = a - b;

  if (std::fabs(diff) < EPSILON)
    return 0;

  if (diff > 0)
    return 1;

  else
    return -1;
}

// array-to-pointer decay
// double *arr == double arr[]
void minmax(double *arr, unsigned n, double &min, double &max) {
  if (!arr) return;

  min = max = arr[0];  // *(arr+0) == *arr
  for (unsigned i = 1; i < n; ++i) {

    if (cmp(arr[i], min) == -1)
      min = arr[i];

    if (cmp(arr[i], max) == 1)
      max = arr[i];

  }
}

double arr3[3];

int main() {

  double arr[] = {1,2,3.14};

  unsigned n;
  std::cin >> n;
  double *arr2 = new double[n];

  // можем да подадем и двата "вида" масиви
  // minmax(arr);
  // minmax(arr2);

  double min, max;
  minmax(arr, sizeof(arr)/sizeof(double), min, max);

  std::cout << min << ' ' << max << '\n';

  delete[] arr2;

  return 0;
}
