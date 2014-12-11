#include <gtest/gtest.h>
#include <thread>

//#define LOCK_GLOBAL
#include "kth_cprog_safe_vector.hpp"


template<typename T>
void swapn(SafeVector<T>& vec, size_t i1, size_t i2, int n)
{
  for (int i = 0; i < 2*n; i++) {
    vec.safeswap(0, 1);
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
  std::thread thread2(swapn<int>, std::ref(safe1), 1, 0, n);
  std::thread thread3(swapn<int>, std::ref(safe1), 2, 3, n);
  std::thread thread4(swapn<int>, std::ref(safe1), 3, 2, n);

  thread1.join();
  thread2.join();
  thread3.join();
  thread4.join();

  EXPECT_EQ(1, safe1[0]);
  EXPECT_EQ(2, safe1[1]);
  EXPECT_EQ(3, safe1[2]);
  EXPECT_EQ(4, safe1[3]);
}

