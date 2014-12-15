#include <gtest/gtest.h>
#include "kth_cprog_vektor_bool.h"

using ::testing::TestWithParam;
using ::testing::Bool;
using ::testing::Combine;
using ::testing::Range;
using ::testing::Values;

#define BLOCK_SIZE sizeof(unsigned int) * CHAR_BIT
#define SIZES Values(0, 1, BLOCK_SIZE-1, BLOCK_SIZE, BLOCK_SIZE+1, 100)

class SizeTest : public TestWithParam<int> {};
INSTANTIATE_TEST_CASE_P(VectorBool, SizeTest, SIZES);

class SizeSizeTest : public TestWithParam<std::tuple<int, int> > {};
INSTANTIATE_TEST_CASE_P(VectorBool, SizeSizeTest, Combine(SIZES, SIZES));

class SizeBoolTest : public TestWithParam<std::tuple<int, bool> > {};
INSTANTIATE_TEST_CASE_P(VectorBool, SizeBoolTest, Combine(SIZES, Bool()));

class SizeBoolBoolTest : public TestWithParam<std::tuple<int, bool, bool> > {};
INSTANTIATE_TEST_CASE_P(VectorBool, SizeBoolBoolTest, Combine(SIZES, Bool(), Bool()));

class SizeSizeBoolTest : public TestWithParam<std::tuple<int, int, bool> > {};
INSTANTIATE_TEST_CASE_P(VectorBool, SizeSizeBoolTest, Combine(SIZES, SIZES, Bool()));

typedef Vector<bool> Vec;

class AlternatingVectorsTest : public TestWithParam<Vec> {};
INSTANTIATE_TEST_CASE_P(VectorBool, AlternatingVectorsTest, Values(
  Vec(0)
  ,Vec({ true })
  ,Vec({ false })
  ,Vec({ true, false })
  ,Vec({ false, true })
  ,Vec({ true, false, true })
  ,Vec({ false, true, false })
  ,Vec({ true, false, true, false })
  ,Vec({ false, true, false, true })
  ,Vec({ // 31
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true
  })
  ,Vec({ // 31
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false
  })
  ,Vec({ // 32
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false
  })
  ,Vec({ // 32
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true
  })
  ,Vec({ // 33
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true
  })
  ,Vec({ // 33
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false
  })
  ,Vec({ // 63
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true
  })
  ,Vec({ // 63
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false
  })
  ,Vec({ // 64
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false
  })
  ,Vec({ // 64
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true
  })
  ,Vec({ // 65
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true
  })
  ,Vec({ // 65
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false
  })
));

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
  const Vec vector1_31({
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true,
  });
  const Vec vector2_31({
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false,
  });
  const Vec vector3_31 = {
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true,
  };
  const Vec vector4_31 = {
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false,
  };

  EXPECT_EQ(31, vector1_31.size());
  EXPECT_EQ(31, vector2_31.size());
  EXPECT_EQ(31, vector3_31.size());
  EXPECT_EQ(31, vector4_31.size());
  for(size_t i = 0; i < 30; i += 2) {
    EXPECT_TRUE(vector1_31[i]);
    EXPECT_FALSE(vector1_31[i+1]);
    EXPECT_FALSE(vector2_31[i]);
    EXPECT_TRUE(vector2_31[i+1]);
    EXPECT_TRUE(vector3_31[i]);
    EXPECT_FALSE(vector3_31[i+1]);
    EXPECT_FALSE(vector4_31[i]);
    EXPECT_TRUE(vector4_31[i+1]);
  }

  const Vec vector1_32({
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
  });
  const Vec vector2_32({
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
  });
  const Vec vector3_32 = {
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
  };
  const Vec vector4_32 = {
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
  };

  EXPECT_EQ(32, vector1_32.size());
  EXPECT_EQ(32, vector2_32.size());
  EXPECT_EQ(32, vector3_32.size());
  EXPECT_EQ(32, vector4_32.size());
  for(size_t i = 0; i < 31; i += 2) {
    EXPECT_TRUE(vector1_32[i]);
    EXPECT_FALSE(vector1_32[i+1]);
    EXPECT_FALSE(vector2_32[i]);
    EXPECT_TRUE(vector2_32[i+1]);
    EXPECT_TRUE(vector3_32[i]);
    EXPECT_FALSE(vector3_32[i+1]);
    EXPECT_FALSE(vector4_32[i]);
    EXPECT_TRUE(vector4_32[i+1]);
  }

  const Vec vector1_33({
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true
  });
  const Vec vector2_33({
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false
  });
  const Vec vector3_33 = {
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true
  };
  const Vec vector4_33 = {
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false
  };

  EXPECT_EQ(33, vector1_33.size());
  EXPECT_EQ(33, vector2_33.size());
  EXPECT_EQ(33, vector3_33.size());
  EXPECT_EQ(33, vector4_33.size());
  for(size_t i = 0; i < 32; i += 2) {
    EXPECT_TRUE(vector1_33[i]);
    EXPECT_FALSE(vector1_33[i+1]);
    EXPECT_FALSE(vector2_33[i]);
    EXPECT_TRUE(vector2_33[i+1]);
    EXPECT_TRUE(vector3_33[i]);
    EXPECT_FALSE(vector3_33[i+1]);
    EXPECT_FALSE(vector4_33[i]);
    EXPECT_TRUE(vector4_33[i+1]);
  }

  const Vec vector1_63({
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true,
  });
  const Vec vector2_63({
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false,
  });
  const Vec vector3_63 = {
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true,
  };
  const Vec vector4_63 = {
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false,
  };

  EXPECT_EQ(63, vector1_63.size());
  EXPECT_EQ(63, vector2_63.size());
  EXPECT_EQ(63, vector3_63.size());
  EXPECT_EQ(63, vector4_63.size());
  for(size_t i = 0; i < 62; i += 2) {
    EXPECT_TRUE(vector1_63[i]);
    EXPECT_FALSE(vector1_63[i+1]);
    EXPECT_FALSE(vector2_63[i]);
    EXPECT_TRUE(vector2_63[i+1]);
    EXPECT_TRUE(vector3_63[i]);
    EXPECT_FALSE(vector3_63[i+1]);
    EXPECT_FALSE(vector4_63[i]);
    EXPECT_TRUE(vector4_63[i+1]);
  }

  const Vec vector1_64({
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
  });
  const Vec vector2_64({
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
  });
  const Vec vector3_64 = {
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
  };
  const Vec vector4_64 = {
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
  };

  EXPECT_EQ(64, vector1_64.size());
  EXPECT_EQ(64, vector2_64.size());
  EXPECT_EQ(64, vector3_64.size());
  EXPECT_EQ(64, vector4_64.size());
  for(size_t i = 0; i < 63; i += 2) {
    EXPECT_TRUE(vector1_64[i]);
    EXPECT_FALSE(vector1_64[i+1]);
    EXPECT_FALSE(vector2_64[i]);
    EXPECT_TRUE(vector2_64[i+1]);
    EXPECT_TRUE(vector3_64[i]);
    EXPECT_FALSE(vector3_64[i+1]);
    EXPECT_FALSE(vector4_64[i]);
    EXPECT_TRUE(vector4_64[i+1]);
  }

  const Vec vector1_65({
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true
  });
  const Vec vector2_65({
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false
  });
  const Vec vector3_65 = {
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false, true
  };
  const Vec vector4_65 = {
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true, false
  };

  EXPECT_EQ(65, vector1_65.size());
  EXPECT_EQ(65, vector2_65.size());
  EXPECT_EQ(65, vector3_65.size());
  EXPECT_EQ(65, vector4_65.size());
  for(size_t i = 0; i < 64; i += 2) {
    EXPECT_TRUE(vector1_65[i]);
    EXPECT_FALSE(vector1_65[i+1]);
    EXPECT_FALSE(vector2_65[i]);
    EXPECT_TRUE(vector2_65[i+1]);
    EXPECT_TRUE(vector3_65[i]);
    EXPECT_FALSE(vector3_65[i+1]);
    EXPECT_FALSE(vector4_65[i]);
    EXPECT_TRUE(vector4_65[i+1]);
  }
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
  const size_t size = 70;

  Vec vector(size, false);

  for(size_t i = 0; i < size; ++i) {
    vector[i] = i % 2 == 0;
  }
  for(size_t i = 0; i < size; ++i) {
    EXPECT_EQ(i % 2 == 0, vector[i]);
  }

  for(size_t i = 0; i < size; ++i) {
    vector[i] = i % 2 != 0;
  }
  for(size_t i = 0; i < size; ++i) {
    EXPECT_EQ(i % 2 != 0, vector[i]);
  }
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
  const Vec vector(size);

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
  std::initializer_list<bool> list = {
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
    true, false, true, false, true, false, true, false,
  };
  const Vec vector(list);
  for(size_t i = 0; i < list.size(); ) {
    EXPECT_TRUE(vector[i++]);
    EXPECT_FALSE(vector[i++]);
  }
}

TEST(VectorBool, OperatorBracketConstAlternatingFalseFirst) {
  std::initializer_list<bool> list = {
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
  };
  const Vec vector(list);
  for(size_t i = 0; i < list.size(); ) {
    EXPECT_FALSE(vector[i++]);
    EXPECT_TRUE(vector[i++]);
  }
}

TEST(VectorBool, OperatorAssignment) {
  Vec vector1({
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
    false, true, false, true, false, true, false, true,
  });
  Vec vector2({false});
  vector2 = vector1;

  EXPECT_EQ(vector1.size(), vector2.size());
  for(size_t i = 0; i < vector1.size(); ++i) {
    EXPECT_EQ(vector1[i], vector2[i]);
  }

  vector1[0] = true;
  vector1[31] = false;

  vector2[1] = false;
  vector2[32] = true;

  EXPECT_EQ(true, vector1[0]);
  EXPECT_EQ(true, vector1[1]);
  EXPECT_EQ(false, vector1[31]);
  EXPECT_EQ(false, vector1[32]);

  EXPECT_EQ(false, vector2[0]);
  EXPECT_EQ(false, vector2[1]);
  EXPECT_EQ(true, vector2[31]);
  EXPECT_EQ(true, vector2[32]);
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

TEST(VectorBool, OperatorAssignmentMove) {
  std::unique_ptr<Vec> vector1(new Vec({ true, false, true, false }));

  EXPECT_EQ(true, (*vector1)[0]);
  std::unique_ptr<Vec> vector2;
  vector2 = std::move(vector1);
  EXPECT_EQ(true, (*vector2)[0]);
}

TEST_P(SizeTest, PushBack) {
  const size_t size = GetParam();
  const size_t append_amount = 10;
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

TEST_P(SizeTest, InsertRange) {
  const size_t size = GetParam();

  EXPECT_NO_THROW({
    Vec vector(size);
    vector.insert(size, true);
    vector.insert(0, true);
  });

  EXPECT_THROW({
    Vec vector(size);
    vector.insert(size + 1, true);
    vector.insert(-1, true);
  }, std::out_of_range);
}

class EraseOneItemTest : public TestWithParam<std::tuple<int, int> > {};
INSTANTIATE_TEST_CASE_P(VectorBool, EraseOneItemTest, Combine(Values(70), Values(0, 1, BLOCK_SIZE-1, BLOCK_SIZE, BLOCK_SIZE+1)));
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
INSTANTIATE_TEST_CASE_P(VectorBool, EraseManyItemsTest, Combine(Values(66), Values(0, 1, 0, 1, BLOCK_SIZE - 1, BLOCK_SIZE, BLOCK_SIZE + 1), Values(0, 1, BLOCK_SIZE - 1, BLOCK_SIZE, BLOCK_SIZE + 1)));
TEST_P(EraseManyItemsTest, EraseManyItems) {
  const size_t size = std::get<0>(GetParam());
  const size_t erase_index = std::get<1>(GetParam());
  const size_t erase_amount = std::get<2>(GetParam());
  Vec vector(size, false);

  for(size_t i = erase_index; i < erase_index + erase_amount; ++i) {
    vector[i] = true;
  }

  for(size_t i = 0; i < erase_amount; ++i) {
    vector.erase(erase_index);
  }

  EXPECT_EQ(size - erase_amount, vector.size());
  EXPECT_FALSE(vector.exists(true));
}

TEST_P(SizeTest, EraseRange) {
  const size_t size = GetParam();
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

class BoolTest : public TestWithParam<bool> {};
INSTANTIATE_TEST_CASE_P(VectorBool, BoolTest, Bool());
TEST_P(BoolTest, SortUnique) {
  const size_t size = 4;
  const bool ascending = GetParam();
  Vec vector(size);

  vector[0] = true;
  vector[1] = false;
  vector[2] = true;
  vector[3] = false;

  vector.unique_sort(ascending);

  EXPECT_EQ(2, vector.size());

  if(ascending) {
    EXPECT_EQ(false, vector[0]);
    EXPECT_EQ(true, vector[1]);
  } else {
    EXPECT_EQ(true, vector[0]);
    EXPECT_EQ(false, vector[1]);
  }
}

TEST_P(SizeSizeBoolTest, Exists) {
  const size_t size = std::get<0>(GetParam());
  const size_t needle_index = std::get<1>(GetParam());
  const bool needle_value = std::get<2>(GetParam());

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

TEST_P(AlternatingVectorsTest, ForwardIteratorAgreesWithIndexOperator) {
  Vec v = GetParam();

  int i = 0;
  Vec::iterator it = v.begin();
  for(; i < v.size() && it != v.end(); ++i, ++it) {
    EXPECT_EQ(v[i], *it);
  }
  EXPECT_EQ(v.end(), it);
}

TEST_P(AlternatingVectorsTest, ForwardConstIteratorAgreesWithIndexOperator) {
  const Vec v = GetParam();

  int i = 0;
  Vec::const_iterator it = v.begin();
  for(; i < v.size() && it != v.end(); ++i, ++it) {
    EXPECT_EQ(v[i], *it);
  }
  EXPECT_EQ(v.end(), it);
}

TEST_P(AlternatingVectorsTest, ItrBeginEnd) {
  Vec vector1 = GetParam();
  Vec vector2;

  for(Vec::iterator itr = vector1.begin(); itr != vector1.end(); ++itr) {
    vector2.push_back(*itr);
  }

  ASSERT_EQ(vector1.size(), vector2.size());
  for(size_t i = 0; i < vector1.size(); ++i) {
    EXPECT_EQ(vector1[i], vector2[i]);
  }
}

TEST_P(AlternatingVectorsTest, ItrCBeginEnd) {
  const Vec vector1 = GetParam();
  Vec vector2;

  for(Vec::const_iterator itr = vector1.begin(); itr != vector1.end(); ++itr) {
    vector2.push_back(*itr);
  }

  ASSERT_EQ(vector1.size(), vector2.size());
  for(size_t i = 0; i < vector1.size(); ++i) {
    EXPECT_EQ(vector1[i], vector2[i]);
  }
}

TEST_P(AlternatingVectorsTest, ItrRBeginEnd) {
  Vec vector1 = GetParam();
  Vec vector2;

  for(Vec::reverse_iterator itr = vector1.rbegin(); itr != vector1.rend(); ++itr) {
    vector2.push_back(*itr);
  }

  ASSERT_EQ(vector1.size(), vector2.size());
  for(size_t i = 0; i < vector1.size(); ++i) {
    EXPECT_EQ(vector1[i], vector2[vector1.size() - i - 1]);
  }
}

TEST_P(AlternatingVectorsTest, ItrRCBeginEnd) {
  const Vec vector1 = GetParam();
  Vec vector2;

  for(Vec::const_reverse_iterator itr = vector1.rbegin(); itr != vector1.rend(); ++itr) {
    vector2.push_back(*itr);
  }

  ASSERT_EQ(vector1.size(), vector2.size());
  for(size_t i = 0; i < vector1.size(); ++i) {
    EXPECT_EQ(vector1[i], vector2[vector1.size() - i - 1]);
  }
}

TEST_P(AlternatingVectorsTest, OperatorNot) {
  const Vec& vector = GetParam();
  const Vec neg_vector = ~vector;

  ASSERT_EQ(vector.size(), neg_vector.size());

  for(size_t i = 0; i < vector.size(); ++i) {
    EXPECT_EQ(vector[i], !neg_vector[i]);
  }
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

TEST_P(SizeSizeTest, OperatorEqualFalseSize) {
  const size_t size1 = std::get<0>(GetParam());
  const size_t size2 = std::get<1>(GetParam());

  if(size1 != size2) {
    const Vec vector1(size1);
    const Vec vector2(size2);

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

TEST_P(SizeSizeBoolTest, OperatorEqualTrue) {
  const size_t size = std::get<0>(GetParam());
  const size_t different_index = std::get<1>(GetParam());
  const bool value = std::get<2>(GetParam());

  Vec vector1(size, value);
  Vec vector2(size, value);

  EXPECT_EQ(vector1, vector2);

  if(different_index < size) {
    vector1[different_index] = !value;
    vector2[different_index] = !value;

    EXPECT_EQ(vector1, vector2);
  }
}

TEST_P(SizeBoolBoolTest, OperatorEqualComparesTheRightBits) {
  const size_t size = std::get<0>(GetParam());
  const bool base_value = std::get<1>(GetParam());
  const bool differing_value = std::get<2>(GetParam());

  Vec vector1(size, base_value);
  Vec vector2(size, base_value);

  vector1.push_back(differing_value);
  vector2.push_back(!differing_value);

  vector1.erase(vector1.size() - 1);
  vector2.erase(vector2.size() - 1);

  EXPECT_EQ(vector1, vector2);
}

TEST_P(AlternatingVectorsTest, OperatorEqualWithAlternatingVectors) {
  const Vec& vector = GetParam();
  const Vec copy(vector);
  EXPECT_EQ(vector, copy);

  const Vec neg = ~vector;
  const Vec neg_copy(neg);
  EXPECT_EQ(neg, neg_copy);
}

TEST_P(SizeTest, Weight1) {
  const size_t size = GetParam();
  Vec vector(size);
  for(size_t i = 0; i < size; ++i) {
    vector[i] = (i % 2) == 1;
  }
  const Vec before(vector);

  EXPECT_EQ(size / 2, vector.weight1());

  EXPECT_EQ(before.size(), vector.size());
  for(size_t i = 0; i < vector.size(); ++i) {
    EXPECT_EQ(before[i], vector[i]) << "Vector has changed.";
  }
}

TEST_P(AlternatingVectorsTest, ConvertToUnsignedInteger) {
  const Vec vector = GetParam();
  if(vector.size() > sizeof(unsigned int) * CHAR_BIT) {
    EXPECT_THROW({
      static_cast<unsigned int>(GetParam());
    }, std::runtime_error);
  } else {
    const unsigned int vec_i = GetParam();

    for(size_t i = 0; i < vector.size() && i < sizeof(unsigned int)*CHAR_BIT; ++i) {
      EXPECT_EQ(vector[i], (vec_i & (1<<i)) != 0);
    }
    if(vector.size() < sizeof(unsigned int) * CHAR_BIT) {
      EXPECT_EQ(vec_i >> vector.size(), 0);
    }
  }
}

TEST(VectorBool, StreamInput) {
  std::cout << Vec({true, false, true, false, false, true, true, false}) << std::endl;
}
