#include <cstring>
#include <iostream>
#include <fstream>
#include <limits>

constexpr unsigned int MAX_FN_SIZE = 11;
constexpr unsigned int MAX_NAME_SIZE = 65;
constexpr unsigned int MAX_FILENAME_SIZE = 129;
constexpr unsigned int MAX_COMMAND_SIZE = 129;


/* ----------------------------- */
/* ЛОГИКА ЗА СТРУКТУРАТА STUDENT */
/* ----------------------------- */

enum class Major {
  CS, SE, IS, INF, UNKNOWN
};

char const *toString(Major major) {
  switch (major) {
    case Major::CS:
      return "CS";
    case Major::SE:
      return "SE";
    case Major::IS:
      return "IS";
    case Major::INF:
      return "INF";
    default:
      return "unknown major";
  }
}

Major fromString(char const *major) {
  if (!strcmp(major, "CS"))
    return Major::CS;

  if (!strcmp(major, "SE"))
    return Major::SE;

  if (!strcmp(major, "IS"))
    return Major::IS;

  if (!strcmp(major, "INF"))
    return Major::INF;

  return Major::UNKNOWN;
}

// защо не пречи полетата са дефинирани в този ред?
struct Student {
  char fn[MAX_FN_SIZE];
  char firstName[MAX_NAME_SIZE];
  char lastName[MAX_NAME_SIZE];
  Major major;
  unsigned short year;
  unsigned short group;
};

// така можем да обединим писането в произволен изходен поток;
// std::ofstream и std::cout наследяват от std::ostream,
// така че могат да използват методите на std::ostream
// (все още не знаем какво в действителност е наследяване)
void print(Student const &s, std::ostream &os=std::cout) {
  os << s.fn << ',';
  os << s.firstName << ',';
  os << s.lastName << ',';
  os << toString(s.major) << ',';
  os << s.year << ',';
  os << s.group;
}


/* ------------------------- */
/* ЛОГИКА ЗА ДИНАМИЧЕН МАСИВ */
/* ------------------------- */

// аналогично на тази в задача 04, но с друг тип на елементите в масива

// подобно на това, което е правено на лекции
struct DynArray {
  Student *arr;
  size_t size, capacity;
};

// създаване на динамичен масив с конрекретен капацитет
DynArray mkDynArray(size_t capacity=0) {
  DynArray result{};

  if (capacity == 0)
    return result;

  result.arr = new Student[capacity];
  result.capacity = capacity;

  return result;
}

// преоразмеряване на динамичен масив
void resize(DynArray &dyn) {
  // заделяме памет за новия масив с двойно по-голям капацитет
  size_t newCapacity = dyn.capacity > 0 ? dyn.capacity * 2 : 1;
  Student *newArr = new Student[newCapacity];

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
void pushBack(Student const &s, DynArray &dyn) {
  if (dyn.size >= dyn.capacity) {
    resize(dyn);
  }

  dyn.arr[dyn.size++] = s;
}

// освобождаване на паметта за масив
void free(DynArray &dyn) {
  delete[] dyn.arr;
  dyn.arr = nullptr;
  dyn.size = 0;
  dyn.capacity = 0;
}


/* ----------------- */
/* ЛОГИКА ЗА ФАЙЛОВЕ */
/* ----------------- */

// тук абстрахираме логиката за четене на един студент.
// подаваме като параметър обектът, който е отворил файла,
// за да не се налага да отваряме файла отново и отново,
// което би трябвало да направим, ако подаваме името му
std::ifstream &readStudentFromFile(std::ifstream &ifs, Student &student) {

  ifs.getline(student.fn, MAX_FN_SIZE, ',');
  ifs.getline(student.firstName, MAX_NAME_SIZE, ',');
  ifs.getline(student.lastName, MAX_NAME_SIZE, ',');

  char major[10];
  ifs.getline(major, 10, ',');
  student.major = fromString(major);

  ifs >> student.year;
  ifs.ignore(std::numeric_limits<std::streamsize>::max(), ',');
  ifs >> student.group;

  ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  return ifs;
}

bool readStudentsFromFile(char const *filename, DynArray &students) {
  std::ifstream ifile(filename, std::ios::in);

  if (!ifile.is_open()) {
    std::cout << "could not open file " << filename << '\n';
    return false;
  }

  students = mkDynArray();

  Student student;
  while (readStudentFromFile(ifile, student)) {
    pushBack(student, students);
  }

  return true;
}

void writeStudentsToFile(DynArray const &students, char const *filename) {
  std::ofstream ofile(filename, std::ios::out);

  if (!ofile.is_open()) {
    std::cout << "could not open file " << filename << '\n';
    return;
  }

  for (size_t i = 0; i < students.size; ++i) {
    print(students.arr[i], ofile);
    ofile << '\n';
  }

  ofile.close();
}


/* ------------------- */
/* ЛОГИКА ЗА КОМАНДИТЕ */
/* ------------------- */

void filterByYear(unsigned short year, DynArray const &students, std::ostream &os=std::cout) {
  for (size_t i = 0; i < students.size; ++i)
    if (students.arr[i].year == year) {
      print(students.arr[i], os);
      os << '\n';
    }
}

bool changeYear(char const *fn, unsigned short year, DynArray &students) {
  for (size_t i = 0; i < students.size; ++i)
    if (!strcmp(students.arr[i].fn, fn)) {
      students.arr[i].year = year;
      return true;
    }
  return false;
}

bool removeByFn(char const *fn, DynArray &students) {
  size_t i = 0;

  while (i < students.size) {
    if (!strcmp(students.arr[i].fn, fn))
      break;

    i++;
  }

  if (i >= students.size)
    return false;

  while (i < students.size-1) {
    students.arr[i] = students.arr[i+1];
    i++;
  }

  students.size--;

  return true;
}

// сортирането на студентите по някакъв ключ означава,
// че в общия случай не знам точно по коя/кои от полетата
// на обектите ще искаме да сортираме. обикновено такъв вид
// сортиране се извършва на база предикат, който се подава
// като аргумент на функцията, извършваща сортировката
// (т.е. функция от по-висок ред). все още не сме говорили за тях,
// така че ще добавим този пример, след като се запознаем с тази тема


/* --------------------- */
/* ИЗПЪЛНЕНИЕ НА КОМАНДИ */
/* --------------------- */

// допълнителните валидации са оставени за упражнение на програмиста :)
struct CommandInfo {
  unsigned int argc;
  char **argv;
};

void free(CommandInfo &ci) {
  for (unsigned i = 0; i < ci.argc; ++i)
    delete[] ci.argv[i];
  delete[] ci.argv;
}

bool isWhitespace(char c) {
  return c == ' ' || c == '\n' || c == '\t';
}

void skipWhitespaces(char const *&str) {
  while (str && isWhitespace(*str))
    str++;
}

unsigned int countArgs(char const *command) {
  if (!command || !*command)
    return 0;

  unsigned int argc = 0;

  char prev = *command;
  if (!isWhitespace(prev))
    argc++;

  command++;
  while (*command) {
    if (isWhitespace(prev) && !isWhitespace(*command))
      argc++;

    prev = *command;
    command++;
  }

  return argc;
}

char const *tokenEnd(char const *begin) {
  while (begin && *begin && !isWhitespace(*begin))
    begin++;

  return begin;
}

CommandInfo parseCommand(char const *command) {
  if (!command)
    return {};

  CommandInfo ci;
  ci.argc = countArgs(command);
  ci.argv = new char*[ci.argc];

  unsigned int i = 0;
  while (i < ci.argc) {
    skipWhitespaces(command);

    char const *token = tokenEnd(command);

    unsigned int size = token - command;
    ci.argv[i] = new char[size+1];
    strncpy(ci.argv[i], command, size);
    ci.argv[i][size] = '\0';

    command = token + 1;
    i++;
  }

  return ci;
}

enum class ErrorCode {
  OK,
  EXIT,
  INVALID_COMMAND
};

ErrorCode execCommand(DynArray &students, char const *command) {
  if (!command)
    return ErrorCode::INVALID_COMMAND;

  ErrorCode ec = ErrorCode::INVALID_COMMAND;

  CommandInfo ci = parseCommand(command);

  if (ci.argc == 0) {
    ec = ErrorCode::INVALID_COMMAND;
  }

  else if (!strcmp(ci.argv[0], "saveas") && ci.argc == 2) {
    writeStudentsToFile(students, ci.argv[1]);
    ec = ErrorCode::EXIT;
  }

  else if (!strcmp(ci.argv[0], "filter_by_year") && ci.argc == 2) {
    filterByYear(atoi(ci.argv[1]), students);
    ec = ErrorCode::OK;
  }

  else if (!strcmp(ci.argv[0], "remove_by_fn") && ci.argc == 2) {
    removeByFn(ci.argv[1], students);
    ec = ErrorCode::OK;
  }

  else if (!strcmp(ci.argv[0], "change_year") && ci.argc == 3) {
    changeYear(ci.argv[1], atoi(ci.argv[2]), students);
    ec = ErrorCode::OK;
  }

  free(ci);

  return ec;
}

int main() {

  std::cout << "Enter a file name:\n";
  char filename[MAX_FILENAME_SIZE];
  std::cin.getline(filename, MAX_FILENAME_SIZE);

  DynArray students;

  if (!readStudentsFromFile(filename, students)) {
    return -1;
  }

  std::cout << "Successfully loaded file: " << filename << '\n';

  char command[MAX_COMMAND_SIZE];
  do {
    std::cout << ">";
    std::cin.getline(command, MAX_COMMAND_SIZE);
  } while (execCommand(students, command) != ErrorCode::EXIT);

  free(students);

  return 0;
}
