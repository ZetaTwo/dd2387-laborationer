#include <gtest/gtest.h>
#include "kth_cprog_template_container.hpp"

TEST(Vector, ItrBeginEnd) {
  Vector<int> vector1({ 1, 2, 3, 4 });
  Vector<int> vector2;

  for (Vector<int>::iterator itr = vector1.begin(); itr != vector1.end(); ++itr)
  {
    vector2.push_back(*itr);
  }

  EXPECT_EQ(vector1.size(), vector2.size());
  EXPECT_EQ(vector1[0], vector2[0]);
  EXPECT_EQ(vector1[1], vector2[1]);
  EXPECT_EQ(vector1[2], vector2[2]);
  EXPECT_EQ(vector1[3], vector2[3]);
}

TEST(Vector, ItFind) {
  Vector<int> vector1({ 1, 2, 3, 4 });

  Vector<int>::iterator itr = vector1.find(3);
  EXPECT_EQ(3, *itr);
  EXPECT_GT(itr, vector1.begin());
  EXPECT_LT(itr, vector1.end());

  itr = vector1.find(5);
  EXPECT_EQ(vector1.end(), itr);

  itr = vector1.find(1);
  EXPECT_EQ(1, *itr);
  EXPECT_EQ(itr, vector1.begin());
  EXPECT_LT(itr, vector1.end());
}


TEST(Vector, ItrCBeginEnd) {
  const Vector<int> vector1({ 1, 2, 3, 4 });
  Vector<int> vector2;

  for (Vector<int>::const_iterator itr = vector1.begin(); itr != vector1.end(); ++itr)
  {
    vector2.push_back(*itr);
  }

  EXPECT_EQ(vector1.size(), vector2.size());
  EXPECT_EQ(vector1[0], vector2[0]);
  EXPECT_EQ(vector1[1], vector2[1]);
  EXPECT_EQ(vector1[2], vector2[2]);
  EXPECT_EQ(vector1[3], vector2[3]);
}

TEST(Vector, ItrRBeginEnd) {
  Vector<int> vector1({ 1, 2, 3, 4 });
  Vector<int> vector2({ 4, 3, 2, 1 });
  Vector<int> vector3;

  for (Vector<int>::reverse_iterator itr = vector1.rbegin(); itr != vector1.rend(); ++itr)
  {
    vector3.push_back(*itr);
  }

  EXPECT_EQ(vector2.size(), vector3.size());
  EXPECT_EQ(vector2[0], vector3[0]);
  EXPECT_EQ(vector2[1], vector3[1]);
  EXPECT_EQ(vector2[2], vector3[2]);
  EXPECT_EQ(vector2[3], vector3[3]);
}

TEST(Vector, ItrRCBeginEnd) {
  const Vector<int> vector1({ 1, 2, 3, 4 });
  Vector<int> vector2({ 4, 3, 2, 1 });
  Vector<int> vector3;

  for (Vector<int>::const_reverse_iterator itr = vector1.rbegin(); itr != vector1.rend(); ++itr)
  {
    vector3.push_back(*itr);
  }

  EXPECT_EQ(vector2.size(), vector3.size());
  EXPECT_EQ(vector2[0], vector3[0]);
  EXPECT_EQ(vector2[1], vector3[1]);
  EXPECT_EQ(vector2[2], vector3[2]);
  EXPECT_EQ(vector2[3], vector3[3]);
}

TEST(Vector, EvilInt3) {
  Vector<int> A(1024, 5);
  Vector<int> B(1024, 6);
  Vector<int> X;

  X = std::move(B);
  B = std::move(A);
  A = std::move(X);

  X.reset();

  EXPECT_EQ(A.end(), A.find(5));
  EXPECT_EQ(A.begin(), A.find(6));

  EXPECT_EQ(B.end(), B.find(6));
  EXPECT_EQ(B.begin(), B.find(5));

  EXPECT_EQ(0, X.size());

  B = B;
  EXPECT_EQ(1024, B.size());
  EXPECT_EQ(5, B[1024 - 1]);

  A = std::move(A);
  EXPECT_EQ(1024, A.size());
  EXPECT_EQ(6, A[1024 - 1]);
}
