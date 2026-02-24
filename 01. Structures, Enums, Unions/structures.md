# Големина на структура

В следните примери приемаме, че:

- `sizeof(double) == 8`, `sizeof(int) == 4`, `sizeof(bool) == 1`;
- `alignof(double) == 8`, `alignof(int) == 4`, `alignof(bool) == 1`.

За всяка от следните структури да се определи нейната големина
и разположението на данните в паметта (т.е. ако има padding, къде е той,
как са подравнени данните и т.н.):

1.
```cpp
struct Empty {};

struct Foo {
  char c;
  int i;
};

struct Bar {
  int i;
  char c;
};
```

2.
```cpp
struct Baz {
  char c1;
  double d;
  char c2;
  int i;
};
```

Как би изглеждала най-оптималната откъм памет дефиниция на горната структура?

3.
```cpp
struct Qux {
  bool b1, b2;
  char arr[4];
};
```

4.
```cpp
struct Quux {
  Qux qux;  // от 3-тия пример
  int i;
};
```

5.
```cpp
struct Corge {
  Quux quxs[3];
  Corge *corgePtr, &corgeRef;
  char c;
  int i;
};
```
