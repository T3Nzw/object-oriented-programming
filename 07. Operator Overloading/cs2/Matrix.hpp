#ifndef __MATRIX_HPP
#define __MATRIX_HPP

#include <cstddef>

template<std::size_t M, std::size_t N>
class Matrix {
public:
  double *operator[](std::size_t index) {
    return m_matrix[index];
  }

  double const *operator[](std::size_t index) const {
    return m_matrix[index];
  }

  // this: Matrix<M,N> *
  // Matrix<3,4> m1
  // Matrix<5,6> m2
  // m1 += m2
  Matrix<M,N> &operator+=(Matrix<M,N> const &other) {
    for (std::size_t i = 0; i < M; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        m_matrix[i][j] += other.m_matrix[i][j];
      }
    }
    return *this;
  }

  Matrix operator+(Matrix const &other) const {
    Matrix cpy(*this);
    cpy += other;
    return *this;
  }

  // m1[M][N], m2[N][K] => (m1*m2)[M][K]
  // Matrix<M,N> : *this
  template<std::size_t K>
  Matrix<M,K> operator*(Matrix<N,K> const &other) const {
    // ...
  }

  // няма как да имаме *=

private:
  // (m_matrix[0])[5]
  // double ** -> [] -> double * -> [] -> double
  double m_matrix[M][N];
};

// int matrix[10][5];
// std::cout << matrix[3][4];

// Matrix<10,5> m;

// temaplte<typename T>
// class vector {
//   private:
//    Rational *arr;
// };

// std::vector<int>
// std::vector<double>
// std::vector<Rational>

#endif // __MATRIX_HPP
