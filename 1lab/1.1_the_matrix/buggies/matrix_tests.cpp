#include <gtest/gtest.h>
#include <sstream>
#include "Matrix.h"


//Verify tests
bool MatrixCompare(const Matrix& a, const Matrix& b) {
  if(a.rows() != b.rows() || a.cols() != b.cols()) {
    return false;
  }

  for(size_t y = 0; y < a.rows(); ++y) {
    for(size_t x = 0; x < a.cols(); ++x) {
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

Matrix StringToMatrix(const std::string data) {
  std::stringstream ss(data);
  Matrix m;
  ss >> m;
  return m;
}

TEST(Matrix, ConstructorDefault) {
  EXPECT_NO_THROW({
    Matrix matrix1;
    EXPECT_EQ(0, matrix1.rows());
    EXPECT_EQ(0, matrix1.cols());
  });

}

TEST(Matrix, ConstructorSize) {
  const size_t size = 3;

  Matrix matrix(size);
  EXPECT_EQ(size, matrix.rows());
  EXPECT_EQ(size, matrix.cols());
}

TEST(Matrix, ConstructorSizeZero) {
  const size_t size = 0;

  EXPECT_THROW({
    Matrix matrix(size);
  }, std::invalid_argument);
}

TEST(Matrix, ConstructorSize2) {
  const size_t size_rows = 3, size_cols = 4;

  Matrix matrix(size_rows, size_cols);
  EXPECT_EQ(size_rows, matrix.rows());
  EXPECT_EQ(size_cols, matrix.cols());
}

TEST(Matrix, ConstructorSize2ZeroX) {
  const size_t size_x = 0, size_y = 4;

  EXPECT_THROW({
    Matrix matrix(size_x, size_y);
  }, std::invalid_argument);
}

TEST(Matrix, ConstructorSize2ZeroY) {
  const size_t size_x = 3, size_y = 0;

  EXPECT_THROW({
    Matrix matrix(size_x, size_y);
  }, std::invalid_argument);
}

TEST(Matrix, ConstructorSerialized) {
  Matrix matrix = StringToMatrix("       [ 1 2 -3 ; 5 6 7 ]");
  EXPECT_EQ(2, matrix.rows());
  EXPECT_EQ(3, matrix.cols());
}

TEST(Matrix, ConstructorSerializedError1) {
  EXPECT_THROW({
    Matrix matrix = StringToMatrix("[ 1 2 -3 ; 5 6 ]");
  }, std::invalid_argument);
}

TEST(Matrix, OperatorAssignment) {
  const size_t size = 3;
  Matrix matrix1(size);
  Matrix matrix2;

  matrix1[0][0] = 13;
  matrix2 = matrix1;
  matrix1[0][1] = 14;
  matrix2[0][2] = 15;

  EXPECT_EQ(13, matrix1[0][0]);
  EXPECT_EQ(13, matrix2[0][0]);

  EXPECT_EQ(14, matrix1[0][1]);
  EXPECT_EQ(0, matrix2[0][1]);

  EXPECT_EQ(0, matrix1[0][2]);
  EXPECT_EQ(15, matrix2[0][2]);
}

TEST(Matrix, OperatorAssignmentSelf) {
  const size_t size = 3;
  Matrix matrix1(size);

  matrix1[1][1] = 13;
  matrix1 = matrix1;
  EXPECT_EQ(size, matrix1.rows());
  EXPECT_EQ(size, matrix1.cols());
  EXPECT_EQ(13, matrix1[1][1]);
}

TEST(Matrix, OperatorEqualTrue) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");

  EXPECT_TRUE(MatrixCompare(matrix1, matrix2));
}

TEST(Matrix, OperatorEqualFalseValue) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 1 2 3 ; 5 6 7 ]");

  EXPECT_FALSE(MatrixCompare(matrix1, matrix2));
}

TEST(Matrix, OperatorEqualFalseSize) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 1 2 ; 5 6 ]");

  EXPECT_FALSE(MatrixCompare(matrix1, matrix2));
}

TEST(Matrix, OperatorNequalTrueValue) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 1 2 3 ; 5 6 7 ]");

  EXPECT_FALSE(MatrixCompare(matrix1, matrix2));
}

TEST(Matrix, OperatorNequalTrueSize) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 1 2 ; 5 6 ]");

  EXPECT_FALSE(MatrixCompare(matrix1, matrix2));
}

TEST(Matrix, OperatorNequalFalse) {
  Matrix matrix1 = StringToMatrix("[ 1 2 3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 1 2 3 ; 5 6 7 ]");

  EXPECT_TRUE(MatrixCompare(matrix1, matrix2));
}

TEST(Matrix, OperatorAddition) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 2 -3 1 ; -6 5 7 ]");
  Matrix matrix3 = StringToMatrix("[ 3 -1 -2; -1 11 14 ]");

  Matrix matrix4 = matrix1 + matrix2;
  EXPECT_TRUE(MatrixCompare(matrix3, matrix4));
}

TEST(Matrix, OperatorAdditionSize) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 2 -3 ; -6 5 ]");

  EXPECT_THROW({
    Matrix matrix3 = matrix1 + matrix2;
  }, std::exception);
}

TEST(Matrix, OperatorMultiplication) {
  Matrix matrix1 = StringToMatrix("[ 1 2 3 ; 4 5 6 ]");
  Matrix matrix2 = StringToMatrix("[ 7 8 ; 9 10; 11 12 ]");
  Matrix matrix3 = StringToMatrix("[ 58 64; 139 154 ]");

  Matrix matrix4 = matrix1 * matrix2;
  EXPECT_TRUE(MatrixCompare(matrix3, matrix4));
}

TEST(Matrix, OperatorMultiplicationSize) {
  Matrix matrix1 = StringToMatrix("[ 1 2 3 ; 4 5 6 ]");
  Matrix matrix2 = StringToMatrix("[ 7 8 ; 9 10 ]");

  EXPECT_THROW({
    Matrix matrix3 = matrix1 * matrix2;
  }, std::exception);
}

TEST(Matrix, OperatorMultiplicationScalar) {
  Matrix matrix1 = StringToMatrix("[ 1 2 3 ; 4 5 6 ]");
  Matrix matrix2 = StringToMatrix("[ 2 4 6; 8 10 12 ]");

  Matrix matrix3 = 2 * matrix1;
  EXPECT_TRUE(MatrixCompare(matrix2, matrix3));
}

TEST(Matrix, OperatorMultiplicationScalar2) {
  Matrix matrix1 = StringToMatrix("[ 1 2 3 ; 4 5 6 ]");
  Matrix matrix2 = StringToMatrix("[ 2 4 6; 8 10 12 ]");

  Matrix matrix3 = matrix1 * 2;
  EXPECT_TRUE(MatrixCompare(matrix2, matrix3));
}

TEST(Matrix, OperatorSubtraction) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 2 -3 1 ; -6 5 7 ]");
  Matrix matrix3 = StringToMatrix("[ -1 5 -4; 11 1 0 ]");

  Matrix matrix4 = matrix1 - matrix2;
  EXPECT_TRUE(MatrixCompare(matrix3, matrix4));
}

TEST(Matrix, OperatorSubtractionSize) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 2 -3 ; -6 5 ]");

  EXPECT_THROW({
    Matrix matrix3 = matrix1 - matrix2;
  }, std::exception);
}

TEST(Matrix, OperatorNegative) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ -1 -2 3 ; -5 -6 -7 ]");

  Matrix matrix3 = -matrix1;
  EXPECT_TRUE(MatrixCompare(matrix2, matrix3));
}

TEST(Matrix, Transpose) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 1 5; 2 6; -3 7 ]");
  EXPECT_TRUE(MatrixCompare(matrix1, matrix2.transpose()));
}

TEST(Matrix, OperatorIndex) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  EXPECT_EQ(6, matrix1[1][1]);
}

TEST(Matrix, OperatorIndexRange) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  EXPECT_THROW({
    int a = matrix1[3][0];
  }, std::out_of_range);
  EXPECT_THROW({
    int a = matrix1[-1][0];
  }, std::out_of_range);
  EXPECT_THROW({
    int a = matrix1[0][3];
  }, std::out_of_range);
  EXPECT_THROW({
    int a = matrix1[0][-1];
  }, std::out_of_range);
}

TEST(Matrix, Rows) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  EXPECT_EQ(2, matrix1.rows());
}

TEST(Matrix, Cols) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  EXPECT_EQ(3, matrix1.cols());
}

TEST(Matrix, OperatorIstream) {
  std::stringstream ss("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix1;
  Matrix matrix2 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  ss >> matrix1;

  EXPECT_TRUE(MatrixCompare(matrix1, matrix2));
}

TEST(Matrix, OperatorOstream) {
  std::stringstream ss;
  std::string string1("[ 1 2 -3 \n; 5 6 7 ]");
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");

  ss << matrix1;

  EXPECT_EQ(string1, ss.str());
}

TEST(Matrix, Case1Multiplication) {
  Matrix matrix1 = StringToMatrix("[ 1 2 3 ; 4 5 6 ]");
  Matrix matrix2 = StringToMatrix("[ 7 8 ; 9 10; 11 12 ]");
  Matrix matrix3 = StringToMatrix("[ 58 64; 139 154 ]");

  Matrix matrix4 = matrix1 * matrix2;
  EXPECT_EQ("[ 58 64 \n; 139 154 ]", MatrixToString(matrix4));
  EXPECT_TRUE(MatrixCompare(matrix3, matrix4));
}

TEST(Matrix, Case2SelfAssignment) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  matrix1 = matrix1;
  EXPECT_EQ("[ 1 2 -3 \n; 5 6 7 ]", MatrixToString(matrix1));
}

TEST(Matrix, Case3OutputConstCorrectness) {
  Matrix matrix1 = StringToMatrix("[ 1 2 3 ; 4 5 6 ]");

  EXPECT_EQ("[ 1 2 3 \n; 4 5 6 ]", MatrixToString(matrix1));
  EXPECT_EQ("[ 1 2 3 \n; 4 5 6 ]", MatrixToString(matrix1));
}

TEST(Matrix, Case4InputOutput) {
  Matrix matrix1 = StringToMatrix("[ 1 2 3 ; 4 5 6 ]");

  EXPECT_EQ("[ 1 2 3 \n; 4 5 6 ]", MatrixToString(matrix1));
}

TEST(Matrix, Case5Addition) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 2 -3 1 ; -6 5 7 ]");
  Matrix matrix3 = StringToMatrix("[ 3 -1 -2; -1 11 14 ]");

  Matrix matrix4 = matrix1 + matrix2;
  EXPECT_EQ("[ 3 -1 -2 \n; -1 11 14 ]", MatrixToString(matrix4));
  EXPECT_TRUE(MatrixCompare(matrix3, matrix4));
}

TEST(Matrix, Case6Transposition) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 1 5; 2 6; -3 7 ]");

  matrix2 = matrix2.transpose();
  EXPECT_EQ("[ 1 2 -3 \n; 5 6 7 ]", MatrixToString(matrix2));
  EXPECT_TRUE(MatrixCompare(matrix1, matrix2));
}

TEST(Matrix, Case7Negation) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ -1 -2 3 ; -5 -6 -7 ]");

  Matrix matrix3 = -matrix1;
  EXPECT_EQ("[ -1 -2 3 \n; -5 -6 -7 ]", MatrixToString(matrix3));
  EXPECT_TRUE(MatrixCompare(matrix2, matrix3));
}

TEST(Matrix, Case8ScalarMultiplication) {
  Matrix matrix1 = StringToMatrix("[ 1 2 3 ; 4 5 6 ]");
  Matrix matrix2 = StringToMatrix("[ 2 4 6; 8 10 12 ]");

  Matrix matrix3 = 2 * matrix1;
  EXPECT_TRUE(MatrixCompare(matrix2, matrix3));
}

TEST(Matrix, Case9RepeatedAddition) {
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

TEST(Matrix, Case10Subtraction) {
  Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2 = StringToMatrix("[ 2 -3 1 ; -6 5 7 ]");
  Matrix matrix3 = StringToMatrix("[ -1 5 -4; 11 1 0 ]");

  Matrix matrix4 = matrix1 - matrix2;
  EXPECT_TRUE(MatrixCompare(matrix3, matrix4));
}

TEST(Matrix, Case11AdditionConstCorrectness) {
  const Matrix matrix1_original = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  const Matrix matrix2_original = StringToMatrix("[ 2 -3 1 ; -6 5 7 ]");
  Matrix m1 = matrix1_original;
  Matrix m2 = matrix2_original;

  for(int i = 0; i < 10; ++i) {
    m2 + m1 + m2;
  }

  EXPECT_TRUE(MatrixCompare(matrix1_original, m1));
  EXPECT_TRUE(MatrixCompare(matrix2_original, m2));
}

TEST(Matrix, Case12SubtractionConstCorrectness) {
  const Matrix matrix1_original = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  const Matrix matrix2_original = StringToMatrix("[ 2 -3 1 ; -6 5 7 ]");
  Matrix m1 = matrix1_original;
  Matrix m2 = matrix2_original;

  for(int i = 0; i < 10; ++i) {
    m2 - m1 - m2;
  }

  EXPECT_TRUE(MatrixCompare(matrix1_original, m1));
  EXPECT_TRUE(MatrixCompare(matrix2_original, m2));
}

TEST(Matrix, Case13MultiplicationConstCorrectness) {
  const Matrix matrix1_original = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  const Matrix matrix2_original = StringToMatrix("[ 2 -3 1 ; -6 5 7 ]").transpose();
  Matrix m1 = matrix1_original;
  Matrix m2 = matrix2_original;

  for(int i = 0; i < 10; ++i) {
    m2 * m1 * m2;
  }

  EXPECT_TRUE(MatrixCompare(matrix1_original, m1));
  EXPECT_TRUE(MatrixCompare(matrix2_original, m2));
}

TEST(Matrix, Case14ScalarMultiplicationConstCorrectness) {
  const Matrix matrix1_original = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  const int c = 5;
  Matrix m1 = matrix1_original;

  for(int i = 0; i < 10; ++i) {
    c * m1 * c;
  }

  EXPECT_TRUE(MatrixCompare(matrix1_original, m1));
  EXPECT_EQ(5, c);
}

TEST(Matrix, Case15NegationConstCorrectness) {
  const Matrix matrix1_original = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  Matrix m1 = matrix1_original;

  for(int i = 0; i < 9; ++i) {
    -m1;
  }

  EXPECT_TRUE(MatrixCompare(matrix1_original, m1));
}

TEST(Matrix, Case16RepeatedTransposition) {
  const Matrix matrix1 = StringToMatrix("[ 1 2 -3 ; 5 6 7 ]");
  const Matrix matrix2_original = StringToMatrix("[ 1 5; 2 6; -3 7 ]");
  Matrix matrix2 = matrix2_original;

  for(int i = 0; i < 5; ++i) {
    EXPECT_TRUE(MatrixCompare(matrix1, matrix2.transpose()));
    EXPECT_TRUE(MatrixCompare(matrix1, matrix2));
    EXPECT_TRUE(MatrixCompare(matrix2_original, matrix2.transpose()));
    EXPECT_TRUE(MatrixCompare(matrix2_original, matrix2));
  }
}
