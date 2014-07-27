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
