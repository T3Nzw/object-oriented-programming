#include <cstddef>
#include <iostream>

// runtime пресмятане на числата на Фибоначи

size_t fibRec(size_t n) {
  if (n <= 1)
    return n;

  return fibRec(n-1) + fibRec(n-2);
}

// както бяхме казвали, стойностите в enum са compile-time константи,
// т.е. се знаят по време на компилация. инстанцирането на шаблоните
// с конкретни стойности също става по време на компилация, т.е.
// пресмятането на fib<N>::value също става по време на компилация

template<size_t N>
struct fib {
  enum : size_t { value = fib<N-1>::value + fib<N-2>::value };
};

template<>
struct fib<0> {
  enum : size_t{ value = 0 };
};

template<>
struct fib<1> {
  enum : size_t { value = 1 };
};

int main() {

  // сравнете времето за изпълнение и на двете извиквания

  // std::cout << fibRec(50) << '\n';

  std::cout << fib<50>::value << '\n';

  return 0;
}
