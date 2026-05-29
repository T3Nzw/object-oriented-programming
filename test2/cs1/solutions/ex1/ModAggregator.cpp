#include "ModAggregator.hpp"
#include <stdexcept>

void ModAggregator::feed(int value) {
  result += value % k;
}

int ModAggregator::aggregate() const {
  return result;
}

ModAggregator *ModAggregator::clone() const {
  return new ModAggregator(*this);
}

ModAggregator::ModAggregator(unsigned k)
: k(k) {
  if (k == 0)
    throw std::invalid_argument("division by zero");
}
