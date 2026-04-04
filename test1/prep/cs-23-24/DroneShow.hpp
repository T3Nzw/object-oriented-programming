#ifndef __DRONE_SHOW_HPP
#define __DRONE_SHOW_HPP

#include "Drone.hpp"

constexpr unsigned MAX_NAME_SIZE = 128;
constexpr unsigned MAX_DRONES_SIZE = 1024;

class DroneShow {
public:
  bool emptyShow() const;
  bool isEmpty(unsigned position) const;
  void play();
  // допълнителен метод за простота при тестването :)
  // иначе трябва да заделяме памет за масива drones, който подаваме
  // на параметризирания конструктор, в main функцията,
  // след което да го освободим там, което е досадно :)
  bool addDrone(Drone drone, unsigned index);

public:
  // с цел по-лесно тестване :)
  DroneShow(char const *name);
  DroneShow(char const *name, Drone const* const* drones, unsigned numberOfDrones);
  DroneShow(DroneShow const &);
  DroneShow(DroneShow &&) noexcept;
  DroneShow &operator=(DroneShow const &);
  DroneShow &operator=(DroneShow &&) noexcept;
  ~DroneShow();

private:
  void copyFrom(DroneShow const &);
  void moveFrom(DroneShow &&) noexcept;
  void free();

private:
  char m_name[MAX_NAME_SIZE];
  Drone *m_drones[MAX_DRONES_SIZE];
};

#endif // __DRONE_SHOW_HPP
