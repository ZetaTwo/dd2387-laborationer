#include <gtest/gtest.h>
#include "hypercube.hpp"

typedef uint8_t byte;

TEST(Hypercube, DefaultConstructorDim1) { Hypercube<byte, 1> h; }
TEST(Hypercube, DefaultConstructorDim2) { Hypercube<byte, 2> h; }
TEST(Hypercube, DefaultConstructorDim3) { Hypercube<byte, 3> h; }
TEST(Hypercube, DefaultConstructorDim4) { Hypercube<byte, 4> h; }
TEST(Hypercube, DefaultConstructorDim5) { Hypercube<byte, 5> h; }
TEST(Hypercube, DefaultConstructorDim6) { Hypercube<byte, 6> h; }
// Memory consumption increases exponentially - with Vector default size 16 a
// Hypercube<byte, 6> is ~16 MB and <byte, 7> is ~260 MB

TEST(Hypercube, SizeConstructorDim1) { Hypercube<byte, 1> h(3); }
TEST(Hypercube, SizeConstructorDim2) { Hypercube<byte, 2> h(3); }
TEST(Hypercube, SizeConstructorDim3) { Hypercube<byte, 3> h(3); }

TEST(Hypercube, IsAHypercube) {
  const size_t dim = 3, size = 5;
  Hypercube<byte, dim> h(size);

  for(size_t i = 0; i < size; ++i) {
    for(size_t j = 0; j < size; ++j) {
      for(size_t k = 0; k < size; ++k) {
        EXPECT_EQ(0, h[i][j][k]);

        EXPECT_THROW({
          h[-1][j][k];
        }, std::out_of_range);
        EXPECT_THROW({
          h[i][-1][k];
        }, std::out_of_range);
        EXPECT_THROW({
          h[i][j][-1];
        }, std::out_of_range);

        EXPECT_THROW({
          h[size][j][k];
        }, std::out_of_range);
        EXPECT_THROW({
          h[i][size][k];
        }, std::out_of_range);
        EXPECT_THROW({
          h[i][j][size];
        }, std::out_of_range);
      }
    }
  }
}

TEST(Hypercube, IndexOperatorAssignmentWorks) {
  Hypercube<byte, 3> h(5);
  h[1][2][3] = 127;
  h[3][1][2] = 128;
  h[2][3][1] = 129;
  EXPECT_EQ(127, h[1][2][3]);
  EXPECT_EQ(128, h[3][1][2]);
  EXPECT_EQ(129, h[2][3][1]);
}

TEST(Hypercube, PartialAssignment) {
  // Copied from lab instructions

  Hypercube<int, 3> n(7); // kub med 7*7*7 element
  Hypercube<int, 6> m(5); // sex dimensioner, 5*5*...*5 element
  m[1][3][2][1][4][0] = 7;

  Hypercube<int, 3> t(5);
  t = m[1][3][2]; // tilldela med del av m

  t[1][4][0] = 2; // ändra t, ändra inte m
  EXPECT_EQ(7, m[1][3][2][1][4][0]);
  EXPECT_EQ(2, t[1][4][0]);
}
