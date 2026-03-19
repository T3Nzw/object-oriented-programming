#include <iostream>
#include "String.hpp"

// top-level const-qualifier
// т.е. при наличие на указател/референция,
// const, който е максимално вдясно, се нарича
// top-level const-qualifier,
// напр. int *const, int **const, int const
// и др.
int *const foo(int const x) {
  return nullptr;
}

// top-level const-qualifier-ите нямат значение
// при параметрите на функции и типа на връщаните резултати.
// тоест, 1. дали ще напишем int const x или int x, няма значение
// и долната функция се счита за редефиниция на горната;
// и 2. това, че функцията връща константен указател,
// няма значение за това на какво го присвояваме,
// тъй като просто копираме стойността, т.е.
// int *ptr = foo(4); е валидно

// int *const foo(int x) {
  // return nullptr;
// }

// bottom-level const-qualifiers -
// намират се вляво от указател/референция,
// напр. int const *, int const & и др.
// и забраняват промяната на обекта, към който сочат.
// долните два функции са различни, понеже bottom-level
// const-qualifier-ите правят разлика при типовете на параметрите

void bar(int &x) {}
void bar(int const &x) {}

// така се имплементира std::swap в стандартната библиотека
// с цел избягване на излишни копия (напр. за String класа, който написахме).
// ако няма дефинирани move семантики, се използват копиращите семантики
template<typename T>
void swap(T &a, T &b) {
  T tmp = std::move(a);
  a = std::move(b);
  b = std::move(tmp);
}

int main() {

  String const s;

  std::cout << std::boolalpha;
  std::cout << s.empty() << '\n';

  String s2("abcd");

  // s2.c_str()[1] = '\0';

  s2.push_back('1');

  s2.print();
  std::cout << '\n';

  s2.append("23");

  s2.print();
  std::cout << '\n';

  int x = 10;
  int &y = x;
  int const &z = y;
  int const &t = 7;

  // 8: prvalue
  int &&rvalueRef1 = 8;
  // std::move(x): xvalue
  int &&rvalueRef2 = std::move(x);

  String s3 = std::move(s2);

  s2.print();
  s2.empty();

  String s4("123");

  s4 = std::move(s4);

  String s5("427");

  swap(s4, s5);

  return 0;
}
