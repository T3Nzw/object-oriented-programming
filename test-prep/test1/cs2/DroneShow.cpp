#include "DroneShow.hpp"
#include "Drone.hpp"

#include <cstdlib>
#include <cstring>
#include <cassert>

bool DroneShow::isEmpty(unsigned position) const {
  if (position >= MAX_DRONES_SIZE)
    return true;

  return !m_drones[position];
}

void DroneShow::play() {

  // murzi me

}

DroneShow::DroneShow(char const *name, Drone const *const *drones, unsigned numberOfDrones)
: m_drones{} {

  assert(strlen(name) < MAX_NAME_SIZE);
  assert(numberOfDrones <= MAX_DRONES_SIZE);

  strcpy(m_name, name);

  for (unsigned i = 0; i < numberOfDrones; ++i) {
    if (drones[i])
      m_drones[i] = new Drone(*drones[i]);
  }
}

DroneShow::DroneShow(DroneShow const &other) {
  copyFrom(other);
}

DroneShow::DroneShow(DroneShow &&other) noexcept {
  moveFrom(std::move(other));
}

DroneShow &DroneShow::operator=(DroneShow const &other) {
  if (this != &other) {
    free();
    copyFrom(other);
  }
  return *this;
}

DroneShow &DroneShow::operator=(DroneShow &&other) noexcept {
  if (this != &other) {
    free();
    moveFrom(std::move(other));
  }
  return *this;
}

DroneShow::~DroneShow() {
  free();
}

void DroneShow::copyFrom(DroneShow const &other) {
  strcpy(m_name, other.m_name);

  for (unsigned i = 0; i < MAX_DRONES_SIZE; ++i) {
    if (other.m_drones[i])
      m_drones[i] = new Drone(*other.m_drones[i]);
    else
      m_drones[i] = nullptr;
  }
}

void DroneShow::moveFrom(DroneShow &&other) noexcept {
  strcpy(m_name, other.m_name);
  strcpy(other.m_name, "");

  for (unsigned i = 0; i < MAX_DRONES_SIZE; ++i) {
    m_drones[i] = other.m_drones[i];
    other.m_drones[i] = nullptr;
  }
}

void DroneShow::free() {
  for (unsigned i = 0; i < MAX_DRONES_SIZE; ++i)
    delete m_drones[i];
}
