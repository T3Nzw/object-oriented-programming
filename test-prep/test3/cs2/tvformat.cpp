#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>


class Person {};

template<std::size_t PARTICIPANTS, std::size_t EVENTS>
class TVFormat {
public:

private:
  Person *participants[PARTICIPANTS];
  Person *host;
  char *events[EVENTS];
};

class FMIChallenge : public TVFormat<14, 10> {
public:
  
};

int main() {

  return 0;
}
