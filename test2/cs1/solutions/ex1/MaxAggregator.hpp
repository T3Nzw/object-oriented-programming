#ifndef __MAX_AGGREGATOR_HPP
#define __MAX_AGGREGATOR_HPP

#include "Aggregator.hpp"
#include <limits>

class MaxAggregator : public Aggregator {
public:
  virtual void feed(int) override;
  virtual int aggregate() const override;

  virtual MaxAggregator *clone() const override;

public:
  MaxAggregator();

private:
  int currMax;
};

#endif
