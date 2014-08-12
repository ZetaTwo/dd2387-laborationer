#include <gtest/gtest.h>
#include "../vector/kth_cprog_vektor_bool.cpp"

using ::testing::TestWithParam;
using ::testing::Bool;
using ::testing::Combine;
using ::testing::Range;
using ::testing::Values;

#define SIZES Values(0, 1, 16, 31, 32, 33, 48, 63, 64, 65, 1000)

class SizeTest : public TestWithParam<int> {};
INSTANTIATE_TEST_CASE_P(VectorBool, SizeTest, SIZES);

class SizeSizeTest : public TestWithParam<std::tuple<int, int> > {};
INSTANTIATE_TEST_CASE_P(VectorBool, SizeSizeTest, Combine(SIZES, SIZES));

class SizeBoolTest : public TestWithParam<std::tuple<int, bool> > {};
INSTANTIATE_TEST_CASE_P(VectorBool, SizeBoolTest, Combine(SIZES, Bool()));

class SizeSizeBoolTest : public TestWithParam<std::tuple<int, int, bool> > {};
INSTANTIATE_TEST_CASE_P(VectorBool, SizeSizeBoolTest, Combine(SIZES, SIZES, Bool()));

typedef Vector<bool> Vec;

TEST(VectorBool, ConstructorDefault) {
  EXPECT_NO_THROW({
    Vec vector;
  });
}

TEST(VectorBool, ConstructorCopy) {
  const size_t size = 65;
  Vec vector1(size, false);

  vector1[31] = true;
  vector1[64] = true;

  Vec vector2(vector1);

  EXPECT_EQ(vector1.size(), vector2.size());
  for(size_t i = 0; i < vector1.size(); ++i) {
    EXPECT_EQ(vector1[i], vector2[i]);
  }

  vector1[32] = true;

  vector2[31] = false;
  vector2[63] = true;

  EXPECT_EQ(true, vector1[31]);
  EXPECT_EQ(true, vector1[32]);
  EXPECT_EQ(false, vector1[63]);
  EXPECT_EQ(true, vector1[64]);

  EXPECT_EQ(false, vector2[31]);
  EXPECT_EQ(false, vector2[32]);
  EXPECT_EQ(true, vector2[63]);
  EXPECT_EQ(true, vector2[64]);
}

TEST(VectorBool, ConstructorCopyAssignment) {
  const size_t size = 65;
  Vec vector1(size, false);

  vector1[31] = true;
  vector1[64] = true;

  Vec vector2 = vector1;

  EXPECT_EQ(vector1.size(), vector2.size());
  for(size_t i = 0; i < vector1.size(); ++i) {
    EXPECT_EQ(vector1[i], vector2[i]);
  }

  vector1[32] = true;

  vector2[31] = false;
  vector2[63] = true;

  EXPECT_EQ(true, vector1[31]);
  EXPECT_EQ(true, vector1[32]);
  EXPECT_EQ(false, vector1[63]);
  EXPECT_EQ(true, vector1[64]);

  EXPECT_EQ(false, vector2[31]);
  EXPECT_EQ(false, vector2[32]);
  EXPECT_EQ(true, vector2[63]);
  EXPECT_EQ(true, vector2[64]);
}

TEST(VectorBool, ConstructorInitlist) {
  const Vec vector1({
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
  });
  const Vec vector2({
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
  });

  EXPECT_EQ(40, vector1.size());
  EXPECT_EQ(40, vector2.size());
  for(size_t i = 0; i < 40; i += 2) {
    EXPECT_TRUE(vector1[i]);
    EXPECT_FALSE(vector1[i+1]);
    EXPECT_FALSE(vector2[i]);
    EXPECT_TRUE(vector2[i+1]);
  }
}

TEST(VectorBool, ConstructorInitlistAssignment) {
  Vec vector = { true, false, true, false };

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
    EXPECT_FALSE(vector[i]);
  }
}

TEST_P(SizeBoolTest, ConstructorRepeat) {
  const size_t size = std::get<0>(GetParam());
  const bool value = std::get<1>(GetParam());
  Vec vector(size, value);
  EXPECT_EQ(size, vector.size());
  for(size_t i = 0; i < size; i++) {
    EXPECT_EQ(value, vector[i]);
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

  if(size > 0) {
    EXPECT_NO_THROW({
      vector[0] = false;
      vector[0] = true;
      vector[size-1] = false;
      vector[size-1] = true;
    });
  }

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

  if(size > 0) {
    EXPECT_NO_THROW({
      vector[0];
      vector[size-1];
    });
  }

  EXPECT_THROW({
    vector[size];
  }, std::out_of_range);

  EXPECT_THROW({
    vector[-1];
  }, std::out_of_range);
}

TEST_P(SizeBoolTest, OperatorBracketConstAllEqual) {
  const size_t size = std::get<0>(GetParam());
  const bool value = std::get<1>(GetParam());
  const Vec vector(size, value);

  for(size_t i = 0; i < size; ++i) {
    EXPECT_EQ(value, vector[i]);
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
  Vec vector1({false, true, false, false});
  Vec vector2({false});
  vector2 = vector1;

  EXPECT_EQ(vector1.size(), vector2.size());
  for(size_t i = 0; i < vector1.size(); ++i) {
    EXPECT_EQ(vector1[i], vector2[i]);
  }

  vector1[0] = true;

  vector2[1] = false;
  vector2[3] = true;

  EXPECT_EQ(true, vector1[0]);
  EXPECT_EQ(true, vector1[1]);
  EXPECT_EQ(false, vector1[3]);

  EXPECT_EQ(false, vector2[0]);
  EXPECT_EQ(false, vector2[1]);
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
  Vec vector;
  vector = { true, false, true, false };

  EXPECT_EQ(4, vector.size());
  EXPECT_EQ(true, vector[0]);
  EXPECT_EQ(false, vector[1]);
  EXPECT_EQ(true, vector[2]);
  EXPECT_EQ(false, vector[3]);
}

TEST(VectorBool, OperatorAssignmentMove) {
  std::unique_ptr<Vec> vector1(new Vec({ true, false, true, false }));

  EXPECT_EQ(true, (*vector1)[0]);
  std::unique_ptr<Vec> vector2;
  vector2 = std::move(vector1);
  EXPECT_EQ(true, (*vector2)[0]);
}

TEST_P(SizeSizeTest, PushBack) {
  const size_t size = std::get<0>(GetParam());
  const size_t append_amount = std::get<1>(GetParam());
  Vec vector(size, false);

  for(size_t i = 0; i < append_amount; ++i) {
    EXPECT_EQ(size + i, vector.size());
    vector.push_back(true);
  }

  EXPECT_EQ(size + append_amount, vector.size());

  for(size_t i = 0; i < size; ++i) {
    EXPECT_FALSE(vector[i]);
  }
  for(size_t i = size; i < size + append_amount; ++i) {
    EXPECT_TRUE(vector[i]);
  }
}

TEST_P(SizeSizeTest, InsertOneItem) {
  const size_t size = std::get<0>(GetParam());
  const size_t insert_index = std::get<1>(GetParam());
  Vec vector(size, false);

  if(insert_index > size) {
    EXPECT_THROW({
      vector.insert(insert_index, true);
    }, std::out_of_range);
  } else {
    vector.insert(insert_index, true);

    EXPECT_EQ(size + 1, vector.size());

    for(size_t i = 0; i < insert_index; ++i) {
      EXPECT_FALSE(vector[i]);
    }
    EXPECT_TRUE(vector[insert_index]);
    for(size_t i = insert_index+1; i < vector.size(); ++i) {
      EXPECT_FALSE(vector[i]);
    }
  }
}

TEST(VectorBool, InsertManyItems) {
  const size_t size = 2;
  const size_t insert_index = 1;
  const size_t insert_amount = 64;
  Vec vector(size);

  for(size_t i = 0; i < insert_amount; i++) {
    vector.insert(insert_index, true);
  }

  EXPECT_EQ(size + insert_amount, vector.size());
  for(size_t i = 0; i < insert_index; ++i) {
    EXPECT_FALSE(vector[i]);
  }
  for(size_t i = insert_index; i < insert_index + insert_amount; ++i) {
    EXPECT_TRUE(vector[i]);
  }
  for(size_t i = insert_index + insert_amount; i < vector.size(); ++i) {
    EXPECT_FALSE(vector[i]);
  }
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

class EraseOneItemTest : public TestWithParam<std::tuple<int, int> > {};
INSTANTIATE_TEST_CASE_P(VectorBool, EraseOneItemTest, Combine(Values(70), Values(0, 1, 16, 31, 32, 33, 48, 63, 64, 65)));
TEST_P(EraseOneItemTest, EraseOneItem) {
  const size_t size = std::get<0>(GetParam());
  const size_t erase_index = std::get<1>(GetParam());
  Vec vector(size, false);

  if(erase_index > 1) {
    vector[erase_index - 2] = true;
  }
  vector[erase_index] = true;
  if(size > 1 && erase_index < size - 2) {
    vector[erase_index + 2] = true;
  }

  vector.erase(erase_index);

  EXPECT_EQ(size - 1, vector.size());

  if(erase_index > 1) {
    EXPECT_TRUE(vector[erase_index - 2]);
  }
  if(erase_index > 0) {
    EXPECT_FALSE(vector[erase_index - 1]);
  }
  if(erase_index < size - 1) {
    EXPECT_FALSE(vector[erase_index]);
  }
  if(erase_index < size - 2) {
    EXPECT_TRUE(vector[erase_index + 1]);
  }
}

class EraseManyItemsTest : public TestWithParam<std::tuple<int, int, int> > {};
INSTANTIATE_TEST_CASE_P(VectorBool, EraseManyItemsTest, Combine(Values(66), Values(0, 1, 16, 31, 32, 33), Values(16, 31, 32, 33)));
TEST_P(EraseManyItemsTest, EraseManyItems) {
  const size_t size = std::get<0>(GetParam());
  const size_t erase_index = std::get<1>(GetParam());
  const size_t erase_amount = std::get<2>(GetParam());
  Vec vector(size, false);

  for(size_t i = erase_index; i < erase_index + erase_amount; ++i) {
    vector[erase_index] = true;
  }

  for(size_t i = 0; i < erase_amount; ++i) {
    vector.erase(erase_index);
  }

  EXPECT_EQ(size - erase_amount, vector.size());
  EXPECT_FALSE(vector.exists(true));
}

TEST(VectorBool, EraseRange) {
  const size_t size = 4;
  Vec vector1(size);
  Vec vector2(size+1);

  EXPECT_THROW({
    vector1.erase(size);
  }, std::out_of_range);
  EXPECT_NO_THROW({
    vector2.erase(size);
  });
}

TEST_P(SizeTest, Clear) {
  const size_t size = GetParam();
  Vec vector(size);

  vector.clear();
  EXPECT_EQ(0, vector.size());
}

TEST_P(SizeSizeBoolTest, Sort) {
  const size_t size = std::get<0>(GetParam());
  const size_t weight = std::get<1>(GetParam());
  const bool ascending = std::get<2>(GetParam());

  if(weight <= size) {
    Vec vector(size, false);

    if(size > 0) {
      const size_t start_index = ascending ? 0 : size - weight;
      for(size_t i = start_index; i < start_index + weight; ++i) {
        vector[i] = 1;
      }
    }
    ASSERT_EQ(weight, vector.weight()) << "Test setup failed.";

    vector.sort(ascending);

    const size_t flip_index = ascending ? size - weight : weight;
    for(size_t i = 0; i < flip_index; ++i) {
      EXPECT_EQ(!ascending, vector[i]);
    }
    for(size_t i = flip_index; i < size; ++i) {
      EXPECT_EQ(ascending, vector[i]);
    }
  }
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

TEST_P(SizeSizeBoolTest, Exists) {
  const size_t size = std::get<0>(GetParam());
  const size_t needle_index = std::get<1>(GetParam());
  const size_t needle_value = std::get<2>(GetParam());

  if(needle_index < size) {
    Vec vector(size, !needle_value);
    ASSERT_FALSE(vector.exists(needle_value));

    vector[needle_index] = needle_value;
    EXPECT_TRUE(vector.exists(needle_value));
  }
}

TEST_P(SizeTest, Size) {
  const size_t size = GetParam();
  Vec vector(size);

  EXPECT_EQ(size, vector.size());
}

TEST(VectorBool, ItrBeginEnd) {
  Vec vector1({ true, false, true, false });
  Vec vector2;

  for(Vec::iterator itr = vector1.begin(); itr != vector1.end(); ++itr) {
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

  for(Vec::const_iterator itr = vector1.begin(); itr != vector1.end(); ++itr) {
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

  for(Vec::reverse_iterator itr = vector1.rbegin(); itr != vector1.rend(); ++itr) {
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

  for(Vec::const_reverse_iterator itr = vector1.rbegin(); itr != vector1.rend(); ++itr) {
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

TEST_P(SizeSizeBoolTest, OperatorEqualFalseSize) {
  const size_t size1 = std::get<0>(GetParam());
  const size_t size2 = std::get<1>(GetParam());
  const bool value = std::get<2>(GetParam());

  if(size1 != size2) {
    const Vec vector1(size1, value);
    const Vec vector2(size2, value);

    EXPECT_NE(vector1, vector2);
  }
}

TEST_P(SizeSizeBoolTest, OperatorEqualFalseValue) {
  const size_t size = std::get<0>(GetParam());
  const size_t differing_index = std::get<1>(GetParam());
  const bool initial_value = std::get<2>(GetParam());

  if(differing_index < size) {
    const Vec vector1(size, initial_value);
    Vec vector2(size, initial_value);

    vector2[differing_index] = !initial_value;

    EXPECT_NE(vector1, vector2);
  }
}

TEST_P(SizeBoolTest, OperatorEqualTrue) {
  const size_t size = std::get<0>(GetParam());
  const bool value = std::get<1>(GetParam());
  const Vec vector1(size, value);
  const Vec vector2(size, value);

  EXPECT_EQ(vector1, vector2);
}

TEST(VectorBool, OperatorEqualComparesTheRightBits) {
  Vec vector1({ true, false, true, true, false });
  Vec vector2({ true, false, true, true, true });

  vector1.erase(vector1.size());
  vector2.erase(vector2.size());

  EXPECT_EQ(vector1, vector2);
}

TEST_P(SizeTest, Weight1) {
  const size_t size = GetParam();
  Vec vector(size);
  for(size_t i = 0; i < size; ++i) {
    vector[i] = i % 2;
  }
  const Vec before(vector);

  EXPECT_EQ(size / 2, vector.weight1());

  EXPECT_EQ(before.size(), vector.size());
  for(size_t i = 0; i < vector.size(); ++i) {
    EXPECT_EQ(before[i], vector[i]) << "Vector has changed.";
  }
}

TEST_P(SizeTest, Weight2) {
  const size_t size = GetParam();
  Vec vector(size);
  for(size_t i = 0; i < size; ++i) {
    vector[i] = i % 2;
  }
  const Vec before(vector);

  EXPECT_EQ(size / 2, vector.weight2());

  EXPECT_EQ(before.size(), vector.size());
  for(size_t i = 0; i < vector.size(); ++i) {
    EXPECT_EQ(before[i], vector[i]) << "Vector has changed.";
  }
}

TEST_P(SizeTest, Weight3) {
  const size_t size = GetParam();
  Vec vector(size);
  for(size_t i = 0; i < size; ++i) {
    vector[i] = i % 2;
  }
  const Vec before(vector);

  EXPECT_EQ(size / 2, vector.weight3());

  EXPECT_EQ(before.size(), vector.size());
  for(size_t i = 0; i < vector.size(); ++i) {
    EXPECT_EQ(before[i], vector[i]) << "Vector has changed.";
  }
}

TEST(VectorBool, StreamInput) {
  std::cout << Vec({true, false, true, false, false, true, true, false}) << std::endl;
}
