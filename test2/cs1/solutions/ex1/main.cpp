#include <iostream>
#include "Aggregator.hpp"
#include "MaxAggregator.hpp"
#include "ModAggregator.hpp"
#include "CustomAggregator.hpp"

int main() {

  CustomAggregator *e = new CustomAggregator(0, [](int a, int b) { return a + b; });
  std::cout << aggregateSeq({5,5,10}, e) << '\n';

  ModAggregator *m = new ModAggregator(10);
  std::cout << aggregateSeq({12,15,10}, m) << '\n';

  MaxAggregator *mx = new MaxAggregator();
  std::cout << aggregateSeq({-1,-4,-2,-35}, mx) << '\n';

  delete e;
  delete m;
  delete mx;

  return 0;
}
