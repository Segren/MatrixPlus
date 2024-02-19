#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;
  const double EPSILON = 1e-7;
  void Free() noexcept;
  S21Matrix MinorMatrix(const int skip_row, const int skip_column) const;
  double calc_determinant(int n) const;
  double calculate_minor(int i, int j) const;

 public:
  S21Matrix();
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int rowValue);
  void SetCols(int colValue);

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(double number) const;
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  bool operator==(const S21Matrix &other) const;
  S21Matrix &operator=(S21Matrix &&other);
  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator*=(const S21Matrix &other);
  S21Matrix operator*=(double number);
  double &operator()(int row, int col) &;
  const double &operator()(int row, int col) const &;
};

#endif  // S21_MATRIX_OOP_H_