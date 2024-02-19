#include "test.h"

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

namespace TestCase {
void genMatrix(S21Matrix &matrix) {
  if (matrix.GetRows() < 0 || matrix.GetCols() < 0) {
    throw std::logic_error("genMatrix: Incorrect matrix size");
  }
  srand(time(nullptr) + rand());
  for (int i = 0; i < matrix.GetRows(); ++i) {
    for (int j = 0; j < matrix.GetCols(); ++j) {
      matrix(i, j) = rand() % 24;
    }
  }
}

void fillMatrix(S21Matrix &matrix, double first_value, double iteration) {
  if (matrix.GetRows() < 0 || matrix.GetCols() < 0) {
    throw std::logic_error("fillMatrix: Incorrect matrix size");
  }
  for (int i = 0; i < matrix.GetRows(); ++i) {
    for (int j = 0; j < matrix.GetCols(); ++j) {
      matrix(i, j) = first_value;
      first_value += iteration;
    }
  }
}
}  // namespace TestCase

TEST(Getters, Rows) {
  S21Matrix matrix(5, 3);
  ASSERT_EQ(matrix.GetRows(), 5);
}

TEST(Getters, Cols) {
  S21Matrix matrix(5, 3);
  ASSERT_EQ(matrix.GetCols(), 3);
}

TEST(Setters, RowsIncrease) {
  srand(time(nullptr) + rand());
  const int rows = rand() % 10 + 1;
  const int cols = rand() % 10 + 1;
  S21Matrix matrix(rows, cols);
  const int newRows = rows + 3;
  matrix.SetRows(newRows);
  ASSERT_TRUE(matrix.GetRows() == newRows &&
              matrix(newRows - 1, cols - 1) == 0);
}

TEST(Setters, RowsDecrease) {
  S21Matrix matrix(3, 5);
  matrix.SetRows(2);
  ASSERT_TRUE(matrix.GetRows() == 2);
}

TEST(Setters, RowsSame) {
  S21Matrix matrix(3, 5);
  matrix.SetRows(3);
  ASSERT_TRUE(matrix.GetRows() == 3);
}

TEST(Setters, RowsFailure) {
  S21Matrix matrix(3, 5);
  EXPECT_ANY_THROW(matrix.SetRows(-2));
}

TEST(Setters, ColsFailure) {
  S21Matrix matrix(3, 5);
  EXPECT_ANY_THROW(matrix.SetCols(-2));
}

TEST(Setters, ColsIncrease) {
  srand(time(nullptr) + rand());
  const int rows = rand() % 10 + 1;
  const int cols = rand() % 10 + 1;
  S21Matrix matrix(rows, cols);
  const int newCols = cols + 3;
  matrix.SetCols(newCols);
  ASSERT_TRUE(matrix.GetCols() == newCols &&
              matrix(rows - 1, newCols - 1) == 0);
}

TEST(Setters, ColsDecrease) {
  S21Matrix matrix(3, 5);
  matrix.SetCols(2);
  ASSERT_TRUE(matrix.GetCols() == 2);
}

TEST(Setters, ColsSame) {
  S21Matrix matrix(3, 5);
  matrix.SetCols(5);
  ASSERT_TRUE(matrix.GetCols() == 5);
}

TEST(Constructors, Base) {
  S21Matrix matrix;
  ASSERT_TRUE(matrix.GetRows() == 0 && matrix.GetCols() == 0);
}

TEST(Constructors, Parameters) {
  S21Matrix matrix(3, 5);
  ASSERT_TRUE(matrix.GetRows() == 3 && matrix.GetCols() == 5);
}

TEST(Constructors, Copy) {
  S21Matrix matrix1(3, 5);
  TestCase::genMatrix(matrix1);
  S21Matrix matrix2(matrix1);
  ASSERT_TRUE(matrix1 == matrix2);
}

TEST(Constructors, Move) {
  S21Matrix matrix0;
  S21Matrix matrix1(3, 5);
  TestCase::genMatrix(matrix1);
  S21Matrix matrix2 = matrix1;

  S21Matrix movedMatrix(std::move(matrix1));
  ASSERT_EQ(movedMatrix.GetRows(), matrix2.GetRows());
  ASSERT_EQ(movedMatrix.GetCols(), matrix2.GetCols());
  ASSERT_TRUE(movedMatrix == matrix2);

  ASSERT_TRUE(matrix1 == matrix0);
}

TEST(Functions, EqMatrixTrue) {
  S21Matrix matrix1;
  S21Matrix matrix2(matrix1);
  ASSERT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Functions, EqMatrixFalse1) {
  S21Matrix matrix1(3, 5);
  TestCase::genMatrix(matrix1);
  S21Matrix matrix2(5, 1);
  TestCase::genMatrix(matrix2);
  ASSERT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Functions, EqMatrixFalse2) {
  S21Matrix matrix1(10, 10);
  TestCase::genMatrix(matrix1);
  S21Matrix matrix2(10, 10);
  TestCase::genMatrix(matrix2);
  ASSERT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Functions, EqMatrixFalse3) {
  S21Matrix matrix1(3, 5);
  TestCase::genMatrix(matrix1);
  S21Matrix matrix2(3, 1);
  TestCase::genMatrix(matrix2);
  ASSERT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Functions, SumMatrixSuccess) {
  srand(time(nullptr));
  const int rows = rand() % 10 + 1;
  const int cols = rand() % 10 + 1;
  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  TestCase::genMatrix(matrix2);
  matrix1.SumMatrix(matrix2);
  ASSERT_TRUE(matrix1 == matrix2);
}

TEST(Functions, SumMatrixFail1) {
  S21Matrix matrix1(5, 6);
  S21Matrix matrix2(2, 3);
  EXPECT_ANY_THROW(matrix1.SumMatrix(matrix2));
}

TEST(Functions, SubMatrixSuccess) {
  srand(time(nullptr));
  const int rows = rand() % 10 + 1;
  const int cols = rand() % 10 + 1;
  S21Matrix matrix1(rows, cols);
  TestCase::genMatrix(matrix1);
  S21Matrix matrix2(matrix1);
  matrix1.SubMatrix(matrix2);
  S21Matrix matrix0(rows, cols);
  ASSERT_TRUE(matrix1 == matrix0);
}

TEST(Functions, SubMatrixFail) {
  S21Matrix matrix1(5, 5);
  TestCase::genMatrix(matrix1);
  S21Matrix matrix2(3, 2);
  EXPECT_ANY_THROW(matrix1.SubMatrix(matrix2));
}

TEST(Functions, MulNumber) {
  S21Matrix matrix(5, 5);
  TestCase::genMatrix(matrix);
  S21Matrix matrixCopy(matrix);
  const double mul = 3;
  matrix.MulNumber(mul);
  srand(time(nullptr));
  const int i = rand() % matrix.GetRows();
  const int k = rand() % matrix.GetCols();
  ASSERT_TRUE(matrix(i, k) == (matrixCopy(i, k) * mul));
}

TEST(Functions, MulMatrixSuccess) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);

  TestCase::fillMatrix(A, 1, 1);
  TestCase::fillMatrix(B, 1, 1);
  A.MulMatrix(B);
  C(0, 0) = 30, C(0, 1) = 36, C(0, 2) = 42;
  C(1, 0) = 66, C(1, 1) = 81, C(1, 2) = 96;
  C(2, 0) = 102, C(2, 1) = 126, C(2, 2) = 150;
  ASSERT_TRUE(A == C);
}

TEST(Functions, MulMatrixFail) {
  S21Matrix A(3, 3);
  S21Matrix B(2, 2);

  TestCase::fillMatrix(A, 1, 1);
  TestCase::fillMatrix(B, 1, 1);
  EXPECT_ANY_THROW(A.MulMatrix(B));
}

TEST(Functions, Transpose) {
  S21Matrix A(3, 4);
  S21Matrix B = A.Transpose();
  ASSERT_TRUE(A.GetCols() == B.GetRows() && A.GetRows() == B.GetCols());
}

TEST(Functions, Determinant1x1) {
  S21Matrix A(1, 1);
  A(0, 0) = 21;
  double determinant = A.Determinant();
  ASSERT_TRUE(determinant == 21);
}

TEST(Functions, Determinant2x2) {
  S21Matrix A(2, 2);
  TestCase::fillMatrix(A, 3, 3);
  double determinant = A.Determinant();
  ASSERT_TRUE(determinant == -18);
}

TEST(Functions, Determinant3x3) {
  S21Matrix A(3, 3);
  TestCase::fillMatrix(A, 1, 1);
  double determinant = A.Determinant();
  ASSERT_TRUE(determinant == 0);
}

TEST(Functions, DeterminantFAIL) {
  S21Matrix A(5, 3);
  EXPECT_ANY_THROW(A.Determinant());
}

TEST(Functions, CalcComplements1) {
  // успех: значения из задания
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 1, A(0, 1) = 2, A(0, 2) = 3;
  A(1, 0) = 0, A(1, 1) = 4, A(1, 2) = 2;
  A(2, 0) = 5, A(2, 1) = 2, A(2, 2) = 1;

  S21Matrix RES = A.CalcComplements();
  C(0, 0) = 0, C(0, 1) = 10, C(0, 2) = -20;
  C(1, 0) = 4, C(1, 1) = -14, C(1, 2) = 8;
  C(2, 0) = -8, C(2, 1) = -2, C(2, 2) = 4;
  ASSERT_TRUE(C == RES);
}

TEST(Functions, CalcComplements2) {
  S21Matrix matrix1(4, 4);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 12;
  matrix1(0, 2) = 12;
  matrix1(0, 3) = -9;
  matrix1(1, 0) = 5;
  matrix1(1, 1) = 15;
  matrix1(1, 2) = 20;
  matrix1(1, 3) = -2;
  matrix1(2, 0) = 16;
  matrix1(2, 1) = 6;
  matrix1(2, 2) = 5;
  matrix1(2, 3) = 41;
  matrix1(3, 0) = 15;
  matrix1(3, 1) = 3;
  matrix1(3, 2) = 21;
  matrix1(3, 3) = 7;

  S21Matrix matrix2(4, 4);
  matrix2(0, 0) = -10992;
  matrix2(0, 1) = -5408;
  matrix2(0, 2) = 7224;
  matrix2(0, 3) = 4200;
  matrix2(1, 0) = 9939;
  matrix2(1, 1) = 2861;
  matrix2(1, 2) = -6333;
  matrix2(1, 3) = -3525;
  matrix2(2, 0) = -1443;
  matrix2(2, 1) = -1157;
  matrix2(2, 2) = 1221;
  matrix2(2, 3) = -75;
  matrix2(3, 0) = -2841;
  matrix2(3, 1) = 641;
  matrix2(3, 2) = 327;
  matrix2(3, 3) = 975;
  ASSERT_TRUE(matrix1.CalcComplements() == matrix2);
}

TEST(Functions, CalcComplementsFail) {
  // успех: значения из задания
  S21Matrix A(3, 2);
  A(0, 0) = 1, A(0, 1) = 2;
  A(1, 0) = 0, A(1, 1) = 4;
  A(2, 0) = 5, A(2, 1) = 2;

  EXPECT_ANY_THROW(A.CalcComplements());
}

TEST(Functions, InverseMatrix1) {
  // успех: матрица 1х1
  S21Matrix A(1, 1);
  S21Matrix C(1, 1);
  A(0, 0) = 21;
  C(0, 0) = 1.0 / 21.0;
  S21Matrix RES = A.InverseMatrix();
  ASSERT_TRUE(C == RES);
}

TEST(Functions, InverseMatrix2) {
  // успех: значения из задания
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 2, A(0, 1) = 5, A(0, 2) = 7;
  A(1, 0) = 6, A(1, 1) = 3, A(1, 2) = 4;
  A(2, 0) = 5, A(2, 1) = -2, A(2, 2) = -3;

  C(0, 0) = 1, C(0, 1) = -1, C(0, 2) = 1;
  C(1, 0) = -38, C(1, 1) = 41, C(1, 2) = -34;
  C(2, 0) = 27, C(2, 1) = -29, C(2, 2) = 24;

  S21Matrix RES = A.InverseMatrix();
  ASSERT_TRUE(C == RES);
}

TEST(Functions, InverseMatrix3) {
  S21Matrix matrix1(4, 4);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 12;
  matrix1(0, 2) = 12;
  matrix1(0, 3) = -9;
  matrix1(1, 0) = 5;
  matrix1(1, 1) = 15;
  matrix1(1, 2) = 20;
  matrix1(1, 3) = -2;
  matrix1(2, 0) = 16;
  matrix1(2, 1) = 6;
  matrix1(2, 2) = 5;
  matrix1(2, 3) = 41;
  matrix1(3, 0) = 15;
  matrix1(3, 1) = 3;
  matrix1(3, 2) = 21;
  matrix1(3, 3) = 7;

  S21Matrix matrix2(4, 4);
  matrix2(0, 0) = 0.407111111;
  matrix2(0, 1) = -0.368111111;
  matrix2(0, 2) = 0.053444444;
  matrix2(0, 3) = 0.105222222;
  matrix2(1, 0) = 0.200296296;
  matrix2(1, 1) = -0.105962963;
  matrix2(1, 2) = 0.042851852;
  matrix2(1, 3) = -0.023740741;
  matrix2(2, 0) = -0.267555556;
  matrix2(2, 1) = 0.234555556;
  matrix2(2, 2) = -0.045222222;
  matrix2(2, 3) = -0.012111111;
  matrix2(3, 0) = -0.155555556;
  matrix2(3, 1) = 0.130555556;
  matrix2(3, 2) = 0.002777778;
  matrix2(3, 3) = -0.036111111;
  ASSERT_TRUE(matrix1.InverseMatrix() == matrix2);
}

TEST(Functions, InverseMatrixFail1) {
  // провал: детерминант равен нулю
  S21Matrix A(3, 3);
  TestCase::fillMatrix(A, 1, 1);
  EXPECT_ANY_THROW(A.InverseMatrix());
}

TEST(Functions, InverseMatrixFail2) {
  // успех: значения из задания
  S21Matrix A(4, 3);
  EXPECT_ANY_THROW(A.InverseMatrix());
}

TEST(Operators, Equal) {
  S21Matrix matrix1;
  TestCase::genMatrix(matrix1);
  S21Matrix matrix2(matrix1);
  ASSERT_TRUE(matrix1.EqMatrix(matrix2) == (matrix1 == matrix2));
}

TEST(Operators, Assignment) {
  S21Matrix matrix1;
  TestCase::genMatrix(matrix1);
  S21Matrix matrix2 = matrix1;
  ASSERT_EQ(matrix1, matrix2);
}

TEST(Operators, SumMatrix) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(3, 4);
  TestCase::genMatrix(matrix1);
  TestCase::genMatrix(matrix2);
  S21Matrix matrix3(matrix1);
  matrix3.SumMatrix(matrix2);
  ASSERT_TRUE(matrix3 == (matrix1 + matrix2));
}

TEST(Operators, SumMatrixIncrement) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(3, 4);
  TestCase::genMatrix(matrix1);
  TestCase::genMatrix(matrix2);
  S21Matrix matrix3(matrix1);
  matrix3.SumMatrix(matrix2);
  ASSERT_TRUE(matrix3 == (matrix1 += matrix2));
}

TEST(Operators, SubMatrix) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(3, 4);
  TestCase::genMatrix(matrix1);
  TestCase::genMatrix(matrix2);
  S21Matrix matrix3(matrix1);
  matrix3.SubMatrix(matrix2);
  ASSERT_TRUE(matrix3 == (matrix1 - matrix2));
}

TEST(Operators, SubMatrixIncrement) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(3, 4);
  TestCase::genMatrix(matrix1);
  TestCase::genMatrix(matrix2);
  S21Matrix matrix3(matrix1);
  matrix3.SubMatrix(matrix2);
  ASSERT_TRUE(matrix3 == (matrix1 -= matrix2));
}

TEST(Operators, MulMatrix) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(4, 3);
  TestCase::genMatrix(matrix1);
  TestCase::genMatrix(matrix2);
  S21Matrix matrix3(matrix1);
  matrix3.MulMatrix(matrix2);
  ASSERT_TRUE(matrix3 == (matrix1 * matrix2));
}

TEST(Operators, MulMatrixIncrement) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(4, 3);
  TestCase::genMatrix(matrix1);
  TestCase::genMatrix(matrix2);
  S21Matrix matrix3(matrix1);
  matrix3.MulMatrix(matrix2);
  ASSERT_TRUE(matrix3 == (matrix1 *= matrix2));
}

TEST(Operators, MulMatrixToNum) {
  S21Matrix matrix1(3, 4);
  const double num = 3;
  TestCase::genMatrix(matrix1);
  S21Matrix matrix3(matrix1);
  matrix3.MulNumber(num);
  ASSERT_TRUE(matrix3 == (matrix1 * num));
}

TEST(Operators, MulMatrixToNumIncrement) {
  S21Matrix matrix1(3, 4);
  const double num = 3;
  TestCase::genMatrix(matrix1);
  S21Matrix matrix3(matrix1);
  matrix3.MulNumber(num);
  ASSERT_TRUE(matrix3 == (matrix1 *= num));
}

TEST(Operators, OutOfRange1) {
  S21Matrix matrix1(3, 4);
  TestCase::genMatrix(matrix1);
  EXPECT_ANY_THROW(matrix1(5, 5));
}

TEST(Operators, OutOfRange2) {
  S21Matrix matrix1(3, 4);
  TestCase::genMatrix(matrix1);
  EXPECT_ANY_THROW(matrix1(4, 4));
}

TEST(Operators, OutOfRange3) {
  S21Matrix matrix1(3, 4);
  TestCase::genMatrix(matrix1);
  EXPECT_ANY_THROW(matrix1(3, 5));
}

TEST(Operators, OutOfRange4) {
  S21Matrix matrix1(3, 4);
  TestCase::genMatrix(matrix1);
  EXPECT_ANY_THROW(matrix1(-3, -3));
}

TEST(Operators, InRange1) {
  S21Matrix matrix1(3, 4);
  ASSERT_TRUE(matrix1(2, 2) == 0);
}