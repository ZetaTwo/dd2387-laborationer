#include <gtest/gtest.h>
#include "../vector/hypercube.hpp"

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
