#include <iostream>

static int x = 0;

void foo() {
  static int x = 0;

  std::cout << x << std::endl;
  x++;
}

class Counter {
public:
  static unsigned getCnt() {
    return cnt;
  }

public:
  Counter() {
    cnt++;
  }

  Counter(int) {
    cnt++;
  }

  Counter(Counter const &) {
    cnt++;
  }

  ~Counter() {
    cnt--;
  }

private:
  static unsigned cnt;
};

unsigned Counter::cnt = 0;

int main() {

  foo();
  foo();

  Counter *c1;
  std::cout << Counter::getCnt() << std::endl;

  {
    Counter *c2 = new Counter();
    c1 = new Counter(*c1);

    std::cout << Counter::getCnt() << std::endl;

    delete c2;
  }

  delete c1;

  std::cout << Counter::getCnt() << std::endl;

  return 0;
}
