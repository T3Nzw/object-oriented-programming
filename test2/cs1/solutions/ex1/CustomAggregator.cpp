#include "CustomAggregator.hpp"
#include <functional>

void CustomAggregator::feed(int value) {
  acc = op(acc, value);
}

int CustomAggregator::aggregate() const {
  return acc;
}

CustomAggregator *CustomAggregator::clone() const {
  return new CustomAggregator(*this);
}

CustomAggregator::CustomAggregator(int initVal, std::function<int(int,int)> op)
: acc(initVal), op(op) {}
