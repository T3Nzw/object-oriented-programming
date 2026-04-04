#include "DroneShow.hpp"
#include "Drone.hpp"

#include <cstdlib>
#include <cstring>
#include <cassert>
#include <utility>
#include <iostream>

bool DroneShow::emptyShow() const {
  for (unsigned i = 0; i < MAX_DRONES_SIZE; ++i)
    if (m_drones[i])
      return false;

  return true;
}

bool DroneShow::isEmpty(unsigned position) const {
  if (position >= MAX_DRONES_SIZE)
    return true;

  return !m_drones[position];
}

void DroneShow::play() {
  if (emptyShow())
    return;

  // този начин е сравнително гнусен,
  // но въпреки това демонстрира обработка на изключения :)
  while (true) {

    try {

      for (unsigned i = 0; i < MAX_DRONES_SIZE; ++i) {
        if (m_drones[i]) {
          // слагаме това най-отгоре, защото то хвърля грешка.
          // в противен случай ще извикаме getName(), ще принтираме името,
          // но може moveWithOneStep да хвърли грешка и да сме принтирали името напразно
          Coordinates coords = m_drones[i]->moveWithOneStep();

          std::cout << m_drones[i]->getName() << ": ";
          coords.print();
          std::cout << std::endl;
        }
      }

    }
    catch (...) {
      return;
    }

  }
}

bool DroneShow::addDrone(Drone drone, unsigned index) {
  if (index >= MAX_DRONES_SIZE)
    return false;

  m_drones[index] = new Drone(std::move(drone));
  return true;
}

// инициализацията на m_drones тук е ключова!

DroneShow::DroneShow(char const *name) : m_drones{} {
  assert(strlen(name) < MAX_NAME_SIZE);
  strcpy(m_name, name);
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
