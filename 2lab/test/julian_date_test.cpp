#include <gtest/gtest.h>
#include "kattistime.h"
#include "julian.h"

using ::testing::TestWithParam;
using ::testing::Values;

class EpochSecondsToJulianDateTest : public TestWithParam<std::tuple<long long, int, int, int>> {};
INSTANTIATE_TEST_CASE_P(JulianDate, EpochSecondsToJulianDateTest, Values(
  std::tuple<long long, int, int, int>{ -62167392000LL,    0,  1,  1 },
  std::tuple<long long, int, int, int>{ -62167305601LL,    0,  1,  1 },
  std::tuple<long long, int, int, int>{ -62167305600LL,    0,  1,  2 },
  std::tuple<long long, int, int, int>{ -62135856000LL,    0, 12, 31 },
  std::tuple<long long, int, int, int>{ -62135769601LL,    0, 12, 31 },
  std::tuple<long long, int, int, int>{ -62135769600LL,    1,  1,  1 },

  std::tuple<long long, int, int, int>{  -3505680000LL, 1858, 11, 17 },
  std::tuple<long long, int, int, int>{  -3505593601LL, 1858, 11, 17 },
  std::tuple<long long, int, int, int>{  -3505593600LL, 1858, 11, 18 },

  std::tuple<long long, int, int, int>{      1123199LL, 1969, 12, 31 },
  std::tuple<long long, int, int, int>{      1123200LL, 1970,  1,  1 },
  std::tuple<long long, int, int, int>{      1123201LL, 1970,  1,  1 },
  std::tuple<long long, int, int, int>{      1209599LL, 1970,  1,  1 },
  std::tuple<long long, int, int, int>{      1209600LL, 1970,  1,  2 },

  std::tuple<long long, int, int, int>{  -2202940800LL, 1900,  2, 28 },
  std::tuple<long long, int, int, int>{  -2202854401LL, 1900,  2, 28 },
  std::tuple<long long, int, int, int>{  -2202854400LL, 1900,  2, 29 },
  std::tuple<long long, int, int, int>{  -2202768001LL, 1900,  2, 29 },
  std::tuple<long long, int, int, int>{  -2202768000LL, 1900,  3,  1 },

  std::tuple<long long, int, int, int>{    952819200LL, 2000,  2, 28 },
  std::tuple<long long, int, int, int>{    952905599LL, 2000,  2, 28 },
  std::tuple<long long, int, int, int>{    952905600LL, 2000,  2, 29 },
  std::tuple<long long, int, int, int>{    952991999LL, 2000,  2, 29 },
  std::tuple<long long, int, int, int>{    952992000LL, 2000,  3,  1 },

  std::tuple<long long, int, int, int>{   1394668800LL, 2014,  2, 28 },
  std::tuple<long long, int, int, int>{   1394755199LL, 2014,  2, 28 },
  std::tuple<long long, int, int, int>{   1394755200LL, 2014,  3,  1 },

  std::tuple<long long, int, int, int>{   1416096000LL, 2014, 11,  3 },
  std::tuple<long long, int, int, int>{   1416182400LL, 2014, 11,  4 }
));

class ValidJulianDateTest : public TestWithParam<std::tuple<int, int, int>> {};
INSTANTIATE_TEST_CASE_P(JulianDate, ValidJulianDateTest, Values(
  std::tuple<int, int, int>{    0,  1,  1 },
  std::tuple<int, int, int>{ 1858, 11, 30 },
  std::tuple<int, int, int>{ 1900,  2, 29 },
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
  std::tuple<int, int, int>{ 2014, 12, 31 },

  std::tuple<int, int, int>{ 2292, 12, 31 },
  std::tuple<int, int, int>{ 2293,  1,  1 }
));

class InvalidJulianDateTest : public TestWithParam<std::tuple<int, int, int>> {};
INSTANTIATE_TEST_CASE_P(JulianDate, InvalidJulianDateTest, Values(
  std::tuple<int, int, int>{    0,  0,  0 },
  std::tuple<int, int, int>{ 1858, 11, 31 },
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

class JulianDateAddMonthTest : public TestWithParam<std::tuple<int, int, int, int, int, int, int>> {};
INSTANTIATE_TEST_CASE_P(JulianDate, JulianDateAddMonthTest, Values(
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

INSTANTIATE_TEST_CASE_P(JulianDateAddMultipleMonths, JulianDateAddMonthTest, Values(
  std::tuple<int, int, int, int, int, int, int>{ 1900,  1, 31,  2, 1900,  4,  1 },
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

class JulianDateAddNegativeMonthTest : public TestWithParam<std::tuple<int, int, int, int, int, int, int>> {};
INSTANTIATE_TEST_CASE_P(JulianDate, JulianDateAddNegativeMonthTest, Values(
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

class JulianDateAddYearTest : public TestWithParam<std::tuple<int, int, int, int, int, int, int>> {};
INSTANTIATE_TEST_CASE_P(JulianDate, JulianDateAddYearTest, Values(
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
  std::tuple<int, int, int, int, int, int, int>{ 1972,  2, 29, 128, 2100,  2, 29 },
  std::tuple<int, int, int, int, int, int, int>{ 1972,  2, 29, 428, 2400,  2, 29 },

  std::tuple<int, int, int, int, int, int, int>{ 1972,  2, 29,  -1, 1971,  2, 28 },
  std::tuple<int, int, int, int, int, int, int>{ 1973,  2, 28,  -1, 1972,  2, 28 }
));

class JulianDateWeekdayTest : public TestWithParam<std::tuple<int, int, int, int>> {};
INSTANTIATE_TEST_CASE_P(JulianDate, JulianDateWeekdayTest, Values(
  std::tuple<int, int, int, int>{ 1, 1858, 11, 17 },

  std::tuple<int, int, int, int>{ 3, 1970,  1,  1 },

  std::tuple<int, int, int, int>{ 5, 2014, 11,  1 },
  std::tuple<int, int, int, int>{ 6, 2014, 11,  2 },
  std::tuple<int, int, int, int>{ 7, 2014, 11,  3 },
  std::tuple<int, int, int, int>{ 1, 2014, 11,  4 },
  std::tuple<int, int, int, int>{ 2, 2014, 11,  5 }
));

using lab2::Date;
using lab2::JulianDate;

TEST_P(EpochSecondsToJulianDateTest, DefaultConstructorSetsResultToToday) {
  const long long current_epoch_seconds = std::get<0>(GetParam());
  const int expected_year = std::get<1>(GetParam());
  const int expected_month = std::get<2>(GetParam());
  const int expected_day = std::get<3>(GetParam());

  set_k_time(current_epoch_seconds);
  const JulianDate d;

  EXPECT_EQ(expected_year, d.year());
  EXPECT_EQ(expected_month, d.month());
  EXPECT_EQ(expected_day, d.day());
}

TEST_P(ValidJulianDateTest, YmdConstructorFailsForInvalidDates) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  EXPECT_NO_THROW({
    JulianDate d(year, month, day);
  });
}

TEST_P(InvalidJulianDateTest, YmdConstructorFailsForInvalidDates) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  EXPECT_THROW({
    JulianDate d(year, month, day);
  }, std::out_of_range);
}

TEST_P(ValidJulianDateTest, YmdConstructorSetsResultToArgument) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  const JulianDate d(year, month, day);

  EXPECT_EQ(year, d.year());
  EXPECT_EQ(month, d.month());
  EXPECT_EQ(day, d.day());
}

TEST_P(ValidJulianDateTest, CopyConstructorMakesResultEqualToArgument) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  const JulianDate gda{year, month, day};
  const Date& da = gda;
  const JulianDate gdb{da};

  EXPECT_EQ(da, gdb);
  EXPECT_EQ(0, da - gdb);
}

TEST_P(ValidJulianDateTest, CopyConstructorDoesNotModifyOriginal) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  const JulianDate gda{year, month, day};
  const Date& da = gda;

  ASSERT_EQ(year, da.year());
  ASSERT_EQ(month, da.month());
  ASSERT_EQ(day, da.day());

  const JulianDate gdb{da};

  EXPECT_EQ(year, da.year());
  EXPECT_EQ(month, da.month());
  EXPECT_EQ(day, da.day());
}

TEST_P(ValidJulianDateTest, OperatorAssignmentSetsSelfEqualToArgument) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  const JulianDate gda{year, month, day};
  const Date& da = gda;

  set_k_time(0);

  JulianDate gdb{};
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

TEST_P(ValidJulianDateTest, OperatorAssignmentDoesNotModifyOriginal) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  const JulianDate gda{year, month, day};
  const Date& da = gda;

  ASSERT_EQ(year, da.year());
  ASSERT_EQ(month, da.month());
  ASSERT_EQ(day, da.day());

  set_k_time(0);

  JulianDate gdb{};
  Date& db = gdb;

  db = da;

  EXPECT_EQ(year, da.year());
  EXPECT_EQ(month, da.month());
  EXPECT_EQ(day, da.day());
}

TEST_P(JulianDateAddMonthTest, AddMonthAddsOneMonthIfPossibleOtherwiseAdds30Days) {
  const int year_before = std::get<0>(GetParam());
  const int month_before = std::get<1>(GetParam());
  const int day_before = std::get<2>(GetParam());

  const int num_months = std::get<3>(GetParam());

  const int year_after = std::get<4>(GetParam());
  const int month_after = std::get<5>(GetParam());
  const int day_after = std::get<6>(GetParam());

  JulianDate gda{year_before, month_before, day_before};
  JulianDate gdb{year_before, month_before, day_before};

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

TEST_P(JulianDateAddNegativeMonthTest, AddNegativeMonthsSubtractsOneMonthIfPossibleOtherwiseSubtracts30Days) {
  const int year_before = std::get<0>(GetParam());
  const int month_before = std::get<1>(GetParam());
  const int day_before = std::get<2>(GetParam());

  const int num_months = std::get<3>(GetParam());

  const int year_after = std::get<4>(GetParam());
  const int month_after = std::get<5>(GetParam());
  const int day_after = std::get<6>(GetParam());

  JulianDate gda{year_before, month_before, day_before};
  JulianDate gdb{year_before, month_before, day_before};

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

TEST_P(JulianDateAddYearTest, AddYearMovesToSameDayOnAnotherYearAndLeapDayGoesToLastFebruary) {
  const int year_before = std::get<0>(GetParam());
  const int month_before = std::get<1>(GetParam());
  const int day_before = std::get<2>(GetParam());

  const int num_years = std::get<3>(GetParam());

  const int year_after = std::get<4>(GetParam());
  const int month_after = std::get<5>(GetParam());
  const int day_after = std::get<6>(GetParam());

  JulianDate gd{year_before, month_before, day_before};

  ASSERT_EQ(year_before, gd.year());
  ASSERT_EQ(month_before, gd.month());
  ASSERT_EQ(day_before, gd.day());

  gd.add_year(num_years);

  EXPECT_EQ(year_after, gd.year());
  EXPECT_EQ(month_after, gd.month());
  EXPECT_EQ(day_after, gd.day());
}

TEST_P(JulianDateWeekdayTest, ExampleDatesHaveCorrectWeekday) {
  const int weekday = std::get<0>(GetParam());
  const int year = std::get<1>(GetParam());
  const int month = std::get<2>(GetParam());
  const int day = std::get<3>(GetParam());

  JulianDate gd{year, month, day};
  EXPECT_EQ(weekday, gd.week_day());
}

TEST(JulianDate, OperatorIncrementPostfixIncreasesDistanceFromOriginalByOne) {
  set_k_time(0);
  const JulianDate original;
  JulianDate jd{original};
  jd++;
  EXPECT_EQ(1, jd - original);
}

TEST(JulianDate, OperatorIncrementPostfixReturnsCopyToBeforeState) {
  const JulianDate original;
  JulianDate jd{original};
  JulianDate jd2{ jd++ };
  EXPECT_EQ(original.mod_julian_day(), jd2.mod_julian_day());
}

TEST(JulianDate, OperatorDecrementPostfixIncreasesDistanceFromOriginalByOne) {
  set_k_time(0);
  const JulianDate original;
  JulianDate jd{original};
  jd--;
  EXPECT_EQ(-1, jd - original);
}

TEST(JulianDate, OperatorDecrementPostfixReturnsCopyToBeforeState) {
  const JulianDate original;
  JulianDate jd{original};
  JulianDate jd2{ jd-- };

  EXPECT_EQ(original.mod_julian_day(), jd2.mod_julian_day());
}

TEST(JulianDate, OperatorIncrementPrefixReturnsAnLvalue) {
  set_k_time(0);
  JulianDate jd;
  const JulianDate jd2;

  ++jd;
  ASSERT_NE(jd2, jd);

  (++jd) = jd2;

  EXPECT_EQ(jd2, jd);
}

TEST(JulianDate, OperatorDecrementPrefixReturnsAnLvalue) {
  set_k_time(0);
  JulianDate jd;
  const JulianDate jd2;

  --jd;
  ASSERT_NE(jd2, jd);

  (--jd) = jd2;

  EXPECT_EQ(jd2, jd);
}
