#ifndef __DRONE_HPP
#define __DRONE_HPP

#include <ios>
constexpr unsigned MAX_FILENAME_SIZE = 64;

struct Coordinates {
  double x, y;

  void print() const;
};

class Drone {
public:
  void printGeneratedPath() const;
  Coordinates moveWithOneStep();

public:
  Drone(char const *name, char const *filename, std::streamsize position);
  Drone(Drone const &);
  Drone(Drone &&) noexcept;
  Drone &operator=(Drone const &);
  Drone &operator=(Drone &&) noexcept;
  ~Drone();

private:
  void copyFrom(Drone const &other);
  void moveFrom(Drone &&other);
  void free();

private:
  char *m_name;
  char m_filename[MAX_FILENAME_SIZE];
  std::streamsize m_position;
};

#endif // __DRONE_HPP
