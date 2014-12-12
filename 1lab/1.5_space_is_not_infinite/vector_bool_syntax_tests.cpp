#include <gtest/gtest.h>
#include "kth_cprog_vektor_bool.hpp"

using std::iterator_traits;
using ::testing::Test;

typedef Vector<bool> Vec;
typedef Vec::iterator It;
typedef Vec::const_iterator CIt;
typedef iterator_traits<It>::difference_type difference;
typedef iterator_traits<It>::reference reference;

struct VectorBoolIterator : Test {
    Vec v;
    Vec::iterator b;
    Vec::iterator e;

  public:
    void SetUp() {
      b = v.begin();
      e = v.begin();
    }
};
struct VectorBoolConstIterator : Test {
    const Vec v;
    Vec::const_iterator it;

  public:
    void SetUp() {
      it = v.begin();
    }
};

// RandomAccessIterator

TEST_F(VectorBoolIterator, IsAdditionAssignable) {
  It& it = b += 0;
}

TEST_F(VectorBoolIterator, IsRightAdditionable) {
  It it = b + 0;
}

TEST_F(VectorBoolIterator, IsLeftAdditionable) {
  It it = 0 + b;
}

TEST_F(VectorBoolIterator, IsSubtractionAssignable) {
  It& it = b -= 0;
}

TEST_F(VectorBoolIterator, IsRightSubtractible) {
  It it = b - 0;
}

TEST_F(VectorBoolIterator, IsLeftSubtractible) {
  difference it = e - b;
}

TEST_F(VectorBoolIterator, IsIndexable) {
  reference it = b[0];
}

TEST_F(VectorBoolIterator, IsLessComparable) {
  bool a = b < e;
}

TEST_F(VectorBoolIterator, IsGreaterComparable) {
  bool a = b > e;
}

TEST_F(VectorBoolIterator, IsGreaterEqualComparable) {
  bool a = b >= e;
}

TEST_F(VectorBoolIterator, IsLessEqualComparable) {
  bool a = b <= e;
}
