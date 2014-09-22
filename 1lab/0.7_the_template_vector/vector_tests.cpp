#include <gtest/gtest.h>
#include "kth_cprog_vektor.cpp"

TEST(Vector, ConstructorDefault) {
  EXPECT_NO_THROW({
    Vector<int> int_vector;
  });
}

TEST(Vector, ConstructorCopy) {
  const size_t size = 4;
  Vector<int> int_vector1(size);

  int_vector1[1] = 13;
  int_vector1[2] = 14;

  Vector<int> int_vector2(int_vector1);

  for(size_t i = 0; i < int_vector1.size(); ++i) {
    EXPECT_EQ(int_vector1[i], int_vector2[i]);
  }

  int_vector1[1] = 12;

  int_vector2[1] = 23;
  int_vector2[3] = 25;

  EXPECT_EQ(0, int_vector1[0]);
  EXPECT_EQ(12, int_vector1[1]);
  EXPECT_EQ(14, int_vector1[2]);
  EXPECT_EQ(0, int_vector1[3]);

  EXPECT_EQ(0, int_vector2[0]);
  EXPECT_EQ(23, int_vector2[1]);
  EXPECT_EQ(14, int_vector2[2]);
  EXPECT_EQ(25, int_vector2[3]);
}

TEST(Vector, ConstructorInitlist) {
  Vector<int> int_vector({ 13, 14, 15, 16 });

  EXPECT_EQ(13, int_vector[0]);
  EXPECT_EQ(14, int_vector[1]);
  EXPECT_EQ(15, int_vector[2]);
  EXPECT_EQ(16, int_vector[3]);
  EXPECT_EQ(4, int_vector.size());
}

TEST(Vector, ConstructorMove) {
  std::unique_ptr<Vector<int> > int_vector1(new Vector<int> ({ 13, 14, 15, 16 }));

  EXPECT_EQ(13, (*int_vector1)[0]);
  std::unique_ptr<Vector<int> > int_vector2(std::move(int_vector1));
  EXPECT_EQ(13, (*int_vector2)[0]);
}

TEST(Vector, ConstructorSize) {
  const size_t size = 32;

  Vector<int> int_vector(size);
  EXPECT_EQ(size, int_vector.size());

  for(size_t i = 0; i < size; i++) {
    EXPECT_EQ(0, int_vector[i]);
  }
}

TEST(Vector, ConstructorZeroSize) {
  const size_t size = 0;

  Vector<int> int_vector(size);
  EXPECT_EQ(size, int_vector.size());
}

TEST(Vector, ConstructorRepeat) {
  const size_t size = 4;

  Vector<int> int_vector(size, 13);
  for(size_t i = 0; i < size; i++) {
    EXPECT_EQ(13, int_vector[i]);
  }
}

TEST(Vector, OperatorBracketWrite) {
  const size_t size = 4;

  Vector<int> int_vector(size);
  EXPECT_EQ(0, int_vector[0]);

  int_vector[0] = 10;
  int_vector[1] = 20;
  int_vector[2] = 30;
  int_vector[3] = 40;

  EXPECT_EQ(10, int_vector[0]);
  EXPECT_EQ(20, int_vector[1]);
  EXPECT_EQ(30, int_vector[2]);
  EXPECT_EQ(40, int_vector[3]);
}

TEST(Vector, OperatorBracketRange) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  EXPECT_THROW({
    int_vector[size];
  }, std::out_of_range);

  EXPECT_THROW({
    int_vector[-1];
  }, std::out_of_range);
}

TEST(Vector, OperatorBracketConst) {
  const Vector<int> int_vector(4, 13);

  EXPECT_EQ(13, int_vector[0]);
  EXPECT_EQ(13, int_vector[1]);
  EXPECT_EQ(13, int_vector[2]);
  EXPECT_EQ(13, int_vector[3]);
}

TEST(Vector, OperatorAssignment) {
  const size_t size = 4;
  Vector<int> int_vector1(size);

  int_vector1[1] = 13;
  Vector<int> int_vector2 = int_vector1;
  int_vector1[2] = 14;
  int_vector2[3] = 15;

  EXPECT_EQ(13, int_vector1[1]);
  EXPECT_EQ(13, int_vector2[1]);

  EXPECT_EQ(14, int_vector1[2]);
  EXPECT_EQ(0, int_vector1[3]);

  EXPECT_EQ(0, int_vector2[2]);
  EXPECT_EQ(15, int_vector2[3]);
}

TEST(Vector, OperatorAssignmentSelf) {
  Vector<int> int_vector = { 13, 14, 15, 16 };

  EXPECT_EQ(13, int_vector[0]);
  EXPECT_EQ(14, int_vector[1]);
  EXPECT_EQ(15, int_vector[2]);
  EXPECT_EQ(16, int_vector[3]);

  int_vector = int_vector;

  EXPECT_EQ(4, int_vector.size());

  EXPECT_EQ(13, int_vector[0]);
  EXPECT_EQ(14, int_vector[1]);
  EXPECT_EQ(15, int_vector[2]);
  EXPECT_EQ(16, int_vector[3]);
}

TEST(Vector, OperatorAssignmentList) {
  Vector<int> int_vector = { 13, 14, 15, 16 };

  EXPECT_EQ(13, int_vector[0]);
  EXPECT_EQ(14, int_vector[1]);
  EXPECT_EQ(15, int_vector[2]);
  EXPECT_EQ(16, int_vector[3]);
  EXPECT_EQ(4, int_vector.size());
}

TEST(Vector, OperatorAssignmentMove) {
  std::unique_ptr<Vector<int> > int_vector1(new Vector<int>({ 13, 14, 15, 16 }));

  EXPECT_EQ(13, (*int_vector1)[0]);
  std::unique_ptr<Vector<int> > int_vector2 = std::move(int_vector1);
  EXPECT_EQ(13, (*int_vector2)[0]);
}

TEST(Vector, PushBack) {
  Vector<int> int_vector;

  for(size_t i = 0; i < 32; i++) {
    EXPECT_EQ(i, int_vector.size());
    int_vector.push_back(i);
    EXPECT_EQ(i, int_vector[i]);
    EXPECT_EQ(i+1, int_vector.size());
  }

  for(size_t i = 0; i < 32; i++) {
    EXPECT_EQ(i, int_vector[i]);
  }
}

TEST(Vector, Insert) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  EXPECT_EQ(0, int_vector[1]);
  int_vector.insert(1, 13);
  EXPECT_EQ(13, int_vector[1]);
  EXPECT_EQ(size + 1, int_vector.size());
}

TEST(Vector, InsertALotOfItems) {
  const size_t size = 1;
  const size_t final_size = 10000;
  Vector<int> int_vector(size);

  while(int_vector.size() < final_size) {
    int_vector.insert(int_vector.size(), int_vector.size());
  }

  EXPECT_EQ(final_size, int_vector.size());
}

TEST(Vector, InsertBeginning) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  EXPECT_EQ(0, int_vector[1]);
  int_vector.insert(0, 13);
  EXPECT_EQ(13, int_vector[0]);
  EXPECT_EQ(size + 1, int_vector.size());
}

TEST(Vector, InsertEnd) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  EXPECT_EQ(0, int_vector[1]);
  int_vector.insert(int_vector.size(), 13);
  EXPECT_EQ(13, int_vector[size]);
  EXPECT_EQ(size + 1, int_vector.size());
}

TEST(Vector, InsertRange) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  EXPECT_THROW({
    int_vector.insert(size+2, 13);
  }, std::out_of_range);
}

TEST(Vector, Erase) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  int_vector[1] = 13;
  int_vector[2] = 14;

  int_vector.erase(1);
  EXPECT_EQ(size - 1, int_vector.size());
  EXPECT_EQ(14, int_vector[1]);
  
}

TEST(Vector, EraseRange) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  EXPECT_THROW({
    int_vector.erase(size);
  }, std::out_of_range);
}

TEST(Vector, Clear) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  int_vector.clear();
  EXPECT_EQ(0, int_vector.size());
}

TEST(Vector, SortAscending) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  int_vector[0] = 40;
  int_vector[1] = 20;
  int_vector[2] = 30;
  int_vector[3] = 10;

  int_vector.sort();

  EXPECT_EQ(10, int_vector[0]);
  EXPECT_EQ(20, int_vector[1]);
  EXPECT_EQ(30, int_vector[2]);
  EXPECT_EQ(40, int_vector[3]);
}

TEST(Vector, SortDescending) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  int_vector[0] = 40;
  int_vector[1] = 20;
  int_vector[2] = 30;
  int_vector[3] = 10;

  int_vector.sort(false);

  EXPECT_EQ(40, int_vector[0]);
  EXPECT_EQ(30, int_vector[1]);
  EXPECT_EQ(20, int_vector[2]);
  EXPECT_EQ(10, int_vector[3]);
}

TEST(Vector, SortUniqueAscending) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  int_vector[0] = 30;
  int_vector[1] = 20;
  int_vector[2] = 30;
  int_vector[3] = 10;

  int_vector.unique_sort();

  EXPECT_EQ(3, int_vector.size());

  EXPECT_EQ(10, int_vector[0]);
  EXPECT_EQ(20, int_vector[1]);
  EXPECT_EQ(30, int_vector[2]);
}

TEST(Vector, SortUniqueDescending) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  int_vector[0] = 30;
  int_vector[1] = 20;
  int_vector[2] = 30;
  int_vector[3] = 10;

  int_vector.unique_sort(false);

  EXPECT_EQ(3, int_vector.size());

  EXPECT_EQ(30, int_vector[0]);
  EXPECT_EQ(20, int_vector[1]);
  EXPECT_EQ(10, int_vector[2]);
}

TEST(Vector, ExistsTrue) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  int_vector[2] = 13;
  EXPECT_TRUE(int_vector.exists(13));

  int_vector[3] = 15;
  EXPECT_TRUE(int_vector.exists(15));
}

TEST(Vector, ExistsFalse) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  int_vector[2] = 13;

  EXPECT_FALSE(int_vector.exists(14));
}

TEST(Vector, Size) {
  const size_t size = 4;
  Vector<int> int_vector(size);

  EXPECT_EQ(size, int_vector.size());
}

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

TEST(Vector, StreamInput) {
  std::cout << Vector<int>({0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597}) << std::endl;
}