#include <gtest/gtest.h>
#include "../vector/kth_cprog_vektor.cpp"

typedef Vector<int> Vec;
typedef Vector<int>::iterator Iterator;
typedef Vector<int>::const_iterator ConstIterator;
typedef Vector<int>::reverse_iterator ReverseIterator;
typedef Vector<int>::const_reverse_iterator ConstReverseIterator;

TEST(VectorIterator, ConstructorDefault) {
  EXPECT_NO_THROW({
    Iterator itr1;
  });
}

TEST(VectorIterator, ConstructorCopy) {
  Vec vector1{ 1, 2, 3, 4 };
  Iterator itr1 = vector1.begin();
  itr1++;
  EXPECT_EQ(*itr1, 2);
  
  Iterator itr2(itr1);
  itr1++;
  itr2++;
  EXPECT_EQ(*itr1, 3);
  EXPECT_EQ(*itr2, 3);
}

TEST(VectorIterator, OperatorIncrementPost) {
  Vec vector1{ 1, 2, 3, 4 };
  Iterator itr1 = vector1.begin();
  EXPECT_EQ(*itr1++, 1);
  EXPECT_EQ(*itr1++, 2);
  EXPECT_EQ(*itr1++, 3);
}

TEST(VectorIterator, OperatorIncrementPre) {
  Vec vector1{ 1, 2, 3, 4 };
  Iterator itr1 = vector1.begin();
  EXPECT_EQ(*++itr1, 2);
  EXPECT_EQ(*++itr1, 3);
}

TEST(VectorIterator, OperatorDereference) {
  Vec vector1{ 1, 2, 3, 4 };
  Iterator itr1 = vector1.begin();
  EXPECT_EQ(*itr1, 1);
}

TEST(VectorIterator, OperatorIndex) {
  Vec vector1{ 1, 2, 3, 4 };
  Iterator itr1 = vector1.begin();
  EXPECT_EQ(itr1[2], 3);
}

TEST(VectorIteratorConst, OperatorDereference) {
  const Vec vector1{ 1, 2, 3, 4 };
  ConstIterator itr1 = vector1.begin();
  EXPECT_EQ(*itr1, 1);
}

TEST(VectorIteratorConst, OperatorIndex) {
  const Vec vector1{ 1, 2, 3, 4 };
  ConstIterator itr1 = vector1.begin();
  EXPECT_EQ(itr1[2], 3);
}

TEST(VectorIteratorReverse, ConstructorDefault) {
  EXPECT_NO_THROW({
    ReverseIterator itr1;
  });
}

TEST(VectorIteratorReverse, ConstructorVector) {
  Vec vector1{ 1, 2, 3, 4 };
  ReverseIterator itr1 = vector1.rbegin();
  itr1++;
  EXPECT_EQ(*itr1, 3);
}

TEST(VectorIteratorReverse, ConstructorCopy) {
  Vec vector1{ 1, 2, 3, 4 };
  ReverseIterator itr1 = vector1.rbegin();
  int a = *itr1;
  itr1++;
  int b = *itr1;
  EXPECT_EQ((*itr1), 3);

  ReverseIterator itr2 = itr1;
  itr1++;
  itr2++;
  EXPECT_EQ(*itr1, 2);
  EXPECT_EQ(*itr2, 2);
}

TEST(VectorIteratorReverse, OperatorIncrementPost) {
  Vec vector1{ 1, 2, 3, 4 };
  ReverseIterator itr1 = vector1.rbegin();
  EXPECT_EQ(*itr1++, 4);
  EXPECT_EQ(*itr1++, 3);
  EXPECT_EQ(*itr1++, 2);
}

TEST(VectorIteratorReverse, OperatorIncrementPre) {
  Vec vector1{ 1, 2, 3, 4 };
  ReverseIterator itr1 = vector1.rbegin();
  EXPECT_EQ(*++itr1, 3);
  EXPECT_EQ(*++itr1, 2);
}

TEST(VectorIteratorReverse, OperatorDereference) {
  Vec vector1{ 1, 2, 3, 4 };
  ReverseIterator itr1 = vector1.rbegin();
  EXPECT_EQ(*itr1, 4);
}

TEST(VectorIteratorReverse, OperatorIndex) {
  Vec vector1{ 1, 2, 3, 4 };
  ReverseIterator itr1 = vector1.rbegin();
  EXPECT_EQ(itr1[2], 2);
}

TEST(VectorIteratorReverseConst, OperatorDereferenceConst) {
  const Vec vector1{ 1, 2, 3, 4 };
  ConstReverseIterator itr1 = vector1.rbegin();
  EXPECT_EQ(*itr1, 4);
}

TEST(VectorIteratorReverseConst, OperatorIndexConst) {
  const Vec vector1{ 1, 2, 3, 4 };
  ConstReverseIterator itr1 = vector1.rbegin();
  EXPECT_EQ(itr1[2], 2);
}