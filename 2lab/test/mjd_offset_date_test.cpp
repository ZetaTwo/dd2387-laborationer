#include <gtest/gtest.h>
#include <sstream>
#include "mjd_offset_date.h"

using lab2::Date;
using lab2::MjdOffsetDate;

class MjdodStub : public MjdOffsetDate {
public:
  // Methods required for tests
  using MjdOffsetDate::MjdOffsetDate; // Inherit constructors

  // Methods under test:
  //  MjdOffsetDate();
  //  MjdOffsetDate(int mjd_offset);
  //  MjdOffsetDate(const Date& original);
  //  virtual MjdOffsetDate& operator=(const Date& other) override;
  //  virtual inline int mod_julian_day() const override { return mjd_offset; }
  //  virtual MjdOffsetDate& operator++() override;
  //  virtual MjdOffsetDate& operator--() override;
  //  virtual MjdOffsetDate& operator+=(int) override;
  //  virtual MjdOffsetDate& operator-=(int) override;

  // Dummy implementations for virtual methods
  virtual int year()            const override { return 0; }
  virtual int month()           const override { return 0; }
  virtual int day()             const override { return 0; }
  virtual int week_day()        const override { return 0; }
  virtual int days_per_week()   const override { return 0; }
  virtual int days_this_month() const override { return 0; }
  virtual int months_per_year() const override { return 0; }
  virtual std::string week_day_name() const override { return ""; }
  virtual std::string month_name()    const override { return ""; }
  virtual Date& add_year (int) override { return *this; }
  virtual Date& add_month(int) override { return *this; }
};

TEST(MjdOffsetDate, DefaultConstructorSetsModJulianDayToZero) {
  const MjdodStub ds = MjdodStub();
  EXPECT_EQ(0, ds.mod_julian_day());
}

TEST(MjdOffsetDate, IntConstructorSetsModJulianDayToArgument) {
  const MjdodStub ds(1);
  EXPECT_EQ(1, ds.mod_julian_day());
}
