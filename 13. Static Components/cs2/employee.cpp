#include <iostream>

class Employee {
private:
  double baseSalary;
};

class Engineer : public Employee {
private:
  // бонусът е уникален за всеки инженер
  double bonus;
};

class Analyst : public Employee {
private:
  // бонусът е един и същ за всички анализатори
  static double bonus;
};

double Analyst::bonus = 0.15;
