#include <gtest/gtest.h>
#include "kattistime.h"
#include "gregorian.h"

using ::testing::TestWithParam;
using ::testing::Values;

class EpochSecondsToGregorianDateTest : public TestWithParam<std::tuple<long long, int, int, int>> {};
INSTANTIATE_TEST_CASE_P(GregorianDate, EpochSecondsToGregorianDateTest, Values(
  std::tuple<long long, int, int, int>{ -62167219200LL,    0,  1,  1 },
  std::tuple<long long, int, int, int>{ -62167132801LL,    0,  1,  1 },
  std::tuple<long long, int, int, int>{ -62167132800LL,    0,  1,  2 },
  std::tuple<long long, int, int, int>{ -62135596801LL,    1,  1,  1 },
  std::tuple<long long, int, int, int>{ -62135596800LL,    1,  1,  1 },

  std::tuple<long long, int, int, int>{  -3506716801LL, 1858, 11, 16 },
  std::tuple<long long, int, int, int>{  -3506716800LL, 1858, 11, 17 },
  std::tuple<long long, int, int, int>{  -3506716799LL, 1858, 11, 17 },

  std::tuple<long long, int, int, int>{           -1LL, 1969, 12, 31 },
  std::tuple<long long, int, int, int>{            0LL, 1970,  1,  1 },
  std::tuple<long long, int, int, int>{            1LL, 1970,  1,  1 },
  std::tuple<long long, int, int, int>{     60*60*24LL, 1970,  1,  2 },

  std::tuple<long long, int, int, int>{  -2203977600LL, 1900,  2, 28 },
  std::tuple<long long, int, int, int>{  -2203891201LL, 1900,  2, 28 },
  std::tuple<long long, int, int, int>{  -2203891200LL, 1900,  3,  1 },

  std::tuple<long long, int, int, int>{    951696000LL, 2000,  2, 28 },
  std::tuple<long long, int, int, int>{    951782399LL, 2000,  2, 28 },
  std::tuple<long long, int, int, int>{    951782400LL, 2000,  2, 29 },
  std::tuple<long long, int, int, int>{    951868799LL, 2000,  2, 29 },
  std::tuple<long long, int, int, int>{    951868800LL, 2000,  3,  1 },

  std::tuple<long long, int, int, int>{   1330387200LL, 2012,  2, 28 },
  std::tuple<long long, int, int, int>{   1330473599LL, 2012,  2, 28 },
  std::tuple<long long, int, int, int>{   1330473600LL, 2012,  2, 29 },
  std::tuple<long long, int, int, int>{   1330559999LL, 2012,  2, 29 },
  std::tuple<long long, int, int, int>{   1330560000LL, 2012,  3,  1 },

  std::tuple<long long, int, int, int>{   1393545600LL, 2014,  2, 28 },
  std::tuple<long long, int, int, int>{   1393631999LL, 2014,  2, 28 },
  std::tuple<long long, int, int, int>{   1393632000LL, 2014,  3,  1 },

  std::tuple<long long, int, int, int>{   1414976494LL, 2014, 11,  3 },
  std::tuple<long long, int, int, int>{   1415059199LL, 2014, 11,  3 },
  std::tuple<long long, int, int, int>{   1415059200LL, 2014, 11,  4 },
  std::tuple<long long, int, int, int>{   1415059201LL, 2014, 11,  4 }
));

class ValidGregorianDateTest : public TestWithParam<std::tuple<int, int, int>> {};
INSTANTIATE_TEST_CASE_P(GregorianDate, ValidGregorianDateTest, Values(
  std::tuple<int, int, int>{    0,  1,  1 },
  std::tuple<int, int, int>{ 1858, 11, 30 },
  std::tuple<int, int, int>{ 1904,  2, 29 },
  std::tuple<int, int, int>{ 2004,  2, 29 },
  std::tuple<int, int, int>{ 1969, 12, 31 },
  std::tuple<int, int, int>{ 1970,  1,  1 },
  std::tuple<int, int, int>{ 1970,  1,  2 },
  std::tuple<int, int, int>{ 2012,  2, 28 },
  std::tuple<int, int, int>{ 2012,  2, 29 },

  std::tuple<int, int, int>{ 2014,  1,  1 },
  std::tuple<int, int, int>{ 2014,  1, 31 },
  std::tuple<int, int, int>{ 2014,  2,  1 },
  std::tuple<int, int, int>{ 2014,  2, 28 },
  std::tuple<int, int, int>{ 2014,  3,  1 },
  std::tuple<int, int, int>{ 2014,  3, 31 },
  std::tuple<int, int, int>{ 2014,  4,  1 },
  std::tuple<int, int, int>{ 2014,  4, 30 },
  std::tuple<int, int, int>{ 2014,  5,  1 },
  std::tuple<int, int, int>{ 2014,  5, 31 },
  std::tuple<int, int, int>{ 2014,  6,  1 },
  std::tuple<int, int, int>{ 2014,  6, 30 },
  std::tuple<int, int, int>{ 2014,  7,  1 },
  std::tuple<int, int, int>{ 2014,  7, 31 },
  std::tuple<int, int, int>{ 2014,  8,  1 },
  std::tuple<int, int, int>{ 2014,  8, 31 },
  std::tuple<int, int, int>{ 2014,  9,  1 },
  std::tuple<int, int, int>{ 2014,  9, 30 },
  std::tuple<int, int, int>{ 2014, 10,  1 },
  std::tuple<int, int, int>{ 2014, 10, 31 },
  std::tuple<int, int, int>{ 2014, 11,  1 },
  std::tuple<int, int, int>{ 2014, 11,  3 },
  std::tuple<int, int, int>{ 2014, 11,  4 },
  std::tuple<int, int, int>{ 2014, 11, 30 },
  std::tuple<int, int, int>{ 2014, 12,  1 },
  std::tuple<int, int, int>{ 2014, 12, 31 }
));

class InvalidGregorianDateTest : public TestWithParam<std::tuple<int, int, int>> {};
INSTANTIATE_TEST_CASE_P(GregorianDate, InvalidGregorianDateTest, Values(
  std::tuple<int, int, int>{    0,  0,  0 },
  std::tuple<int, int, int>{ 1858, 11, 31 },
  std::tuple<int, int, int>{ 1900,  2, 29 },
  std::tuple<int, int, int>{ 2014,  1, 32 },
  std::tuple<int, int, int>{ 2014,  2, 29 },
  std::tuple<int, int, int>{ 2014,  3, 32 },
  std::tuple<int, int, int>{ 2014,  4, 31 },
  std::tuple<int, int, int>{ 2014,  5, 32 },
  std::tuple<int, int, int>{ 2014,  6, 31 },
  std::tuple<int, int, int>{ 2014,  7, 32 },
  std::tuple<int, int, int>{ 2014,  8, 32 },
  std::tuple<int, int, int>{ 2014,  9, 31 },
  std::tuple<int, int, int>{ 2014, 10, 32 },
  std::tuple<int, int, int>{ 2014, 11, 31 },
  std::tuple<int, int, int>{ 2014, 12, 32 }
));

class GregorianDateAddMonthTest : public TestWithParam<std::tuple<int, int, int, int, int, int, int>> {};
INSTANTIATE_TEST_CASE_P(GregorianDate, GregorianDateAddMonthTest, Values(
  //                                               y0, m0, d0, N,   y1, m1, d1
  std::tuple<int, int, int, int, int, int, int>{    0,  1,  1, 1,    0,  2,  1 },

  std::tuple<int, int, int, int, int, int, int>{ 1858, 11, 30, 1, 1858, 12, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 1858, 12, 30, 1, 1859,  1, 30 },

  std::tuple<int, int, int, int, int, int, int>{ 1970,  1, 28, 1, 1970,  2, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 1970,  1, 29, 1, 1970,  2, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 1970,  1, 30, 1, 1970,  3,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 1970,  1, 31, 1, 1970,  3,  2 },

  std::tuple<int, int, int, int, int, int, int>{ 1972,  1, 28, 1, 1972,  2, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 1972,  1, 29, 1, 1972,  2, 29 },
  std::tuple<int, int, int, int, int, int, int>{ 1972,  1, 30, 1, 1972,  2, 29 },
  std::tuple<int, int, int, int, int, int, int>{ 1972,  1, 31, 1, 1972,  3,  1 },

  std::tuple<int, int, int, int, int, int, int>{ 2014,  1,  1, 1, 2014,  2,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  2,  1, 1, 2014,  3,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  3,  1, 1, 2014,  4,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  4,  1, 1, 2014,  5,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  5,  1, 1, 2014,  6,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  6,  1, 1, 2014,  7,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  7,  1, 1, 2014,  8,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  8,  1, 1, 2014,  9,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  9,  1, 1, 2014, 10,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014, 10,  1, 1, 2014, 11,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014, 11,  1, 1, 2014, 12,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014, 12,  1, 1, 2015,  1,  1 },

  std::tuple<int, int, int, int, int, int, int>{ 2014,  1, 31, 1, 2014,  3,  2 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  2, 28, 1, 2014,  3, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  3, 31, 1, 2014,  4, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  4, 30, 1, 2014,  5, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  5, 31, 1, 2014,  6, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  6, 30, 1, 2014,  7, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  7, 31, 1, 2014,  8, 31 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  8, 31, 1, 2014,  9, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  9, 30, 1, 2014, 10, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014, 10, 31, 1, 2014, 11, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014, 11, 30, 1, 2014, 12, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014, 12, 31, 1, 2015,  1, 31 }
));

INSTANTIATE_TEST_CASE_P(GregorianDateAddMultipleMonths, GregorianDateAddMonthTest, Values(
  std::tuple<int, int, int, int, int, int, int>{ 1900,  1, 31,  2, 1900,  4,  2 },
  std::tuple<int, int, int, int, int, int, int>{ 1900,  2, 28,  3, 1900,  5, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 1900,  3, 31,  4, 1900,  7, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 1900,  4, 30,  5, 1900,  9, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 1900,  5, 31,  6, 1900, 11, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 1900,  6, 30,  7, 1901,  1, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 1900,  7, 31,  8, 1901,  4,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 1900,  8, 31,  9, 1901,  6,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 1900,  9, 30, 10, 1901,  8,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 1900, 10, 31, 11, 1901, 10,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 1900, 11, 30, 12, 1901, 12,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 1900, 12, 31, 13, 1902,  2,  2 },

  std::tuple<int, int, int, int, int, int, int>{ 2014,  1, 31,  2, 2014,  4,  2 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  2, 28,  3, 2014,  5, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  3, 31,  4, 2014,  7, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  4, 30,  5, 2014,  9, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  5, 31,  6, 2014, 11, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  6, 30,  7, 2015,  1, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  7, 31,  8, 2015,  4,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  8, 31,  9, 2015,  6,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  9, 30, 10, 2015,  8,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014, 10, 31, 11, 2015, 10,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014, 11, 30, 12, 2015, 12,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014, 12, 31, 13, 2016,  2,  2 }
));

class GregorianDateAddNegativeMonthTest : public TestWithParam<std::tuple<int, int, int, int, int, int, int>> {};
INSTANTIATE_TEST_CASE_P(GregorianDate, GregorianDateAddNegativeMonthTest, Values(
  //                                                 y0, m0, d0, N,   y1, m1, d1
  std::tuple<int, int, int, int, int, int, int>{ 2014, 12, 31,  -1, 2014, 12,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014, 11, 30,  -2, 2014,  9, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014, 10, 31,  -3, 2014,  8, 1  },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  9, 30,  -4, 2014,  5, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  8, 31,  -5, 2014,  4,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  7, 31,  -6, 2014,  2,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  6, 30,  -7, 2013, 11, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  5, 31,  -8, 2013, 10,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  4, 30,  -9, 2013,  7, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  3, 31, -10, 2013,  6,  1 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  2, 28, -11, 2013,  3, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 2014,  1, 31, -12, 2013,  2,  1 }
));

class GregorianDateAddYearTest : public TestWithParam<std::tuple<int, int, int, int, int, int, int>> {};
INSTANTIATE_TEST_CASE_P(GregorianDate, GregorianDateAddYearTest, Values(
  //                                               y0, m0, d0,   N,   y1, m1, d1
  std::tuple<int, int, int, int, int, int, int>{    0,  1,  1,   1,    1,  1,  1 },

  std::tuple<int, int, int, int, int, int, int>{ 1858, 11, 30,   1, 1859, 11, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 1858, 12, 30,   1, 1859, 12, 30 },

  std::tuple<int, int, int, int, int, int, int>{ 1970,  1, 28,   1, 1971,  1, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 1970,  1, 29,   1, 1971,  1, 29 },
  std::tuple<int, int, int, int, int, int, int>{ 1970,  1, 30,   1, 1971,  1, 30 },
  std::tuple<int, int, int, int, int, int, int>{ 1970,  1, 31,   1, 1971,  1, 31 },

  std::tuple<int, int, int, int, int, int, int>{ 1971,  2, 28,   1, 1972,  2, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 1972,  2, 29,   1, 1973,  2, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 1972,  2, 29,   4, 1976,  2, 29 },
  std::tuple<int, int, int, int, int, int, int>{ 1972,  2, 29,  28, 2000,  2, 29 },
  std::tuple<int, int, int, int, int, int, int>{ 1972,  2, 29, 128, 2100,  2, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 1972,  2, 29, 428, 2400,  2, 29 },

  std::tuple<int, int, int, int, int, int, int>{ 1972,  2, 29,  -1, 1971,  2, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 1973,  2, 28,  -1, 1972,  2, 28 }
));

class GregorianDateWeekdayTest : public TestWithParam<std::tuple<int, int, int, int>> {};
INSTANTIATE_TEST_CASE_P(GregorianDate, GregorianDateWeekdayTest, Values(
  std::tuple<int, int, int, int>{ 3, 1858, 11, 17 },

  std::tuple<int, int, int, int>{ 4, 1970,  1,  1 },

  std::tuple<int, int, int, int>{ 6, 2014, 11,  1 },
  std::tuple<int, int, int, int>{ 7, 2014, 11,  2 },
  std::tuple<int, int, int, int>{ 1, 2014, 11,  3 },
  std::tuple<int, int, int, int>{ 2, 2014, 11,  4 },
  std::tuple<int, int, int, int>{ 3, 2014, 11,  5 }
));

using lab2::Date;
using lab2::GregorianDate;

TEST_P(EpochSecondsToGregorianDateTest, DefaultConstructorSetsResultToToday) {
  const long long current_epoch_seconds = std::get<0>(GetParam());
  const int expected_year = std::get<1>(GetParam());
  const int expected_month = std::get<2>(GetParam());
  const int expected_day = std::get<3>(GetParam());

  set_k_time(current_epoch_seconds);
  const GregorianDate d;

  EXPECT_EQ(expected_year, d.year());
  EXPECT_EQ(expected_month, d.month());
  EXPECT_EQ(expected_day, d.day());
}

TEST_P(ValidGregorianDateTest, YmdConstructorFailsForInvalidDates) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  EXPECT_NO_THROW({
    GregorianDate d(year, month, day);
  });
}

TEST_P(InvalidGregorianDateTest, YmdConstructorFailsForInvalidDates) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  EXPECT_THROW({
    GregorianDate d(year, month, day);
  }, std::out_of_range);
}

TEST_P(ValidGregorianDateTest, YmdConstructorSetsResultToArgument) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  const GregorianDate d(year, month, day);

  EXPECT_EQ(year, d.year());
  EXPECT_EQ(month, d.month());
  EXPECT_EQ(day, d.day());
}

TEST_P(ValidGregorianDateTest, CopyConstructorMakesResultEqualToArgument) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  const GregorianDate gda{year, month, day};
  const Date& da = gda;
  const GregorianDate gdb{da};

  EXPECT_EQ(da, gdb);
  EXPECT_EQ(0, da - gdb);
}

TEST_P(ValidGregorianDateTest, CopyConstructorDoesNotModifyOriginal) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  const GregorianDate gda{year, month, day};
  const Date& da = gda;

  ASSERT_EQ(year, da.year());
  ASSERT_EQ(month, da.month());
  ASSERT_EQ(day, da.day());

  const GregorianDate gdb{da};

  EXPECT_EQ(year, da.year());
  EXPECT_EQ(month, da.month());
  EXPECT_EQ(day, da.day());
}

TEST_P(ValidGregorianDateTest, OperatorAssignmentSetsSelfEqualToArgument) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  const GregorianDate gda{year, month, day};
  const Date& da = gda;

  GregorianDate gdb{};
  Date& db = gdb;

  db = da;

  EXPECT_EQ(year, db.year());
  EXPECT_EQ(month, db.month());
  EXPECT_EQ(day, db.day());

  EXPECT_EQ(year, gdb.year());
  EXPECT_EQ(month, gdb.month());
  EXPECT_EQ(day, gdb.day());

  EXPECT_EQ(0, db - da);
  EXPECT_EQ(0, gdb - da);
}

TEST_P(ValidGregorianDateTest, OperatorAssignmentDoesNotModifyOriginal) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  const GregorianDate gda{year, month, day};
  const Date& da = gda;

  ASSERT_EQ(year, da.year());
  ASSERT_EQ(month, da.month());
  ASSERT_EQ(day, da.day());

  GregorianDate gdb{};
  Date& db = gdb;

  db = da;

  EXPECT_EQ(year, da.year());
  EXPECT_EQ(month, da.month());
  EXPECT_EQ(day, da.day());
}

TEST_P(GregorianDateAddMonthTest, AddMonthAddsOneMonthIfPossibleOtherwiseAdds30Days) {
  const int year_before = std::get<0>(GetParam());
  const int month_before = std::get<1>(GetParam());
  const int day_before = std::get<2>(GetParam());

  const int num_months = std::get<3>(GetParam());

  const int year_after = std::get<4>(GetParam());
  const int month_after = std::get<5>(GetParam());
  const int day_after = std::get<6>(GetParam());

  GregorianDate gda{year_before, month_before, day_before};
  GregorianDate gdb{year_before, month_before, day_before};

  ASSERT_EQ(year_before, gda.year());
  ASSERT_EQ(month_before, gda.month());
  ASSERT_EQ(day_before, gda.day());
  ASSERT_EQ(gda, gdb);

  gda.add_month(num_months);
  for(int i = 0; i < num_months; ++i) {
      gdb.add_month();
  }

  EXPECT_EQ(year_after, gda.year());
  EXPECT_EQ(month_after, gda.month());
  EXPECT_EQ(day_after, gda.day());

  EXPECT_EQ(year_after, gdb.year());
  EXPECT_EQ(month_after, gdb.month());
  EXPECT_EQ(day_after, gdb.day());
}

TEST_P(GregorianDateAddNegativeMonthTest, AddNegativeMonthsSubtractsOneMonthIfPossibleOtherwiseSubtracts30Days) {
  const int year_before = std::get<0>(GetParam());
  const int month_before = std::get<1>(GetParam());
  const int day_before = std::get<2>(GetParam());

  const int num_months = std::get<3>(GetParam());

  const int year_after = std::get<4>(GetParam());
  const int month_after = std::get<5>(GetParam());
  const int day_after = std::get<6>(GetParam());

  GregorianDate gda{year_before, month_before, day_before};
  GregorianDate gdb{year_before, month_before, day_before};

  ASSERT_EQ(year_before, gda.year());
  ASSERT_EQ(month_before, gda.month());
  ASSERT_EQ(day_before, gda.day());
  ASSERT_EQ(gda, gdb);

  gda.add_month(num_months);
  for(int i = 0; i > num_months; --i) {
      gdb.add_month(-1);
  }

  EXPECT_EQ(year_after, gda.year());
  EXPECT_EQ(month_after, gda.month());
  EXPECT_EQ(day_after, gda.day());

  EXPECT_EQ(year_after, gdb.year());
  EXPECT_EQ(month_after, gdb.month());
  EXPECT_EQ(day_after, gdb.day());
}

TEST_P(GregorianDateAddYearTest, AddYearMovesToSameDayOnAnotherYearAndLeapDayGoesToLastFebruary) {
  const int year_before = std::get<0>(GetParam());
  const int month_before = std::get<1>(GetParam());
  const int day_before = std::get<2>(GetParam());

  const int num_years = std::get<3>(GetParam());

  const int year_after = std::get<4>(GetParam());
  const int month_after = std::get<5>(GetParam());
  const int day_after = std::get<6>(GetParam());

  GregorianDate gd{year_before, month_before, day_before};

  ASSERT_EQ(year_before, gd.year());
  ASSERT_EQ(month_before, gd.month());
  ASSERT_EQ(day_before, gd.day());

  gd.add_year(num_years);

  EXPECT_EQ(year_after, gd.year());
  EXPECT_EQ(month_after, gd.month());
  EXPECT_EQ(day_after, gd.day());
}

TEST_P(GregorianDateWeekdayTest, ExampleDatesHaveCorrectWeekday) {
  const int weekday = std::get<0>(GetParam());
  const int year = std::get<1>(GetParam());
  const int month = std::get<2>(GetParam());
  const int day = std::get<3>(GetParam());

  GregorianDate gd{year, month, day};
  EXPECT_EQ(weekday, gd.week_day());
}
