#include <cmath>
#include <iostream>
#include <fstream>
#include <limits>

constexpr unsigned int MAX_FILENAME_SIZE = 129;

// тъй като ще работим със стойности с плаваща запетая (double),
// трябва да ги сравняваме правилно
int cmp(double x, double y) {
  double diff = x - y;

  // fabs е abs за числа с плаваща запетая;
  // std::numeric_limits<double>::epsilon() ни дава директно епсилон константа
  if (std::fabs(diff) < std::numeric_limits<double>::epsilon())
    return 0;

  if (diff < 0)
    return -1;

  else
    return 1;
}

/* ------------------------- */
/* ЛОГИКА ЗА ДИНАМИЧЕН МАСИВ */
/* ------------------------- */

// подобно на това, което е правено на лекции
struct DynArray {
  double *arr;
  size_t size, capacity;
};

// създаване на динамичен масив с конрекретен капацитет
DynArray mkDynArray(size_t capacity=0) {
  DynArray result{};

  if (capacity == 0)
    return result;

  result.arr = new double[capacity];
  result.capacity = capacity;

  return result;
}

// преоразмеряване на динамичен масив
void resize(DynArray &dyn) {
  // заделяме памет за новия масив с двойно по-голям капацитет
  size_t newCapacity = dyn.capacity > 0 ? dyn.capacity * 2 : 1;
  double *newArr = new double[newCapacity];

  // копираме всички елементи от стария масив в новия
  for (size_t i = 0; i < dyn.size; ++i) {
    newArr[i] = dyn.arr[i];
  }

  // освобождаваме паметта за стария масив
  delete[] dyn.arr;

  // присвояваме новите масив и капацитет на полетата на обекта dyn
  dyn.arr = newArr;
  dyn.capacity = newCapacity;
}

// добавяне на елемент в динамичен масив
void pushBack(double x, DynArray &dyn) {
  if (dyn.size >= dyn.capacity) {
    resize(dyn);
  }

  dyn.arr[dyn.size++] = x;
}

// освобождаване на паметта за масив
void free(DynArray &dyn) {
  delete[] dyn.arr;
  dyn.arr = nullptr;
  dyn.size = 0;
  dyn.capacity = 0;
}

DynArray mergeSorted(DynArray const &dyn1, DynArray const &dyn2) {
  // предварително заделяме памет за големината на резултатния масив.
  // не използваме полето capacity, защото нямаме нужда от тази допълнителна
  // памет в алгоритъма за сливане на сортирани масиви
  DynArray result = mkDynArray(dyn1.size + dyn2.size);

  size_t index1 = 0, index2 = 0;
  while (index1 < dyn1.size && index2 < dyn2.size) {
    // за четимост
    double el1 = dyn1.arr[index1], el2 = dyn2.arr[index2];

    if (cmp(el1, el2) < 0) {
      pushBack(el1, result);
      index1++;
    }
    else {
      pushBack(el2, result);
      index2++;
    }
  }

  while (index1 < dyn1.size) {
    pushBack(dyn1.arr[index1], result);
    index1++;
  }

  while (index2 < dyn2.size) {
    pushBack(dyn2.arr[index2], result);
    index2++;
  }

  return result;
}

/* -------------------------------- */
/* ЛОГИКА ЗА ЧЕТЕНЕ/ПИСАНЕ ВЪВ ФАЙЛ */
/* -------------------------------- */

DynArray readFromFile(char const *filename) {
  std::ifstream ifile(filename, std::ios::in);

  if (!ifile.is_open()) {
    std::cout << "could not open file" << filename << '\n';
    return mkDynArray();
  }

  // инициализиране на полетата на динамичния масив със стойности по подразбиране
  DynArray result = mkDynArray();

  // тук приемаме, че файлът е в правилен формат (т.е. има само числа)
  double x;
  // по този начин изпускаме интервали, нови редове, табулации и т.н.
  while (ifile >> x) {
    pushBack(x, result);
  }

  ifile.close();

  return result;
}

void writeToFile(DynArray const &dyn, char const *filename) {
  std::ofstream ofile(filename, std::ios::out);

  if (!ofile.is_open()) {
    std::cout << "could not open file " << filename << '\n';
    return;
  }

  // последният whitespace не е витален за логиката (защо?)
  for (size_t i = 0; i < dyn.size; ++i) {
    ofile << dyn.arr[i] << ' ';
  }

  ofile.close();
}

void sortContentsAndWriteTo(char const *filename1, char const *filename2, char const *outputFilename) {
  DynArray dyn1 = readFromFile(filename1);
  DynArray dyn2 = readFromFile(filename2);

  DynArray sorted = mergeSorted(dyn1, dyn2);

  writeToFile(sorted, outputFilename);

  free(sorted);
  free(dyn2);
  free(dyn1);
}

int main() {

  char filename1[MAX_FILENAME_SIZE],
       filename2[MAX_FILENAME_SIZE],
       outputFilename[MAX_FILENAME_SIZE];

  std::cin.getline(filename1, MAX_FILENAME_SIZE);
  std::cin.getline(filename2, MAX_FILENAME_SIZE);
  std::cin.getline(outputFilename, MAX_FILENAME_SIZE);

  sortContentsAndWriteTo(filename1, filename2, outputFilename);

  return 0;
}
