#include "Matrix.h"


Matrix::Matrix() : m_cols(0), m_rows(0)
{
}

Matrix::Matrix(const Matrix& other) : m_cols(other.m_cols), m_rows(other.m_rows), m_vectors(m_rows)
{

}

Matrix::Matrix(std::size_t size) : m_cols(size), m_rows(size), m_vectors(m_rows, matrix_row(m_cols))
{
  if (size == 0) {
    throw std::invalid_argument("Matrix size must be at least 1");
  }
}

Matrix::Matrix(std::size_t rows, std::size_t cols) : m_cols(cols), m_rows(rows), m_vectors(m_rows, matrix_row(m_cols))
{
  if (rows == 0 || cols == 0) {
    throw std::invalid_argument("Matrix must have at least one row and column");
  }
}

Matrix::Matrix(std::string serialized)
{

}

Matrix::~Matrix()
{

}

Matrix& Matrix::operator=(const Matrix& other)
{
  if (this == &other) {
    return *this;
  }

  m_vectors = other.m_vectors;
  m_cols = other.m_cols;
  m_rows = other.m_rows;
  
  return *this;
}

bool Matrix::operator==(const Matrix& other) const
{
  if (rows() != other.rows() || cols() != other.cols()) {
    return false;
  }



  return false;
}

bool Matrix::operator!=(const Matrix& other) const
{
  return false;
}

Matrix Matrix::operator+(const Matrix& other) const
{
  Matrix a;
  return a;
}

Matrix Matrix::operator*(const Matrix& other) const
{
  Matrix a;
  return a;
}

Matrix Matrix::operator*(int factor) const
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
