#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;
  const double EPSILON = 1e-7;
  void Free() noexcept;  // DONE
  S21Matrix MinorMatrix(const int skip_row,
                        const int skip_column) const;  // DONE
  double calc_determinant(int n) const;                // DONE
  double calculate_minor(int i, int j) const;          // DONE

 public:
  S21Matrix();                             // DONE
  explicit S21Matrix(int rows, int cols);  // DONE
  S21Matrix(const S21Matrix &other);       // DONE
  S21Matrix(S21Matrix &&other) noexcept;   // DONE
  ~S21Matrix();                            // DONE

  bool EqMatrix(const S21Matrix &other) const;  // DONE
  void SumMatrix(const S21Matrix &other);       // DONE
  void SubMatrix(const S21Matrix &other);       // DONE
  void MulNumber(const double num);             // DONE
  void MulMatrix(const S21Matrix &other);       // DONE
  S21Matrix Transpose() const;                  // DONE
  S21Matrix CalcComplements() const;            // DONE
  double Determinant() const;                   // DONE
  S21Matrix InverseMatrix() const;              // DONE

  S21Matrix operator*(const S21Matrix &other) const;   // DONE
  S21Matrix operator*(double number) const;            // DONE
  S21Matrix operator+(const S21Matrix &other) const;   // DONE
  S21Matrix operator-(const S21Matrix &other) const;   // DONE
  bool operator==(const S21Matrix &other) const;       // DONE
  S21Matrix &operator=(const S21Matrix &other);        // DONE
  S21Matrix operator+=(const S21Matrix &other);        // DONE
  S21Matrix operator-=(const S21Matrix &other);        // DONE
  S21Matrix operator*=(const S21Matrix &other);        // DONE
  S21Matrix operator*=(double number);                 // DONE
  double &operator()(int row, int col) &;              // DONE
  const double &operator()(int row, int col) const &;  // DONE
};

#endif  // S21_MATRIX_OOP_H_