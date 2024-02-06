#include "s21_matrix_oop.h"

#include <cmath>      // std::abs
#include <stdexcept>  // error lib
#include <stdexcept>  // logic_error
#include <utility>    // std::move

S21Matrix::S21Matrix() : rows_(0), cols_(0) {
  matrix_ = new double *[rows_] {};
  for (int i = 0; i < rows_; ++i) {
    try {
      matrix_[i] = new double[cols_]{};
    } catch (...) {
      for (int j = 0; j < i; ++j) {
        delete[] matrix_[j];
      }
      delete[] matrix_;
      throw;
    }
  }
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  matrix_ = new double *[rows_] {};
  for (int i = 0; i < rows_; ++i) {
    try {
      matrix_[i] = new double[cols_]{};
    } catch (...) {
      for (int j = 0; j < i; ++j) {
        delete[] matrix_[j];
      }
      delete[] matrix_;
      throw;
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { Free(); }

void S21Matrix::Free() noexcept {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix S21Matrix::MinorMatrix(const int skip_row,
                                 const int skip_column) const {
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int row = 0, sub_row = 0; row < rows_; row++) {
    if (row == skip_row) continue;
    for (int col = 0, sub_col = 0; col < cols_; col++) {
      if (col == skip_column) continue;
      result(sub_row, sub_col) = (*this)(row, col);
      sub_col++;
    }
    sub_row++;
  }
  return result;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool flag = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) flag = false;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::abs((*this)(i, j) - other(i, j)) > EPSILON) flag = false;
    }
  }
  return flag;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("SumMatrix: Incorrect matrix size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("SubMatrix: Incorrect matrix size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::logic_error("MulMatrix: incorrect matrix size");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(j, i) = (*this)(i, j);
    }
  }
  return result;
}

double S21Matrix::calc_determinant(int n) const {
  double det = 0;
  if (n == 1) {
    // базовый случай: определитель матрицы 1x1 это единственный элемент
    det = (*this)(0, 0);
  } else if (n == 2) {
    // базовый случай: определитель матрицы 2х2 рассчитывается просто
    det = (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  } else {
    for (int j = 0; j < n; j++) {
      S21Matrix minor = S21Matrix::MinorMatrix(0, j);
      // рекурсивно вычислить определитель подматрицы
      double sub_det = minor.calc_determinant(n - 1);
      // добавить к общему определителю учитывая знак
      det += (j % 2 == 0 ? 1 : -1) * (*this)(0, j) * sub_det;
    }
  }
  return det;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::logic_error("Determinant: incorrect matrix size");
  }
  return S21Matrix::calc_determinant(rows_);
}

// версия для модификации
double &S21Matrix::operator()(int row, int col) & {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Index out of range");
  return matrix_[row][col];
}

// версия для чтения
const double &S21Matrix::operator()(int row, int col) const & {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Index out of range");
  return matrix_[row][col];
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix tmp{*this};
  tmp.SumMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix tmp{*this};
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix tmp{*this};
  tmp.MulMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(double number) const {
  S21Matrix tmp{*this};
  tmp.MulNumber(number);
  return tmp;
}

S21Matrix S21Matrix::operator*=(double number) {
  MulNumber(number);
  return *this;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    Free();
    rows_ = other.rows_;
    cols_ = other.cols_;

    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::logic_error("CalcComplements: incorrect matrix size");
  }

  S21Matrix result;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      double minor = S21Matrix::calculate_minor(i, j);
      result(i, j) = minor * pow(-1, i + j);
    }
  }
  return result;
}

double S21Matrix::calculate_minor(int i, int j) const {
  double minor = 1;
  if (rows_ > 1) {
    S21Matrix sub_matrix = S21Matrix::MinorMatrix(i, j);
    minor = sub_matrix.Determinant();
    sub_matrix.Free();
  }
  return minor;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error("InverseMatrix: incorrect matrix size");
  }
  double det = S21Matrix::Determinant();
  if (det < EPSILON) {
    throw std::logic_error("InverseMatrix: determinant must be non-zero");
  }
  S21Matrix complements = S21Matrix::CalcComplements();
  S21Matrix transposed_matrix = complements.Transpose();
  S21Matrix result = transposed_matrix * (1 / det);
  return result;
}