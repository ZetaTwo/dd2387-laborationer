#include <gtest/gtest.h>
#include <sstream>
#include "../matrix/Matrix.h"

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
  const size_t size_x = 3, size_y = 4;

  Matrix matrix(size_x, size_y);
  EXPECT_EQ(size_y, matrix.rows());
  EXPECT_EQ(size_x, matrix.cols());
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
  Matrix matrix("[ 1 2 -3 ; 5 6 7 ]");
  EXPECT_EQ(2, matrix.rows());
  EXPECT_EQ(3, matrix.cols());
}

TEST(Matrix, ConstructorSerializedError1) {
  EXPECT_THROW({
    Matrix matrix("[ 1 2 -3 ; 5 6 ]");
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
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2("[ 1 2 -3 ; 5 6 7 ]");

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(Matrix, OperatorEqualFalseValue) {
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2("[ 1 2 3 ; 5 6 7 ]");

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(Matrix, OperatorEqualFalseSize) {
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2("[ 1 2 ; 5 6 ]");

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(Matrix, OperatorNequalTrueValue) {
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2("[ 1 2 3 ; 5 6 7 ]");

  EXPECT_TRUE(matrix1 != matrix2);
}

TEST(Matrix, OperatorEqualTrueSize) {
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2("[ 1 2 ; 5 6 ]");

  EXPECT_TRUE(matrix1 != matrix2);
}

TEST(Matrix, OperatorNequalFalse) {
  Matrix matrix1("[ 1 2 3 ; 5 6 7 ]");
  Matrix matrix2("[ 1 2 3 ; 5 6 7 ]");

  EXPECT_FALSE(matrix1 != matrix2);
}

TEST(Matrix, OperatorAddition) {
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2("[ 2 -3 1 ; -6 5 7 ]");
  Matrix matrix3("[ 3 -1 -2; -1 11 14 ]");

  Matrix matrix4 = matrix1 + matrix2;
  EXPECT_EQ(matrix3, matrix4);
}

TEST(Matrix, OperatorAdditionSize) {
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2("[ 2 -3 ; -6 5 ]");

  EXPECT_THROW({
    Matrix matrix3 = matrix1 + matrix2;
  }, std::invalid_argument);
}

TEST(Matrix, OperatorMultiplication) {
  Matrix matrix1("[ 1 2 3 ; 4 5 6 ]");
  Matrix matrix2("[ 7 8 ; 9 10; 11 12 ]");
  Matrix matrix3("[ 58 64; 139 154 ]");

  Matrix matrix4 = matrix1 * matrix2;
  EXPECT_EQ(matrix3, matrix4);
}

TEST(Matrix, OperatorMultiplicationSize) {
  Matrix matrix1("[ 1 2 3 ; 4 5 6 ]");
  Matrix matrix2("[ 7 8 ; 9 10; 11 12 ]");

  EXPECT_THROW({
    Matrix matrix3 = matrix2 * matrix1;
  }, std::invalid_argument);
}

TEST(Matrix, OperatorMultiplicationScalar) {
  Matrix matrix1("[ 1 2 3 ; 4 5 6 ]");
  Matrix matrix2("[ 2 4 6; 8 10 12 ]");

  Matrix matrix3 = 2 * matrix1;
  EXPECT_EQ(matrix2, matrix3);
}

TEST(Matrix, OperatorMultiplicationScalar2) {
  Matrix matrix1("[ 1 2 3 ; 4 5 6 ]");
  Matrix matrix2("[ 2 4 6; 8 10 12 ]");

  Matrix matrix3 = matrix1 * 2;
  EXPECT_EQ(matrix2, matrix3);
}

TEST(Matrix, OperatorSubtraction) {
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2("[ 2 -3 1 ; -6 5 7 ]");
  Matrix matrix3("[ -1 1 -4; 11 1 0 ]");

  Matrix matrix4 = matrix1 - matrix2;
  EXPECT_EQ(matrix3, matrix4);
}

TEST(Matrix, OperatorSubtractionSize) {
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2("[ 2 -3 ; -6 5 ]");

  EXPECT_THROW({
    Matrix matrix3 = matrix1 - matrix2;
  }, std::invalid_argument);
}

TEST(Matrix, OperatorNegative) {
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2("[ -1 -2 3 ; -5 -6 -7 ]");

  Matrix matrix3 = -matrix1;
  EXPECT_EQ(matrix2, matrix3);
}

TEST(Matrix, Transpose) {
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix2("[ 1 5; 2 6; -3 7 ]");
  EXPECT_EQ(matrix1, matrix2.transpose());
}

TEST(Matrix, OperatorIndex) {
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  EXPECT_EQ(-3, matrix1[0][2]);
}

TEST(Matrix, OperatorIndexRange) {
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
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
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  EXPECT_EQ(2, matrix1.rows());
}

TEST(Matrix, Cols) {
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  EXPECT_EQ(3, matrix1.cols());
}

TEST(Matrix, OperatorIstream) {
  std::stringstream ss("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix1;
  Matrix matrix2("[ 1 2 -3 ; 5 6 7 ]");
  ss >> matrix1;

  EXPECT_EQ(matrix1, matrix2);
}

TEST(Matrix, OperatorOstream) {
  std::stringstream ss;
  std::string string1("[ 1 2 -3 ; 5 6 7 ]");
  Matrix matrix1("[ 1 2 -3 ; 5 6 7 ]");
  
  ss << matrix1;

  EXPECT_EQ(matrix1, string1);
}
