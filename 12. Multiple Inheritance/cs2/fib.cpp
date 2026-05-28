#include <iostream>

using ullong = unsigned long long;

ullong fib(ullong n) {
  if (n <= 1) {
    return n;
  }

  return fib(n-1) + fib(n-2);
}

template<typename T>
void foo() {
  std::cout << "typename T\n";
}

template<>
void foo<int>() {
  std::cout << "int\n";
}

template<ullong N>
struct Fib {
  enum {
    value = Fib<N-1>::value + Fib<N-2>::value
  };
};

template<>
struct Fib<0> {
  enum {
    value = 0
  };
};

template<>
struct Fib<1> {
  enum {
    value = 1
  };
};

template<>
struct Fib<2> {
  enum {
    value = Fib<1>::value + Fib<0>::value
  };
};

int main() {

  // std::cout << fib(100) << '\n';

  foo<char>();
  foo<int>();

  std::cout << Fib<45>::value << '\n';

  return 0;
}
