#ifndef __AGGREGATOR_HPP
#define __AGGREGATOR_HPP

#include <stdexcept>
#include <vector>
class Aggregator {
public:
  virtual void feed(int)=0;
  virtual int aggregate() const=0;

  virtual Aggregator *clone() const=0;

  virtual ~Aggregator()=default;
};

inline int aggregateSeq(std::vector<int> const &seq, Aggregator *evaluator) {
  if (!evaluator)
    throw std::runtime_error("invalid aggregator");

  for (int el : seq)
    evaluator->feed(el);

  return evaluator->aggregate();
}

#endif
