#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

class S21Matrix
{
private:
    int rows_, cols_;
    double **matrix_;
    const double EPSILON = 1e-7;
    void Free() noexcept; // DONE

    S21Matrix SubMatrix(const int skip_row, const int skip_column) const; // DONE

public:
    S21Matrix() noexcept;                   // DONE
    explicit S21Matrix(int rows, int cols); // DONE
    S21Matrix(const S21Matrix &other);      // DONE
    S21Matrix(S21Matrix &&other) noexcept;  // DONE
    ~S21Matrix();                           // DONE

    bool EqMatrix(const S21Matrix &other) const; // DONE
    void SumMatrix(const S21Matrix &other);      // DONE
    void SubMatrix(const S21Matrix &other);      // DONE
    void MulNumber(const double num);            // DONE
    void MulMatrix(const S21Matrix &other);      // DONE
    S21Matrix Transpose() const;                 // DONE
    S21Matrix CalcComplements() const;
    double Determinant() const;
    S21Matrix InverseMatrix() const;

    S21Matrix operator*(const S21Matrix &other);
    S21Matrix operator*(double number);
    S21Matrix operator+(const S21Matrix &other);
    S21Matrix operator-(const S21Matrix &other);
    bool operator==(const S21Matrix &other) const;
    S21Matrix &operator=(const S21Matrix &other);
    S21Matrix operator+=(const S21Matrix &other);
    S21Matrix operator-=(const S21Matrix &other);
    S21Matrix operator*=(const S21Matrix &other);
    S21Matrix operator*=(double number);
    double &operator()(int i, int j) &;
};

#endif // S21_MATRIX_OOP_H_