#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <iostream>
#include "Matrix.h"

bool MatrixCompare(const Matrix& a, const Matrix& b) {
  if(a.rows() != b.rows() || a.cols() != b.cols()) {
    return false;
  }

  for (int y = 0; y < a.rows(); ++y)
  {
    for (int x = 0; x < a.cols(); ++x)
    {
      if(a[y][x] != b[y][x]) {
        return false;
      }
    }
  }

  return true;
}

std::string MatrixToString(Matrix& matrix) {
  std::stringstream ss;
  ss << matrix;
  return ss.str();
}

Matrix StringToMatrix(std::string data) {
  std::stringstream ss(data);
  Matrix m;
  ss >> m;
  return m;
}

TEST(Matrix, Case1) {
  Matrix matrix1 = StringToMatrix("[ 1 2 3 ; 4 5 6 ]");
  Matrix matrix2 = StringToMatrix("[ 7 8 ; 9 10; 11 12 ]");
  Matrix matrix3 = StringToMatrix("[ 58 64; 139 154 ]");

  Matrix matrix4 = matrix1 * matrix2;
  EXPECT_EQ("[ 58 64 \n; 139 154 ]", MatrixToString(matrix4));
  EXPECT_TRUE(MatrixCompare(matrix3, matrix4));
}

TEST(Matrix, Case2) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  matrix1 = matrix1;
  EXPECT_EQ("[ 1 2 -3 \n; 5 6 7 ]", MatrixToString(matrix1));
}

TEST(Matrix, Case3) {
  Matrix matrix1 = StringToMatrix("[ 1 2 3 ; 4 5 6 ]");

  EXPECT_EQ("[ 1 2 3 \n; 4 5 6 ]", MatrixToString(matrix1));
  EXPECT_EQ("[ 1 2 3 \n; 4 5 6 ]", MatrixToString(matrix1));
}

TEST(Matrix, Case4) {
  Matrix matrix1 = StringToMatrix("[ 1 2 3 ; 4 5 6 ]");

  EXPECT_EQ("[ 1 2 3 \n; 4 5 6 ]", MatrixToString(matrix1));
}

TEST(Matrix, Case5) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 2 -3 1 ; -6 5 7 ]");
  Matrix matrix3 = StringToMatrix("[ 3 -1 -2; -1 11 14 ]");

  Matrix matrix4 = matrix1 + matrix2;
  EXPECT_EQ("[ 3 -1 -2 \n; -1 11 14 ]", MatrixToString(matrix4));
  EXPECT_TRUE(MatrixCompare(matrix3, matrix4));
}

TEST(Matrix, Case6) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 1 5; 2 6; -3 7 ]");

  matrix2 = matrix2.transpose();
  EXPECT_EQ("[ 1 2 -3 \n; 5 6 7 ]", MatrixToString(matrix2));
  EXPECT_TRUE(MatrixCompare(matrix1, matrix2));
}

TEST(Matrix, Case7) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ -1 -2 3 ; -5 -6 -7 ]");

  Matrix matrix3 = -matrix1;
  EXPECT_EQ("[ -1 -2 3 \n; -5 -6 -7 ]", MatrixToString(matrix3));
  EXPECT_TRUE(MatrixCompare(matrix2, matrix3));
}

TEST(Matrix, Case8) {
  Matrix matrix1 = StringToMatrix("[ 1 2 3 ; 4 5 6 ]");
  Matrix matrix2 = StringToMatrix("[ 2 4 6; 8 10 12 ]");

  Matrix matrix3 = 2 * matrix1;
  EXPECT_TRUE(MatrixCompare(matrix2, matrix3));
}

TEST(Matrix, Case9) {
  Matrix m1, m2, m3, m_o1, m_o2, m_result;

  m1 = StringToMatrix("[ 2 3 ; 3 4 ]");
  m2 = StringToMatrix("[ 7 3 ; 4 2 ]");
  m3 = StringToMatrix("[ 3 4 ; 1 4 ]");

  m_result = StringToMatrix("[ 12 10 ; 8 10 ]");

  m_o1 = m1 + m2;
  m_o2 = m_o1 + m3;

  EXPECT_EQ(2, m_o2.rows());
  EXPECT_EQ(2, m_o2.cols());
  EXPECT_TRUE(MatrixCompare(m_o2, m_result));
}