#include <gtest/gtest.h>
#include "kattistime.h"
#include "gregorian_date.h"

using ::testing::TestWithParam;
using ::testing::Values;

class GregorianLeapYearTest : public TestWithParam<std::tuple<int, bool>> {};

INSTANTIATE_TEST_CASE_P(GregorianDate, GregorianLeapYearTest, Values(
  std::tuple<int, bool>{0, true},
  std::tuple<int, bool>{100, false},
  std::tuple<int, bool>{1900, false},
  std::tuple<int, bool>{1904, true},
  std::tuple<int, bool>{1996, true},
  std::tuple<int, bool>{2000, true},
  std::tuple<int, bool>{2004, true},
  std::tuple<int, bool>{2100, false},
  std::tuple<int, bool>{2558, false},
  std::tuple<int, bool>{2560, true}
));

class EpochSecondsToGregorianDateTest : public TestWithParam<std::tuple<long long, int, int, int>> {};
INSTANTIATE_TEST_CASE_P(GregorianDate, EpochSecondsToGregorianDateTest, Values(
  std::tuple<long long, int, int, int>{-3506716801LL, 1858, 11, 16},
  std::tuple<long long, int, int, int>{-3506716800LL, 1858, 11, 17},
  std::tuple<long long, int, int, int>{-3506716799LL, 1858, 11, 17},
  std::tuple<long long, int, int, int>{-1, 1969, 12, 31},
  std::tuple<long long, int, int, int>{0, 1970, 1, 1},
  std::tuple<long long, int, int, int>{1, 1970, 1, 1},
  std::tuple<long long, int, int, int>{60*60*24, 1970, 1, 2},
  std::tuple<long long, int, int, int>{1414976494LL, 2014, 11, 3},
  std::tuple<long long, int, int, int>{1415059199LL, 2014, 11, 3},
  std::tuple<long long, int, int, int>{1415059200LL, 2014, 11, 4},
  std::tuple<long long, int, int, int>{1415059201LL, 2014, 11, 4}
));

class ValidGregorianDateTest : public TestWithParam<std::tuple<int, int, int>> {};
INSTANTIATE_TEST_CASE_P(GregorianDate, ValidGregorianDateTest, Values(
  std::tuple<int, int, int>{0, 1, 1},
  std::tuple<int, int, int>{1858, 11, 30},
  std::tuple<int, int, int>{1969, 12, 31},
  std::tuple<int, int, int>{1970, 1, 1},
  std::tuple<int, int, int>{1970, 1, 2},
  std::tuple<int, int, int>{2012, 2, 28},
  std::tuple<int, int, int>{2014, 11, 3},
  std::tuple<int, int, int>{2014, 11, 4},
  std::tuple<int, int, int>{2014, 1, 31},
  std::tuple<int, int, int>{2014, 2, 28},
  std::tuple<int, int, int>{2014, 3, 31},
  std::tuple<int, int, int>{2014, 4, 30},
  std::tuple<int, int, int>{2014, 5, 31},
  std::tuple<int, int, int>{2014, 6, 30},
  std::tuple<int, int, int>{2014, 7, 31},
  std::tuple<int, int, int>{2014, 8, 31},
  std::tuple<int, int, int>{2014, 9, 30},
  std::tuple<int, int, int>{2014, 10, 31},
  std::tuple<int, int, int>{2014, 11, 30},
  std::tuple<int, int, int>{2014, 12, 31}
));

class InvalidGregorianDateTest : public TestWithParam<std::tuple<int, int, int>> {};
INSTANTIATE_TEST_CASE_P(GregorianDate, InvalidGregorianDateTest, Values(
  std::tuple<int, int, int>{0, 0, 0},
  std::tuple<int, int, int>{1858, 11, 31},
  std::tuple<int, int, int>{2014, 1, 32},
  std::tuple<int, int, int>{2014, 2, 29},
  std::tuple<int, int, int>{2014, 3, 32},
  std::tuple<int, int, int>{2014, 4, 31},
  std::tuple<int, int, int>{2014, 5, 32},
  std::tuple<int, int, int>{2014, 6, 31},
  std::tuple<int, int, int>{2014, 7, 32},
  std::tuple<int, int, int>{2014, 8, 32},
  std::tuple<int, int, int>{2014, 9, 31},
  std::tuple<int, int, int>{2014, 10, 32},
  std::tuple<int, int, int>{2014, 11, 31},
  std::tuple<int, int, int>{2014, 12, 32}
));

class GregorianYmdTest : public TestWithParam<std::tuple<int, int, int>> {};
INSTANTIATE_TEST_CASE_P(GregorianDate, GregorianYmdTest, Values(
  std::tuple<int, int, int>{1970, 1, 1},
  std::tuple<int, int, int>{1970, 1, 2},
  std::tuple<int, int, int>{1858, 11, 16},
  std::tuple<int, int, int>{1858, 11, 17},
  std::tuple<int, int, int>{2014, 11, 3}
));

using lab2::Date;
using lab2::GregorianDate;

TEST_P(GregorianLeapYearTest, IsLeapYearIsCorrect) {
  EXPECT_EQ(std::get<1>(GetParam()), GregorianDate::is_leap_year(std::get<0>(GetParam())));
}

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

TEST_P(GregorianYmdTest, YmdConstructorSetsResultToArgument) {
  const int year = std::get<0>(GetParam());
  const int month = std::get<1>(GetParam());
  const int day = std::get<2>(GetParam());

  const GregorianDate d(year, month, day);

  EXPECT_EQ(year, d.year());
  EXPECT_EQ(month, d.month());
  EXPECT_EQ(day, d.day());
}
