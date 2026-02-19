#include <iostream>

int **allocateMatrix(unsigned rows, unsigned cols) {
  int **matrix = new int*[rows];
  for (unsigned i = 0; i < rows; ++i) {
    matrix[i] = new int[cols];
  }
  return matrix;
}

void readElements(int **matrix, unsigned rows, unsigned cols) {
  for (unsigned i = 0; i < rows; ++i)
    for (unsigned j = 0; j < cols; ++j)
      std::cin >> matrix[i][j];
}

void freeMatrix(int **matrix, unsigned rows) {
  for (unsigned i = 0; i < rows; ++i)
    delete[] matrix[i];
  delete[] matrix;
}

constexpr unsigned ROWS = 10, COLS = 10;

// за домашно - защо синтаксисът за matrix е такъв?
void print(int matrix[][COLS], unsigned rows, unsigned cols) {
  for (unsigned int i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j)
      std::cout << matrix[i][j] << ' ';

    std::cout << '\n';
  }
}

int main() {

  // [] -> array
  // на всеки new съответства точно един delete

  // динамична памет за променливи
  int *ptr = new int(10);

  int *ptr2 = new int{10};
  int *ptr3 = new int;
  *ptr3 = 10;

  delete ptr;

  ptr = new int(18);
  *ptr = 11;

  delete ptr;
  delete ptr2;
  delete ptr3;

  // динамична памет за масиви
  unsigned n;
  std::cin >> n;
  int *arr = new int[n];
  delete[] arr;

  // динамична памет за матрици
  unsigned rows, cols;
  std::cin >> rows >> cols;

  int **matrix = allocateMatrix(rows, cols);
  readElements(matrix, rows, cols);
  // ...
  freeMatrix(matrix, rows);


  int smatrix[ROWS][COLS]{};

  print(smatrix, 3, 3);

  return 0;
}
