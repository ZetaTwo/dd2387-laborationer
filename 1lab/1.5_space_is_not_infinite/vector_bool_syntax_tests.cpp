#include <gtest/gtest.h>
#include "kth_cprog_vektor_bool.h"

using std::iterator_traits;
using std::move;
using std::swap;
using ::testing::Test;

struct VectorBoolIteratorFixture : Test {
    typedef Vector<bool> Vec;
    typedef Vec::iterator It;
    typedef iterator_traits<It>::difference_type difference;
    typedef iterator_traits<It>::reference reference;
    typedef iterator_traits<It>::value_type value_type;

    Vec v;
    It b;
    It e;

  public:
    void SetUp() {
      b = v.begin();
      e = v.begin();
    }
};
struct VectorBoolConstIteratorFixture : Test {
    typedef const Vector<bool> Vec;
    typedef Vec::const_iterator It;

    Vec v;
    It it;

  public:
    void SetUp() {
      it = v.begin();
    }
};

// RandomAccessIterator

TEST_F(VectorBoolIteratorFixture, IsAdditionAssignable) {
  It& it = b += 0;
}

TEST_F(VectorBoolIteratorFixture, IsRightAdditionable) {
  It it = b + 0;
}

TEST_F(VectorBoolIteratorFixture, IsLeftAdditionable) {
  It it = 0 + b;
}

TEST_F(VectorBoolIteratorFixture, IsSubtractionAssignable) {
  It& it = b -= 0;
}

TEST_F(VectorBoolIteratorFixture, IsRightSubtractible) {
  It it = b - 0;
}

TEST_F(VectorBoolIteratorFixture, IsLeftSubtractible) {
  difference it = e - b;
}

TEST_F(VectorBoolIteratorFixture, IsIndexable) {
  reference it = b[0];
}

TEST_F(VectorBoolIteratorFixture, IsLessComparable) {
  bool a = b < e;
}

TEST_F(VectorBoolIteratorFixture, IsGreaterComparable) {
  bool a = b > e;
}

TEST_F(VectorBoolIteratorFixture, IsGreaterEqualComparable) {
  bool a = b >= e;
}

TEST_F(VectorBoolIteratorFixture, IsLessEqualComparable) {
  bool a = b <= e;
}

// BidirectionalIterator

TEST_F(VectorBoolIteratorFixture, IsPrefixDecrementable) {
  It& it = --b;
}

TEST_F(VectorBoolIteratorFixture, IsPostfixDecrementable) {
  const It& it = b--;
}

TEST_F(VectorBoolIteratorFixture, IsPostfixDecrementDefererencible) {
  reference r = *b--;
}

// ForwardIterator

TEST_F(VectorBoolIteratorFixture, IsPrefixIncrementable) {
  It& it = ++b;
}

TEST_F(VectorBoolIteratorFixture, IsPostfixIncrementable) {
  It it = b++;
}

TEST_F(VectorBoolIteratorFixture, IsPostfixIncrementDereferenceable) {
  reference it = *b++;
}

TEST_F(VectorBoolIteratorFixture, IsPostfixVoidIncrementable) {
  (void)b++;
}

// InputIterator

TEST_F(VectorBoolIteratorFixture, IsNotEqualComparable) {
  bool a = b != e;
}

TEST_F(VectorBoolIteratorFixture, IsAsteriskDereferenceable) {
  value_type v = *b;
}

// operator-> is not applicable: bool a; a.foo is nonsensical

// DefaultConstructible

TEST_F(VectorBoolIteratorFixture, IsDefaultInitializable) {
  It it;
}

TEST_F(VectorBoolIteratorFixture, IsDefaultValueInitializable) {
  It it{};
}

TEST_F(VectorBoolIteratorFixture, IsDefaultTemporaryValueInitializable) {
  It();
  It{};
}

// CopyConstructible

TEST_F(VectorBoolIteratorFixture, IsCopyConstructible) {
  It it1 = b;
  It it2(b);
  It it3{b};
}

// MoveConstructible

TEST_F(VectorBoolIteratorFixture, IsMoveConstructible) {
  It it1 = move(It{});
  It it2(move(It{}));
  It it3{move(It{})};
}

// CopyAssignable

TEST_F(VectorBoolIteratorFixture, IsCopyAssignable) {
  It it;
  it = b;
}

// MoveAssignable

TEST_F(VectorBoolIteratorFixture, IsMoveAssignable) {
  It it;
  it = std::move(It{});
}

// Destructible

TEST_F(VectorBoolIteratorFixture, IsDestructible) {
  b.~It();
}

// Swappable

TEST_F(VectorBoolIteratorFixture, IsSwappable) {
  swap(b, e);
}

// EqualityComparable

TEST_F(VectorBoolIteratorFixture, IsEqualityComparable) {
  bool a = b == e;
}
