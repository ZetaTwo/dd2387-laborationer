#include <gtest/gtest.h>
#include "western_date.h"

using ::testing::TestWithParam;
using ::testing::Values;

class DayNamesTest : public TestWithParam<std::tuple<int, std::string>> {};

INSTANTIATE_TEST_CASE_P(WesternDate, DayNamesTest, Values(
  std::tuple<int, std::string>{0, "monday"},
  std::tuple<int, std::string>{1, "tuesday"},
  std::tuple<int, std::string>{2, "wednesday"},
  std::tuple<int, std::string>{3, "thursday"},
  std::tuple<int, std::string>{4, "friday"},
  std::tuple<int, std::string>{5, "saturday"},
  std::tuple<int, std::string>{6, "sunday"}
));

using lab2::Date;
using lab2::WesternDate;

class WesternDateStub : public WesternDate {
public:
  // Methods required for tests
  using WesternDate::WesternDate; // Inherit constructors

  // Provide outside access to protected static variables
  inline std::string get_week_day_name(const int index) const { return day_names[index]; }
  inline std::string get_month_name(const int index)    const { return month_names[index]; }

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

  const WesternDateStub ds = WesternDateStub();
  EXPECT_EQ(day_name, ds.get_week_day_name(day_index));
}
