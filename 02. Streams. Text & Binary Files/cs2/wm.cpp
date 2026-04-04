#include <iostream>
#include <fstream>
#include <cstring>

struct WeatherMeasurement {
  char *city;
  double temperature;
  double humidity;
};

void writeWM(std::ofstream &ofs, WeatherMeasurement const &wm) {
  if (!ofs)
    return;

  // !!!
  // ofs.write(reinterpret_cast<char const *>(&wm), sizeof(WeatherMeasurement));

  // "abcd" ~> 4 abcd
  unsigned size = strlen(wm.city);
  ofs.write(reinterpret_cast<char const *>(&size), sizeof(unsigned));

  ofs.write(reinterpret_cast<char const *>(wm.city), size);

  ofs.write(reinterpret_cast<char const *>(&wm.temperature), sizeof(double));
  ofs.write(reinterpret_cast<char const *>(&wm.humidity), sizeof(double));
}

std::ifstream &readWM(std::ifstream &ifs, WeatherMeasurement &wm) {
  if (!ifs)
    return ifs;

  unsigned size;
  ifs.read(reinterpret_cast<char *>(&size), sizeof(unsigned));

  wm.city = new char[size+1];
  ifs.read(reinterpret_cast<char *>(wm.city), size);
  wm.city[size] = '\0';

  ifs.read(reinterpret_cast<char *>(&wm.temperature), sizeof(double));
  ifs.read(reinterpret_cast<char *>(&wm.humidity), sizeof(double));

  return ifs;
}

template<typename T>
struct DynArr {
  T *arr;
  unsigned size;
};

DynArr<WeatherMeasurement> readWMS(char const *filename) {
  // 1. първо пресмятаме размера на файла
  // 2. пресмятаме колко обекта имаме
  std::ifstream ifs(filename, std::ios::in|std::ios::binary);

  WeatherMeasurement wm;
  while (readWM(ifs, wm)) {}
}

int main() {


  return 0;
}
