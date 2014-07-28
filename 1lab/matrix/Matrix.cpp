#include "Matrix.h"


Matrix::Matrix()
{

}

Matrix::Matrix(const Matrix& other)
{

}

Matrix::Matrix(std::size_t size)
{

}

Matrix::Matrix(std::size_t rows, std::size_t cols)
{

}

Matrix::Matrix(std::string serialized)
{

}

Matrix::~Matrix()
{

}

Matrix& Matrix::operator=(const Matrix&)
{
  Matrix a;
  return a;
}

bool Matrix::operator==(const Matrix&) const
{
  return false;
}

bool Matrix::operator!=(const Matrix&) const
{
  return false;
}

Matrix Matrix::operator+(const Matrix&) const
{
  Matrix a;
  return a;
}

Matrix Matrix::operator*(const Matrix&) const
{
  Matrix a;
  return a;
}

Matrix Matrix::operator*(int) const
{
  Matrix a;
  return a;
}

Matrix Matrix::operator-(const Matrix&) const
{
  Matrix a;
  return a;
}

Matrix Matrix::operator-() const
{
  Matrix a;
  return a;
}

Matrix Matrix::transpose() const
{
  Matrix a;
  return a;
}

Matrix::matrix_row& Matrix::operator[](index i)
{
  return m_vectors[0];
}

const Matrix::matrix_row& Matrix::operator[](index i) const
{
  Matrix a;
  return a[0];
}

std::size_t Matrix::rows() const
{
  return m_rows;
}

std::size_t Matrix::cols() const
{
  return m_cols;
}

void Matrix::add_row()
{

}

std::istream& operator>>(std::istream& stream, Matrix& matrix)
{
  return stream;
}

std::ostream& operator<<(std::ostream& stream, Matrix& matrix)
{
  return stream;
}

Matrix operator*(int factor, const Matrix& matrix)
{
  Matrix a;
  return a;
}
