#include <gtest/gtest.h>
#include <thread>

//#define LOCK_GLOBAL
#include "kth_cprog_safe_vector.hpp"

template<size_t n>
struct LargeType {
  LargeType<n - 1> a, b;
  LargeType() : LargeType(0) {}
  LargeType(long long int a) : a(a), b(a) {}
  inline bool operator==(const long long int a) const { return this->a == a; }
  inline bool operator==(const LargeType& other) const { return a == other.a; }
};
template<>
struct LargeType<0> {
  long long int a;
  LargeType() : LargeType(0) {}
  LargeType(long long int a) : a(a) {}
  inline bool operator==(const long long int a) const { return this->a == a; }
  inline bool operator==(const LargeType& other) const { return a == other.a; }
};

template<size_t n>
bool operator==(const long long int a, const LargeType<n>& lt) { return lt.a == a; }

typedef LargeType<7> Kibibyte;
typedef LargeType<17> Mebibyte;
typedef LargeType<27> Gibibyte;

template<typename SafeVector>
void swapn(SafeVector& vec, size_t i1, size_t i2, int n)
{
  for (int i = 0; i < n; i++) {
    vec.safeswap(i1, i2);
  }
}

template<class SafeVector>
void run_thread_swap_test(SafeVector& vec, const int n) {
  std::vector<std::thread> threads;

  for(size_t i = 0; i < vec.size(); i += 2) {
    threads.emplace_back(swapn<SafeVector>, std::ref(vec), i, i + 1, n);
    threads.emplace_back(swapn<SafeVector>, std::ref(vec), i + 1,  i, n + (i % 4 == 0 ? 1 : -1));
  }
  for(std::thread& thread : threads) {
    thread.join();
  }
  for(size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(static_cast<int>(i + (i % 2 == 0 ? 1 : -1)), vec[i]);
  }
}

template<typename T>
class SafeVectorTest : public ::testing::Test {};
TYPED_TEST_CASE_P(SafeVectorTest);

TYPED_TEST_P(SafeVectorTest, BasicSwapTest) {
  TypeParam safe1{ 1, 2, 3, 4 };
  safe1.safeswap(0, 1);

  EXPECT_EQ(2, safe1[0]);
  EXPECT_EQ(1, safe1[1]);

  safe1.safeswap(1, 0);

  EXPECT_EQ(1, safe1[0]);
  EXPECT_EQ(2, safe1[1]);
}

TYPED_TEST_P(SafeVectorTest, ThreadSwapTest) {
  TypeParam safe1{ 0, 1, 2, 3 };
  run_thread_swap_test(safe1, 10000);
}

REGISTER_TYPED_TEST_CASE_P(SafeVectorTest,
  BasicSwapTest,
  ThreadSwapTest
);

INSTANTIATE_TYPED_TEST_CASE_P(IndividuallyLockedInt, SafeVectorTest, SafeVector<int>);
INSTANTIATE_TYPED_TEST_CASE_P(GloballyLockedInt, SafeVectorTest, SuperSafeVector<int>);

typedef Kibibyte HugeType;
INSTANTIATE_TYPED_TEST_CASE_P(IndividuallyLockedHuge, SafeVectorTest, SafeVector<HugeType>);
INSTANTIATE_TYPED_TEST_CASE_P(GloballyLockedHuge, SafeVectorTest, SuperSafeVector<HugeType>);
