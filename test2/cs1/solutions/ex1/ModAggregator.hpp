#ifndef __MOD_AGGREGATOR_HPP
#define __MOD_AGGREGATOR_HPP

#include "Aggregator.hpp"

class ModAggregator : public Aggregator {
public:
  virtual void feed(int) override;
  virtual int aggregate() const override;

  virtual ModAggregator *clone() const override;

public:
  ModAggregator(unsigned k);

private:
  unsigned k;
  int result;
};

#endif
