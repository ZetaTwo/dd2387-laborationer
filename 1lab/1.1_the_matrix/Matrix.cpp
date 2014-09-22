#include "Matrix.h"


Matrix::Matrix() : m_cols(0), m_rows(0) {
}

Matrix::Matrix(const Matrix& other) : m_cols(other.m_cols), m_rows(other.m_rows), m_vectors(other.m_vectors) {
}

Matrix::Matrix(std::size_t size) : m_cols(size), m_rows(size), m_vectors(m_rows, matrix_row(m_cols)) {
  if (size == 0) {
    throw std::invalid_argument("Matrix size must be at least 1");
  }
}

Matrix::Matrix(std::size_t rows, std::size_t cols) : m_cols(cols), m_rows(rows), m_vectors(m_rows, matrix_row(m_cols)) {
  if (rows == 0 || cols == 0) {
    throw std::invalid_argument("Matrix must have at least one row and column");
  }
}

Matrix::Matrix(std::string serialized){
  std::stringstream(serialized) >> *this;
}

Matrix::~Matrix() {
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

  typedef Vector<matrix_row>::const_iterator row_iter;
  typedef matrix_row::const_iterator col_iter;

  for (row_iter row = m_vectors.begin(), other_row = other.m_vectors.begin(); row != m_vectors.end(); row++, other_row++)
  {
    for (col_iter col = row->begin(), other_col = other_row->begin(); col != row->end(); col++, other_col++) {
      if (*col != *other_col) {
        return false;
      }
    }
  }

  return true;
}

bool Matrix::operator!=(const Matrix& other) const
{
  return !(*this == other);
}

Matrix Matrix::operator+(const Matrix& other) const
{
  if (rows() != other.rows() || cols() != other.cols()) {
    throw std::invalid_argument("Matrices must be of same size");
  }

  Matrix result(rows(), cols());

  typedef Vector<matrix_row>::const_iterator row_iter;
  typedef matrix_row::const_iterator col_iter;

  Vector<matrix_row>::iterator res_row = result.m_vectors.begin();
  for (row_iter row = m_vectors.begin(), other_row = other.m_vectors.begin();
    row != m_vectors.end(); row++, other_row++, res_row++)
  {
    matrix_row::iterator res_col = res_row->begin();
    for (col_iter col = row->begin(), other_col = other_row->begin();
      col != row->end(); col++, other_col++, res_col++) {
      *res_col = *col + *other_col;
    }
  }

  return result;
}

Matrix Matrix::operator*(const Matrix& other) const
{
  if (cols() != other.rows()) {
    throw std::invalid_argument("Matrices must be of compatible sizes");
  }

  Matrix result(rows(), other.cols());

  for (index i = 0; i < result.rows(); i++) {
    for (index j = 0; j < result.cols(); j++) {
      for (index k = 0; k < cols(); k++) {
        result[i][j] += m_vectors[i][k] * other.m_vectors[k][j];
      }
    }
  }    

  return result;
}

Matrix Matrix::operator*(int factor) const
{
  Matrix result(rows(), cols());

  typedef Vector<matrix_row>::const_iterator row_iter;
  typedef matrix_row::const_iterator col_iter;

  Vector<matrix_row>::iterator res_row = result.m_vectors.begin();
  for (row_iter row = m_vectors.begin(); row != m_vectors.end(); row++, res_row++)
  {
    matrix_row::iterator res_col = res_row->begin();
    for (col_iter col = row->begin(); col != row->end(); col++, res_col++) {
      *res_col = factor * *col;
    }
  }

  return result;
}

Matrix Matrix::operator-(const Matrix& other) const
{
  if (rows() != other.rows() || cols() != other.cols()) {
    throw std::invalid_argument("Matrices must be of same size");
  }

  Matrix result(rows(), cols());

  typedef Vector<matrix_row>::const_iterator row_iter;
  typedef matrix_row::const_iterator col_iter;

  Vector<matrix_row>::iterator res_row = result.m_vectors.begin();
  for (row_iter row = m_vectors.begin(), other_row = other.m_vectors.begin();
    row != m_vectors.end(); row++, other_row++, res_row++)
  {
    matrix_row::iterator res_col = res_row->begin();
    for (col_iter col = row->begin(), other_col = other_row->begin();
      col != row->end(); col++, other_col++, res_col++) {
      *res_col = *col - *other_col;
    }
  }

  return result;
}

Matrix Matrix::operator-() const
{
  Matrix zero(rows(), cols());

  return zero - *this;
}

Matrix Matrix::transpose() const
{
  Matrix result(cols(), rows());

  for (size_t y = 0; y < rows(); y++)
  {
    for (size_t x = 0; x < cols(); x++)
    {
      result[x][y] = m_vectors[y][x];
    }
  }

  return result;
}

Matrix::matrix_row& Matrix::operator[](index i)
{
  if (i >= rows()) {
    throw std::out_of_range("Index must be less than number of rows");
  }

  return m_vectors[i];
}

const Matrix::matrix_row& Matrix::operator[](index i) const
{
  if (i >= rows()) {
    throw std::out_of_range("Index must be less than number of rows");
  }

  return m_vectors[i];
}

std::size_t Matrix::rows() const
{
  return m_rows;
}

std::size_t Matrix::cols() const
{
  return m_cols;
}

std::istream& operator>>(std::istream& stream, Matrix& matrix)
{
  matrix.m_cols = 0;
  matrix.m_rows = 0;
  matrix.m_vectors.clear();

  //Fetch ";"
  char begin;
  stream >> begin;

  //Fetch first row
  matrix.m_vectors.push_back(Matrix::matrix_row());
  matrix.m_rows++;
  while (stream.good()) {
    int value;
    if (stream >> value) {
      matrix.m_vectors[matrix.m_rows-1].push_back(value);
    }
    else {
      break;
    }
  }
  matrix.m_cols = matrix.m_vectors[matrix.m_rows-1].size();

  //Fetch remaining rows
  stream.clear();
  do {
    char delim;
    stream >> delim;
    if (delim == ']') {
      return stream;
    }

    matrix.m_vectors.push_back(Matrix::matrix_row());
    matrix.m_rows++;
    for (size_t i = 0; i < matrix.m_cols; i++)
    {
      int value;
      if (stream >> value) {
        matrix.m_vectors[matrix.m_rows - 1].push_back(value);
      }
    }
  } while (stream.good());

  throw std::invalid_argument("Malformed matrix");
}

std::ostream& operator<<(std::ostream& stream, const Matrix& matrix)
{
  stream << "[ ";

  typedef Vector<Matrix::matrix_row>::const_iterator row_iter;
  typedef Matrix::matrix_row::const_iterator col_iter;

  bool first = true;
  for (row_iter row = matrix.m_vectors.begin(); row != matrix.m_vectors.end(); row++)
  {
    if (first) {
      first = false;
    }
    else {
      stream << "\n; ";
    }
    for (col_iter col = row->begin(); col != row->end(); col++) {
      stream << *col << " ";
    } 
  }

  stream << "]";

  return stream;
}

Matrix operator*(int factor, const Matrix& matrix)
{
  return matrix * factor;
}
