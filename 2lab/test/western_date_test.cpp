#include <gtest/gtest.h>
#include "western_date.h"

using ::testing::TestWithParam;
using ::testing::Values;

class DayNamesTest : public TestWithParam<std::tuple<int, std::string>> {};
class MonthNamesTest : public TestWithParam<std::tuple<int, std::string>> {};

INSTANTIATE_TEST_CASE_P(WesternDate, DayNamesTest, Values(
  std::tuple<int, std::string>{0, "monday"},
  std::tuple<int, std::string>{1, "tuesday"},
  std::tuple<int, std::string>{2, "wednesday"},
  std::tuple<int, std::string>{3, "thursday"},
  std::tuple<int, std::string>{4, "friday"},
  std::tuple<int, std::string>{5, "saturday"},
  std::tuple<int, std::string>{6, "sunday"}
));

INSTANTIATE_TEST_CASE_P(WesternDate, MonthNamesTest, Values(
  std::tuple<int, std::string>{0, "january"},
  std::tuple<int, std::string>{1, "february"},
  std::tuple<int, std::string>{2, "march"},
  std::tuple<int, std::string>{3, "april"},
  std::tuple<int, std::string>{4, "may"},
  std::tuple<int, std::string>{5, "june"},
  std::tuple<int, std::string>{6, "july"},
  std::tuple<int, std::string>{7, "august"},
  std::tuple<int, std::string>{8, "september"},
  std::tuple<int, std::string>{9, "october"},
  std::tuple<int, std::string>{10, "november"},
  std::tuple<int, std::string>{11, "december"}
));

using lab2::Date;
using lab2::WesternDate;

class WesternDateStub : public WesternDate {
public:
  // Methods required for tests
  using WesternDate::WesternDate; // Inherit constructors

  // Provide outside access to protected static variables
  static inline std::string get_week_day_name(const int index) { return day_names[index]; }
  static inline std::string get_month_name(const int index)    { return month_names[index]; }

  // Methods under test:
  //  virtual inline int days_per_week() const override { return 7; }
  //  virtual inline int months_per_year() const override { return 12; }

  // Dummy implementations for virtual methods
  virtual int year()            const override { return 0; }
  virtual int month()           const override { return 0; }
  virtual int day()             const override { return 0; }
  virtual int week_day()        const override { return 0; }
  virtual int days_this_month() const override { return 0; }
  virtual std::string week_day_name() const override { return ""; }
  virtual std::string month_name()    const override { return ""; }
  virtual Date& add_year (int) override { return *this; }
  virtual Date& add_month(int) override { return *this; }

  virtual bool is_leap_year(int) const override { return false; }
  virtual DateDecomposition getDecomposition() const { return DateDecomposition{0, 0}; }
};

TEST(WesternDate, DaysPerWeekIsSeven) {
  const WesternDateStub ds = WesternDateStub();
  const Date& dr = ds;

  EXPECT_EQ(7, ds.days_per_week());
  EXPECT_EQ(7, dr.days_per_week());
}

TEST(WesternDate, MonthsPerYearIsTwelve) {
  const WesternDateStub ds = WesternDateStub();
  const Date& dr = ds;

  EXPECT_EQ(12, ds.months_per_year());
  EXPECT_EQ(12, dr.months_per_year());
}

TEST_P(DayNamesTest, DayNamesCorrespondToTheRightIndices) {
  const int day_index = std::get<0>(GetParam());
  const std::string day_name = std::get<1>(GetParam());

  EXPECT_EQ(day_name, WesternDateStub::get_week_day_name(day_index));
}

TEST_P(MonthNamesTest, MonthNamesCorrespondToTheRightIndices) {
  const int month_index = std::get<0>(GetParam());
  const std::string month_name = std::get<1>(GetParam());

  EXPECT_EQ(month_name, WesternDateStub::get_month_name(month_index));
}
