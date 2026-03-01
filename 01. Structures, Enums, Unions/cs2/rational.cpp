#include <iostream>
#include <cassert>

struct Rational {
  int numer, denom;
};

void print(Rational const &rat) {
  std::cout << rat.numer << "/" << rat.denom;
}

int gcd(int a, int b) {
  if (a < b)
    std::swap(a, b);

  while (b != 0) {
    int rem = a % b;
    a = b;
    b = rem;
  }

  return a;
}

void simplifyMutable(Rational &rat) {
  int gcdRat = gcd(rat.numer, rat.denom);
  rat.numer /= gcdRat;
  rat.denom /= gcdRat;

  if (rat.numer < 0 && rat.denom < 0
   || rat.numer > 0 && rat.denom < 0) {

    rat.numer *= -1;
    rat.denom *= -1;
  }
}

Rational simplify(Rational const &rat) {
  int gcdRat = gcd(rat.numer, rat.denom);
  Rational result{rat.numer / gcdRat, rat.denom / gcdRat};

  if (result.numer < 0 && result.denom < 0
   || result.numer > 0 && result.denom < 0) {

    result.numer *= -1;
    result.denom *= -1;
  }

  return result;

  // или използвайки предишната функция
  // Rational cpy = rat;
  // simplifyMutable(cpy);
  // return cpy;
}

Rational mkRat(int numer, int denom) {
  assert(denom != 0);

  Rational rat{numer, denom};
  simplifyMutable(rat);

  return rat;
}

Rational add(Rational const &rat1, Rational const &rat2) {
  int numer = rat1.numer * rat2.denom + rat2.numer * rat1.denom;
  int denom = rat1.denom * rat2.denom;

  // .<поле> е името на полето, а отдясно стои стойността
  // трябва да са в същия ред, в който са дефинирани в класа
  return simplify({ .numer = numer, .denom = denom });
}

int main() {

  Rational rat = mkRat(-2, -4);
  Rational rat2 = mkRat(1, 2);

  print(rat);
  std::cout << '\n';

  print(rat2);
  std::cout << '\n';

  print(add(rat, rat2));
  std::cout << '\n';

  return 0;
}
