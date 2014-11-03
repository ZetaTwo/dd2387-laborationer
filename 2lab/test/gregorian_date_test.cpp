#include <gtest/gtest.h>
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

using lab2::Date;
using lab2::GregorianDate;

TEST_P(GregorianLeapYearTest, IsLeapYearIsCorrect) {
  EXPECT_EQ(std::get<1>(GetParam()), GregorianDate::is_leap_year(std::get<0>(GetParam())));
}
