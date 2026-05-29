#include "MaxAggregator.hpp"
#include <limits>
#include <algorithm>

void MaxAggregator::feed(int value) {
  currMax = std::max(currMax, value);
}

int MaxAggregator::aggregate() const {
  return currMax;
}

MaxAggregator *MaxAggregator::clone() const {
  return new MaxAggregator(*this);
}

MaxAggregator::MaxAggregator()
: currMax(std::numeric_limits<int>::min()) {}
