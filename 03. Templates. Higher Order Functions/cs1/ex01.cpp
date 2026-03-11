#include <cstring>
#include <iostream>
#include <cmath>
#include <limits>

template<typename T>
bool equal(T const &a, T const &b) {
  std::cout << "default\n";
  return a == b;
}

template<>
bool equal<double>(double const &a, double const &b) {
  double diff = std::fabs(a - b);
  return diff < std::numeric_limits<double>::epsilon();
}

template<>
bool equal<float>(float const &a, float const &b) {
  double diff = std::fabs(a - b);
  return diff < std::numeric_limits<float>::epsilon();
}

// specialisation
template<>
bool equal<char*>(char *const &a, char *const &b) {
  std::cout << "str\n";
  return !strcmp(a, b);
}

// overloading
bool equal(char const *a, char const *b) {
  std::cout << "overloaded function\n";
  return !strcmp(a, b);
}

int main() {

  // std::cout << equal<float>(0.1 + 0.2, 0.3);

  // char[] -> char *
  // char * -> char const *
  char str[] = "abcd";
  char str2[] = "abcd";
  std::cout << equal(str, str2);

  // char const[] -> char const *
  char const str3[] = "abcd";
  char const str4[] = "abcd";
  std::cout << equal(str3, str4);

  // char *str1 = new char[3]{"ab"};
  // std::cout << equal(str1, str1);
  // delete[] str1;

  return 0;
}
