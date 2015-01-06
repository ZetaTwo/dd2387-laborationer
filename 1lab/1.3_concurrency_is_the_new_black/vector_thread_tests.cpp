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

template<typename T>
void swapn(SafeVector<T>& vec, size_t i1, size_t i2, int n)
{
  for (int i = 0; i < n; i++) {
    vec.safeswap(i1, i2);
  }
}

TEST(SafeVector, BasicSwapTest) {
  SafeVector<int> safe1{ 1, 2, 3, 4 };
  safe1.safeswap(0, 1);

  EXPECT_EQ(2, safe1[0]);
  EXPECT_EQ(1, safe1[1]);

  safe1.safeswap(1, 0);

  EXPECT_EQ(1, safe1[0]);
  EXPECT_EQ(2, safe1[1]);
}

TEST(SafeVector, ThreadSwapTest) {
  SafeVector<int> safe1{ 1, 2, 3, 4 };
  
  const int n = 10000;

  std::thread thread1(swapn<int>, std::ref(safe1), 0, 1, n);
  std::thread thread2(swapn<int>, std::ref(safe1), 1, 0, n + 1);
  std::thread thread3(swapn<int>, std::ref(safe1), 2, 3, n);
  std::thread thread4(swapn<int>, std::ref(safe1), 3, 2, n - 1);

  thread1.join();
  thread2.join();
  thread3.join();
  thread4.join();

  EXPECT_EQ(2, safe1[0]);
  EXPECT_EQ(1, safe1[1]);
  EXPECT_EQ(4, safe1[2]);
  EXPECT_EQ(3, safe1[3]);
}

TEST(SafeVector, ThreadSwapTestWithHugeType) {
  typedef LargeType<14> HugeType;
  SafeVector<HugeType> safe1{ 1, 2, 3, 4 };

  const int n = 10000;

  std::thread thread1(swapn<HugeType>, std::ref(safe1), 0, 1, n);
  std::thread thread2(swapn<HugeType>, std::ref(safe1), 1, 0, n + 1);
  std::thread thread3(swapn<HugeType>, std::ref(safe1), 2, 3, n);
  std::thread thread4(swapn<HugeType>, std::ref(safe1), 3, 2, n - 1);

  thread1.join();
  thread2.join();
  thread3.join();
  thread4.join();

  EXPECT_EQ(2, safe1[0]);
  EXPECT_EQ(1, safe1[1]);
  EXPECT_EQ(4, safe1[2]);
  EXPECT_EQ(3, safe1[3]);
}
