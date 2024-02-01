#include "s21_matrix_oop.h"

#include <cmath>     // std::abs
#include <stdexcept> // error lib
#include <utility>   // std::move

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0)
{
    matrix_ = new double *[rows_] {};
    for (int i = 0; i < rows_; ++i)
    {
        try
        {
            matrix_[i] = new double[cols_]{};
        }
        catch (...)
        {
            for (int j = 0; j < i; ++j)
            {
                delete[] matrix_[j];
            }
            delete[] matrix_;
            throw;
        }
    }
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols)
{
    matrix_ = new double *[rows_] {};
    for (int i = 0; i < rows_; ++i)
    {
        try
        {
            matrix_[i] = new double[cols_]{};
        }
        catch (...)
        {
            for (int j = 0; j < i; ++j)
            {
                delete[] matrix_[j];
            }
            delete[] matrix_;
            throw;
        }
    }
}

S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_)
{
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; i++)
    {
        matrix_[i] = new double[cols_];
        for (int j = 0; j < cols_; j++)
        {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_)
{
    other.cols_ = 0;
    other.rows_ = 0;
    other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix()
{
    for (int i = 0; i < rows_; i++)
    {
        delete[] matrix_[i];
    }
    delete[] matrix_;
}

void S21Matrix::Free() noexcept
{
    delete[] matrix_;
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
}

S21Matrix S21Matrix::SubMatrix(const int skip_row, const int skip_column) const
{
    S21Matrix result(rows_ - 1, cols_ - 1);
    for (int row = 0, sub_row = 0; row < rows_; row++)
    {
        if (row == skip_row)
            continue;
        for (int col = 0, sub_col = 0; col < cols_; col++)
        {
            if (col == skip_column)
                continue;
            result.matrix_[sub_row][sub_col] = matrix_[row][col];
            sub_col++;
        }
        sub_row++;
    }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const
{
    bool flag = true;
    if (rows_ != other.rows_ || cols_ != other.cols_)
        flag = false;
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > EPSILON)
                flag = false;
        }
    }
    return flag;
}

void S21Matrix::SumMatrix(const S21Matrix &other)
{
    if (rows_ != other.rows_ || cols_ != other.cols_)
    {
        throw std::logic_error("SumMatrix: Incorrect matrix size");
    }
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            (*this)(i, j) += other(i, j);
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix &other)
{
    if (rows_ != other.rows_ || cols_ != other.cols_)
    {
        throw std::logic_error("SubMatrix: Incorrect matrix size");
    }
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            (*this)(i, j) -= other(i, j);
        }
    }
}

void S21Matrix::MulNumber(const double num)
{
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            (*this)(i, j) *= num;
        }
    }
}

void S21Matrix::MulMatrix(const S21Matrix &other)
{
    if (cols_ != other.rows_)
    {
        throw std::logic_error("MulMatrix: incorrect matrix size");
    }
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < other.cols_; j++)
        {
            for (int k = 0; k < cols_; k++)
            {
                result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() const
{
    S21Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}