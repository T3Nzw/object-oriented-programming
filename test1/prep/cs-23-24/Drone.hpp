#ifndef __DRONE_HPP
#define __DRONE_HPP

constexpr unsigned MAX_FILENAME_SIZE = 64;

struct Coordinates {
  double x, y;

  void print() const;
};

class Drone {
public:
  char const *getName() const;
  void printGeneratedPath() const;
  Coordinates moveWithOneStep();

public:
  Drone(char const *name, char const *filename, unsigned position);
  Drone(Drone const &);
  Drone(Drone &&) noexcept;
  Drone &operator=(Drone const &);
  Drone &operator=(Drone &&) noexcept;
  ~Drone();

private:
  void copy(Drone const &);
  void move(Drone &&);
  void free();

private:
  char *m_name;
  char m_filename[MAX_FILENAME_SIZE];
  unsigned m_position;
};

#endif // __DRONE_HPP
