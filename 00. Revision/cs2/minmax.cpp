#include <climits>
#include <iostream>

// array-to-pointer decay
// double *arr == double arr[]
void minmax(double *arr, unsigned n, double &min, double &max) {
  if (!arr) return;

  min = max = arr[0];  // *(arr+0) == *arr
  for (unsigned i = 1; i < n; ++i) {

    if (min > arr[i])
      min = arr[i];

    if (max < arr[i])
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

  return 0;
}
