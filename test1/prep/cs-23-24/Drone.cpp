#include "Drone.hpp"

#include <cstring>
#include <cassert>
#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <utility>

void Coordinates::print() const {
  std::cout << x << ',' << y;
}

char const *Drone::getName() const {
  return m_name;
}

void Drone::printGeneratedPath() const {
  std::ifstream ifs(m_filename, std::ios::in|std::ios::binary);
  if (!ifs) {
    std::cerr << "could not open file\n";
    return;
  }

  Coordinates coords;
  while (ifs.read(reinterpret_cast<char *>(&coords), sizeof(coords))) {
    coords.print();
    std::cout << std::endl;
  }

  ifs.close();
}

Coordinates Drone::moveWithOneStep() {
  std::ifstream ifs(m_filename, std::ios::in|std::ios::binary);
  if (!ifs) {
    throw std::runtime_error("could not open file");
  }

  ifs.seekg(0, std::ios::end);
  std::streamsize size = ifs.tellg();

  // m_position = 0,1,...
  // [<0,1>,<2,5>,...]
  if (m_position + 1 >= size / sizeof(Coordinates)) {
    throw std::runtime_error("invalid position");
  }

  m_position++;
  ifs.seekg(m_position * sizeof(Coordinates), std::ios::beg);

  Coordinates coords;
  ifs.read(reinterpret_cast<char *>(&coords), sizeof(coords));

  ifs.close();

  return coords;
}

Drone::Drone(char const *name, char const *filename, unsigned position)
: m_name(new char[strlen(name) + 1]), m_position(position) {

  // debug-ване
  assert(strlen(filename) < 64);

  strcpy(m_name, name);
  strcpy(m_filename, filename);
}

Drone::Drone(Drone const &other) {
  copy(other);
}

Drone::Drone(Drone &&other) noexcept {
  move(std::move(other));
}

Drone &Drone::operator=(Drone const &other) {
  if (this != &other) {
    free();
    copy(other);
  }
  return *this;
}

Drone &Drone::operator=(Drone &&other) noexcept {
  if (this != &other) {
    free();
    move(std::move(other));
  }
  return *this;
}

Drone::~Drone() {
  free();
}

void Drone::copy(Drone const &other) {
  m_name = new char[strlen(other.m_name) + 1];
  strcpy(m_name, other.m_name);

  strcpy(m_filename, other.m_filename);

  m_position = other.m_position;
}

void Drone::move(Drone &&other) {
  m_name = other.m_name;
  other.m_name = nullptr;

  strcpy(m_filename, other.m_filename);
  strcpy(other.m_filename, "");

  m_position = other.m_position;
  other.m_position = 0;
}

void Drone::free() {
  delete[] m_name;
}
