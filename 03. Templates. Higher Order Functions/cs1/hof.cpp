#include <iostream>

// typedef <old> <new>
typedef unsigned Metres;
typedef int (*BinaryOpInt)(int, int);

// using <new> = <old>;
using Feet = unsigned;
using BinaryOpInt2 = int(*)(int, int);

// само с using
template<typename T>
using BinaryOp = T(*)(T, T);

int apply(BinaryOp<int> f, int x, int y) {
  return f(x, y);
}

int add(int x, int y) {
  return x + y;
}

int sub(int x, int y) {
  return x - y;
}

BinaryOp<int> toOp(char symbol) {
  switch (symbol) {
    case '+': return add;
    case '-': return sub;
    // ламбда-функция
    case '*': return [](int x, int y){ return x * y; };
  }

  throw 1;
}

int main() {

  // add -> &add
  // &add -> add
  // std::cout << apply(add, 1, 2);

  add(1, 2);
  (&add)(1, 2);

  std::cout << toOp('+')(1,2);

  return 0;
}
