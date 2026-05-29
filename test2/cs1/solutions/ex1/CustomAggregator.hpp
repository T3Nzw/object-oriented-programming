#ifndef __CUSTOM_AGGREGATOR_HPP
#define __CUSTOM_AGGREGATOR_HPP

#include "Aggregator.hpp"
#include <functional>

class CustomAggregator : public Aggregator {
public:
  virtual void feed(int) override;
  virtual int aggregate() const override;

  virtual CustomAggregator *clone() const override;

public:
  CustomAggregator(int initVal, std::function<int(int,int)> op);

private:
  std::function<int(int,int)> op;
  int acc;
};

#endif
