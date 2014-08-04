#include <gtest/gtest.h>
#include "../vector/kth_cprog_vektor_bool.cpp"

class SizeTest : public ::testing::TestWithParam<size_t> {};
INSTANTIATE_TEST_CASE_P(VectorBool, SizeTest, ::testing::Range(static_cast<size_t>(0), static_cast<size_t>(3000)));

typedef Vector<bool> Vec;

TEST(VectorBool, InternalRoundupFunction) {
  const size_t STORAGE_CELL_SIZE = 32;
  EXPECT_EQ(0, roundUp(0, STORAGE_CELL_SIZE));
  for(size_t s = 1; s <= 32; ++s) {
    EXPECT_EQ(1, roundUp(s, STORAGE_CELL_SIZE));
  }
  for(size_t s = 33; s <= 64; ++s) {
    EXPECT_EQ(2, roundUp(s, STORAGE_CELL_SIZE));
  }
  EXPECT_EQ(3, roundUp(65, STORAGE_CELL_SIZE));
}

TEST(VectorBool, ConstructorDefault) {
  EXPECT_NO_THROW({
    Vec vector;
  });
}

TEST(VectorBool, ConstructorCopy) {
  const size_t size = 4;
  Vec vector1(size);

  vector1[1] = false;
  vector1[2] = true;

  Vec vector2(vector1);

  EXPECT_EQ(vector1.size(), vector2.size());
  for (size_t i = 0; i < vector1.size(); ++i) {
    EXPECT_EQ(vector1[i], vector2[i]);
  }

  vector1[1] = true;

  vector2[3] = true;

  EXPECT_EQ(false, vector1[0]);
  EXPECT_EQ(true, vector1[1]);
  EXPECT_EQ(true, vector1[2]);
  EXPECT_EQ(false, vector1[3]);

  EXPECT_EQ(false, vector2[0]);
  EXPECT_EQ(false, vector2[1]);
  EXPECT_EQ(true, vector2[2]);
  EXPECT_EQ(true, vector2[3]);
}

TEST(VectorBool, ConstructorInitlist) {
  Vec vector({ true, false, true, false });

  EXPECT_EQ(true, vector[0]);
  EXPECT_EQ(false, vector[1]);
  EXPECT_EQ(true, vector[2]);
  EXPECT_EQ(false, vector[3]);
  EXPECT_EQ(4, vector.size());
}

TEST(VectorBool, ConstructorMove) {
  std::unique_ptr<Vec> vector1(new Vec({ true, false, true, false }));

  EXPECT_EQ(true, (*vector1)[0]);
  std::unique_ptr<Vec> vector2(std::move(vector1));
  EXPECT_EQ(true, (*vector2)[0]);
}

TEST_P(SizeTest, ConstructorSize) {
  const size_t size = GetParam();
  Vec vector(size);
  EXPECT_EQ(size, vector.size());

  for(size_t i = 0; i < size; ++i) {
    EXPECT_EQ(false, vector[i]);
  }
}

TEST_P(SizeTest, ConstructorRepeatFalse) {
  const size_t size = GetParam();
  Vec vector(size, false);
  for (size_t i = 0; i < size; i++) {
    EXPECT_FALSE(vector[i]);
  }
}

TEST_P(SizeTest, ConstructorRepeatTrue) {
  const size_t size = GetParam();
  Vec vector(size, true);
  for (size_t i = 0; i < size; i++) {
    EXPECT_TRUE(vector[i]);
  }
}

TEST(VectorBool, OperatorBracketWrite) {
  const size_t size = 4;

  Vec vector(size);
  EXPECT_EQ(false, vector[0]);

  vector[0] = false;
  vector[1] = true;
  vector[2] = false;
  vector[3] = true;

  EXPECT_EQ(false, vector[0]);
  EXPECT_EQ(true, vector[1]);
  EXPECT_EQ(false, vector[2]);
  EXPECT_EQ(true, vector[3]);
}

TEST_P(SizeTest, OperatorBracketWriteRange) {
  const size_t size = GetParam();
  Vec vector(size);

  EXPECT_THROW({
    vector[size] = false;
  }, std::out_of_range);
  EXPECT_THROW({
    vector[size] = true;
  }, std::out_of_range);

  EXPECT_THROW({
    vector[-1] = false;
  }, std::out_of_range);
  EXPECT_THROW({
    vector[-1] = true;
  }, std::out_of_range);
}

TEST_P(SizeTest, OperatorBracketConstRange) {
  const size_t size = GetParam();
  Vec vector(size);

  EXPECT_THROW({
    vector[size];
  }, std::out_of_range);

  EXPECT_THROW({
    vector[-1];
  }, std::out_of_range);
}

TEST_P(SizeTest, OperatorBracketConstAllFalse) {
  const size_t size = GetParam();
  const Vec vector(size, false);

  for(size_t i = 0; i < size; ++i) {
    EXPECT_FALSE(vector[i]);
  }
}

TEST_P(SizeTest, OperatorBracketConstAllTrue) {
  const size_t size = GetParam();
  const Vec vector(size, true);

  for(size_t i = 0; i < size; ++i) {
    EXPECT_TRUE(vector[i]);
  }
}

TEST(VectorBool, OperatorBracketConstAlternatingTrueFirst) {
  std::initializer_list<bool> list = {true, false, true, false, true, false};
  const Vec vector(list);
  for(size_t i = 0; i < list.size(); ) {
    EXPECT_TRUE(vector[i++]);
    EXPECT_FALSE(vector[i++]);
  }
}

TEST(VectorBool, OperatorBracketConstAlternatingFalseFirst) {
  std::initializer_list<bool> list = {false, true, false, true, false, true};
  const Vec vector(list);
  for(size_t i = 0; i < list.size(); ) {
    EXPECT_FALSE(vector[i++]);
    EXPECT_TRUE(vector[i++]);
  }
}

TEST(VectorBool, OperatorAssignment) {
  const size_t size = 4;
  Vec vector1(size);

  vector1[1] = true;
  Vec vector2 = vector1;
  vector1[2] = false;
  vector2[3] = true;

  EXPECT_EQ(true, vector1[1]);
  EXPECT_EQ(false, vector2[1]);

  EXPECT_EQ(false, vector1[2]);
  EXPECT_EQ(false, vector1[3]);

  EXPECT_EQ(false, vector2[2]);
  EXPECT_EQ(true, vector2[3]);
}

TEST(VectorBool, OperatorAssignmentSelf) {
  Vec vector = { true, false, true, false };

  EXPECT_EQ(true, vector[0]);
  EXPECT_EQ(false, vector[1]);
  EXPECT_EQ(true, vector[2]);
  EXPECT_EQ(false, vector[3]);

  vector = vector;

  EXPECT_EQ(4, vector.size());

  EXPECT_EQ(true, vector[0]);
  EXPECT_EQ(false, vector[1]);
  EXPECT_EQ(true, vector[2]);
  EXPECT_EQ(false, vector[3]);
}

TEST(VectorBool, OperatorAssignmentList) {
  Vec vector = { true, false, true, false };

  EXPECT_EQ(true, vector[0]);
  EXPECT_EQ(false, vector[1]);
  EXPECT_EQ(true, vector[2]);
  EXPECT_EQ(false, vector[3]);
  EXPECT_EQ(4, vector.size());
}

TEST(VectorBool, OperatorAssignmentMove) {
  std::unique_ptr<Vec> vector1(new Vec({ true, false, true, false }));

  EXPECT_EQ(true, (*vector1)[0]);
  std::unique_ptr<Vec> vector2;
  vector2 = std::move(vector1);
  EXPECT_EQ(true, (*vector2)[0]);
}

TEST(VectorBool, PushBack) {
  Vec vector;

  for (size_t i = 0; i < 32; i++) {
    EXPECT_EQ(i, vector.size());
    vector.push_back(true);
    EXPECT_EQ(true, vector[i]);
    EXPECT_EQ(i + 1, vector.size());
  }

  for (size_t i = 0; i < 32; i++) {
    EXPECT_EQ(true, vector[i]);
  }
}

TEST(VectorBool, Insert) {
  const size_t size = 4;
  Vec vector(size);

  EXPECT_EQ(false, vector[1]);
  vector.insert(1, true);
  EXPECT_EQ(true, vector[1]);
  EXPECT_EQ(size + 1, vector.size());
}

TEST(VectorBool, InsertALotOfItems) {
  const size_t size = 1;
  const size_t final_size = 1024;
  Vec vector(size);

  for (size_t i = 0; i < final_size; i++)
  {
    vector.insert(vector.size(), true);
  }

  EXPECT_EQ(final_size, vector.size());
}

TEST(VectorBool, InsertBeginning) {
  const size_t size = 4;
  Vec vector(size);

  EXPECT_EQ(false, vector[1]);
  vector.insert(0, true);
  EXPECT_EQ(true, vector[0]);
  EXPECT_EQ(size + 1, vector.size());
}

TEST(VectorBool, InsertEnd) {
  const size_t size = 4;
  Vec vector(size);

  EXPECT_EQ(false, vector[1]);
  vector.insert(vector.size(), true);
  EXPECT_EQ(true, vector[size]);
  EXPECT_EQ(size + 1, vector.size());
}

TEST(VectorBool, InsertRange) {
  const size_t size = 4;
  Vec vector(size);

  EXPECT_THROW({
    vector.insert(size + 2, true);
  }, std::out_of_range);
}

TEST(VectorBool, Erase) {
  const size_t size = 4;
  Vec vector(size);

  vector[1] = false;
  vector[2] = true;

  vector.erase(1);
  EXPECT_EQ(size - 1, vector.size());
  EXPECT_EQ(true, vector[1]);

}

TEST(VectorBool, EraseRange) {
  const size_t size = 4;
  Vec vector(size);

  EXPECT_THROW({
    vector.erase(size);
  }, std::out_of_range);
}

TEST_P(SizeTest, Clear) {
  const size_t size = GetParam();
  Vec vector(size);

  vector.clear();
  EXPECT_EQ(0, vector.size());
}

TEST(VectorBool, SortAscending) {
  const size_t size = 4;
  Vec vector(size);

  vector[0] = true;
  vector[1] = false;
  vector[2] = true;
  vector[3] = false;

  vector.sort();

  EXPECT_EQ(false, vector[0]);
  EXPECT_EQ(false, vector[1]);
  EXPECT_EQ(true, vector[2]);
  EXPECT_EQ(true, vector[3]);
}

TEST(VectorBool, SortDescending) {
  const size_t size = 4;
  Vec vector(size);

  vector[0] = true;
  vector[1] = false;
  vector[2] = true;
  vector[3] = false;

  vector.sort(false);

  EXPECT_EQ(true, vector[0]);
  EXPECT_EQ(true, vector[1]);
  EXPECT_EQ(false, vector[2]);
  EXPECT_EQ(false, vector[3]);
}

TEST(VectorBool, SortUniqueAscending) {
  const size_t size = 4;
  Vec vector(size);

  vector[0] = true;
  vector[1] = false;
  vector[2] = true;
  vector[3] = false;

  vector.unique_sort();

  EXPECT_EQ(2, vector.size());

  EXPECT_EQ(false, vector[0]);
  EXPECT_EQ(true, vector[1]);
}

TEST(VectorBool, SortUniqueDescending) {
  const size_t size = 4;
  Vec vector(size);

  vector[0] = true;
  vector[1] = false;
  vector[2] = true;
  vector[3] = false;

  vector.unique_sort(false);

  EXPECT_EQ(2, vector.size());

  EXPECT_EQ(true, vector[0]);
  EXPECT_EQ(false, vector[1]);
}

TEST(VectorBool, ExistsTrue) {
  const size_t size = 4;
  Vec vector(size, false);
  vector[2] = true;

  EXPECT_TRUE(vector.exists(true));

  vector[3] = false;
  EXPECT_TRUE(vector.exists(false));
}

TEST_P(SizeTest, ExistsFalse) {
  const size_t size = GetParam();
  Vec vector(size, false);

  EXPECT_FALSE(vector.exists(true));
}

TEST_P(SizeTest, Size) {
  const size_t size = GetParam();
  Vec vector(size);

  EXPECT_EQ(size, vector.size());
}

TEST(VectorBool, ItrBeginEnd) {
  Vec vector1({ true, false, true, false });
  Vec vector2;

  for (Vec::iterator itr = vector1.begin(); itr != vector1.end(); ++itr)
  {
    vector2.push_back(*itr);
  }

  EXPECT_EQ(vector1.size(), vector2.size());
  EXPECT_EQ(vector1[0], vector2[0]);
  EXPECT_EQ(vector1[1], vector2[1]);
  EXPECT_EQ(vector1[2], vector2[2]);
  EXPECT_EQ(vector1[3], vector2[3]);
}

TEST(VectorBool, ItrCBeginEnd) {
  const Vec vector1({ true, false, true, false });
  Vec vector2;

  for (Vec::const_iterator itr = vector1.begin(); itr != vector1.end(); ++itr)
  {
    vector2.push_back(*itr);
  }

  EXPECT_EQ(vector1.size(), vector2.size());
  EXPECT_EQ(vector1[0], vector2[0]);
  EXPECT_EQ(vector1[1], vector2[1]);
  EXPECT_EQ(vector1[2], vector2[2]);
  EXPECT_EQ(vector1[3], vector2[3]);
}

TEST(VectorBool, ItrRBeginEnd) {
  Vec vector1({ true, false, true, false });
  Vec vector2({ false, true, false, true });
  Vec vector3;

  for (Vec::reverse_iterator itr = vector1.rbegin(); itr != vector1.rend(); ++itr)
  {
    vector3.push_back(*itr);
  }

  EXPECT_EQ(vector2.size(), vector3.size());
  EXPECT_EQ(vector2[0], vector3[0]);
  EXPECT_EQ(vector2[1], vector3[1]);
  EXPECT_EQ(vector2[2], vector3[2]);
  EXPECT_EQ(vector2[3], vector3[3]);
}

TEST(VectorBool, ItrRCBeginEnd) {
  const Vec vector1({ true, false, true, false });
  Vec vector2({ false, true, false, true });
  Vec vector3;

  for (Vec::const_reverse_iterator itr = vector1.rbegin(); itr != vector1.rend(); ++itr)
  {
    vector3.push_back(*itr);
  }

  EXPECT_EQ(vector2.size(), vector3.size());
  EXPECT_EQ(vector2[0], vector3[0]);
  EXPECT_EQ(vector2[1], vector3[1]);
  EXPECT_EQ(vector2[2], vector3[2]);
  EXPECT_EQ(vector2[3], vector3[3]);
}

TEST(VectorBool, OperatorNot) {
  const Vec vector1({ true, false, true, false });
  const Vec vector2({ false, true, false, true });

  EXPECT_EQ(vector1, ~vector2);
}

TEST(VectorBool, OperatorAnd) {
  const Vec vector1({ true, false, true, true });
  const Vec vector2({ false, true, false, true });
  const Vec vector3({ false, false, false, true });

  EXPECT_EQ(vector3, vector1 & vector2);
}

TEST(VectorBool, OperatorAndSize) {
  const Vec vector1({ true, false, true, true });
  const Vec vector2({ false, true, false });

  EXPECT_THROW({
    Vec vector3 = vector1 & vector2;
  }, std::invalid_argument);
}

TEST(VectorBool, OperatorOr) {
  const Vec vector1({ true, false, true, false });
  const Vec vector2({ false, true, false, false });
  const Vec vector3({ true, true, true, false });

  EXPECT_EQ(vector3, vector1 | vector2);
}

TEST(VectorBool, OperatorOrSize) {
  const Vec vector1({ true, false, true, true });
  const Vec vector2({ false, true, false });

  EXPECT_THROW({
    Vec vector3 = vector1 | vector2;
  }, std::invalid_argument);
}

TEST(VectorBool, OperatorXor) {
  const Vec vector1({ true, false, true, false });
  const Vec vector2({ false, true, true, false });
  const Vec vector3({ true, true, false, false });

  EXPECT_EQ(vector3, vector1 ^ vector2);
}

TEST(VectorBool, OperatorXorSize) {
  const Vec vector1({ true, false, true, true });
  const Vec vector2({ false, true, false });

  EXPECT_THROW({
    Vec vector3 = vector1 ^ vector2;
  }, std::invalid_argument);
}

TEST(VectorBool, OperatorEqualFalseSize) {
  const Vec vector1({ true, false, true, true });
  const Vec vector2({ false, true, false });

  EXPECT_NE(vector1, vector2);
}

TEST(VectorBool, OperatorEqualFalseValue) {
  const Vec vector1({ true, false, true, true });
  const Vec vector2({ false, true, false, true });

  EXPECT_NE(vector1, vector2);
}

TEST(VectorBool, OperatorEqualTrue) {
  const Vec vector1({ true, false, true, true });
  const Vec vector2({ true, false, true, true });

  EXPECT_EQ(vector1, vector2);
}

TEST(VectorBool, OperatorEqualEdgeCase) {
  Vec vector1({ true, false, true, true, false });
  Vec vector2({ true, false, true, true, true });

  vector1.erase(vector1.size());
  vector2.erase(vector2.size());

  EXPECT_EQ(vector1, vector2);
}

TEST(VectorBool, Weight1) {
  const Vec vector1({
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
  });

  EXPECT_EQ(20, vector1.weight1());
}

TEST(VectorBool, Weight2) {
  const Vec vector1({
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
  });

  EXPECT_EQ(20, vector1.weight2());
}

TEST(VectorBool, Weight3) {
  const Vec vector1({
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
  });

  EXPECT_EQ(20, vector1.weight3());
}
