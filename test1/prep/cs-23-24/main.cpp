#include <cstring>
#include <iostream>
#include <fstream>
#include <limits>

#include "Drone.hpp"
#include "DroneShow.hpp"

// на контролно не се очаква да е толкова дълго/усложнено,
// но е добре да се напишат някакви примерни входове,
// за да бъде все пак ясно какъв вход се очаква :)

constexpr char const *dronesPathFile = "dronesPath.txt";
constexpr unsigned MAX_DRONE_NAME_SIZE = 128;

bool isNewline(char c) {
  return c == '\n' || c == '\r';
}

bool isWhitespace(char c) {
  return c == ' ' || c == '\t' || isNewline(c);
}

bool addDrone(std::ifstream &ifs, DroneShow &ds) {
  if (!ifs)
    return false;

  // пропускаме всякакви trailing whitespace-ове
  while (isWhitespace(ifs.peek()))
    ifs.get();

  std::cout << (bool)ifs << ' ' << ifs.good() << ' ' << ifs.eof() << '\n';

  // !ifs не е достатъчно! !ifs == ifs.fail(),
  // така че просто поглеждане с peek() не вдига failbit,
  // за разлика от get, getline, operator>> и т.н.
  if (ifs.eof())
    return false;

  // приемаме, че позволяваме потребителя да въвежда
  // имена с не повече от 127 символа. иначе би
  // трябвало да направим още неща
  char droneName[MAX_DRONE_NAME_SIZE];

  std::cout << "Enter drone name:\n";
  std::cin.getline(droneName, MAX_DRONE_NAME_SIZE);

  char droneFile[MAX_DRONE_NAME_SIZE + 4];
  strcpy(droneFile, droneName);
  strcat(droneFile, ".bin");

  std::cout << "Enter drone index:\n";
  unsigned index;
  std::cin >> index;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::ofstream ofs(droneFile, std::ios::out|std::ios::binary);
  if (!ofs)
    return false;

  Coordinates coords;
  while (ifs >> coords.x && ifs >> coords.y) {
    ofs.write(reinterpret_cast<char const *>(&coords), sizeof(coords));

    if (ifs && isNewline(ifs.peek())) {
      break;
    }
  }

  Drone drone(droneName, droneFile, 0);
  ds.addDrone(drone, index);

  // не е нужно
  ofs.close();

  // тъй като бяхме споменавали std::clog на семинар :)
  std::clog << "Drone " << drone.getName() << " added successfully\n";

  return true;
}

bool createDrones(DroneShow &ds) {
  std::ifstream ifs(dronesPathFile, std::ios::in);
  if (!ifs) {
    std::cerr << "could not open file " << dronesPathFile << '\n';
    return false;
  }

  while (ifs.good() && addDrone(ifs, ds));

  ifs.close();

  return true;
}

int main() {

  DroneShow ds("drone show #1");

  if (createDrones(ds)) {
    ds.play();
  }

  return 0;
}
