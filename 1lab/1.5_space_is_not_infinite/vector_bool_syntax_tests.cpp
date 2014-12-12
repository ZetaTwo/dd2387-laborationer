#include <gtest/gtest.h>
#include "kth_cprog_vektor_bool.hpp"

using std::iterator_traits;
using std::move;
using std::swap;
using ::testing::Test;

typedef Vector<bool> Vec;
typedef Vec::iterator It;
typedef Vec::const_iterator CIt;
typedef iterator_traits<It>::difference_type difference;
typedef iterator_traits<It>::reference reference;
typedef iterator_traits<It>::value_type value_type;

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

// BidirectionalIterator

TEST_F(VectorBoolIterator, IsPrefixDecrementable) {
  It& it = --b;
}

TEST_F(VectorBoolIterator, IsPostfixDecrementable) {
  const It& it = b--;
}

TEST_F(VectorBoolIterator, IsPostfixDecrementDefererencible) {
  reference r = *b--;
}

// ForwardIterator

TEST_F(VectorBoolIterator, IsPrefixIncrementable) {
  It& it = ++b;
}

TEST_F(VectorBoolIterator, IsPostfixIncrementable) {
  It it = b++;
}

TEST_F(VectorBoolIterator, IsPostfixIncrementDereferenceable) {
  reference it = *b++;
}

// InputIterator

TEST_F(VectorBoolIterator, IsNotEqualComparable) {
  bool a = b != e;
}

TEST_F(VectorBoolIterator, IsAsteriskDereferenceable) {
  value_type v = *b;
}

// operator-> is not applicable: bool a; a->foo is nonsensical

// DefaultConstructible

TEST_F(VectorBoolIterator, IsDefaultInitializable) {
  It it;
}

TEST_F(VectorBoolIterator, IsDefaultValueInitializable) {
  It it{};
}

TEST_F(VectorBoolIterator, IsDefaultTemporaryValueInitializable) {
  It();
  It{};
}

// CopyConstructible

TEST_F(VectorBoolIterator, IsCopyConstructible) {
  It it1 = b;
  It it2(b);
  It it3{b};
}

// MoveConstructible

TEST_F(VectorBoolIterator, IsMoveConstructible) {
  It it1 = move(It{});
  It it2(move(It{}));
  It it3{move(It{})};
}

// CopyAssignable

TEST_F(VectorBoolIterator, IsCopyAssignable) {
  It it;
  it = b;
}

// MoveAssignable

TEST_F(VectorBoolIterator, IsMoveAssignable) {
  It it;
  it = std::move(It{});
}

// Destructible

TEST_F(VectorBoolIterator, IsDestructible) {
  b.~It();
}

// Swappable

TEST_F(VectorBoolIterator, IsSwappable) {
  swap(b, e);
}

// EqualityComparable

TEST_F(VectorBoolIterator, IsEqualityComparable) {
  bool a = b == e;
}
