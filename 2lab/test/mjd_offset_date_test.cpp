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

TEST(MjdOffsetDate, CopyConstructorMakesResultEqualToArgument) {
  const MjdodStub dsa(1);
  const MjdodStub dsb(dsa);
  EXPECT_EQ(dsa, dsb);
}

TEST(MjdOffsetDate, CopyConstructorDoesNotModifyMjdOfArgument) {
  const MjdodStub dsa(1);
  const MjdodStub dsb(dsa);
  EXPECT_EQ(1, dsa.mod_julian_day());
}

TEST(MjdOffsetDate, AssignmentOperatorMakesLhsEqualToRhs) {
  const MjdodStub dsa(1);
  MjdodStub dsb(0);
  MjdodStub& dsbr = dsb;

  ASSERT_NE(dsa, dsb);

  dsbr = dsa;

  EXPECT_EQ(dsa, dsb);
}

TEST(MjdOffsetDate, AssignmentOperatorDoesNotModifyMjdOfRhs) {
  const MjdodStub dsa(1);
  MjdodStub dsb(0);

  ASSERT_NE(dsa, dsb);

  dsb = dsa;

  EXPECT_EQ(1, dsa.mod_julian_day());
}

TEST(MjdOffsetDate, AssignmentOperatorIsBoundDynamically) {
  const MjdodStub dsa(1);
  MjdodStub dsb(0);
  Date& dbr = dsb;

  ASSERT_NE(dbr, dsa);

  dbr = dsa;

  EXPECT_EQ(1, dbr.mod_julian_day());
  EXPECT_EQ(1, dsb.mod_julian_day());
}

TEST(MjdOffsetDate, ModJulianDayIsBoundDynamically) {
  const MjdodStub ds(1);
  const Date& dr = ds;

  EXPECT_EQ(1, dr.mod_julian_day());
}

TEST(MjdOffsetDate, OperatorIncrementPrefixIncrementsModJulianDayByOne) {
  MjdodStub ds(0);
  Date& dr = ds;

  ++dr;

  EXPECT_EQ(1, dr.mod_julian_day());
  EXPECT_EQ(1, ds.mod_julian_day());
}

TEST(MjdOffsetDate, OperatorIncrementPrefixReturnsSelfAfterModification) {
  MjdodStub ds(0);
  Date& dr = ds;

  EXPECT_EQ(1, (++dr).mod_julian_day());
}

TEST(MjdOffsetDate, OperatorDecrementPrefixDecrementsModJulianDayByOne) {
  MjdodStub ds(0);
  Date& dr = ds;

  --dr;

  EXPECT_EQ(-1, dr.mod_julian_day());
  EXPECT_EQ(-1, ds.mod_julian_day());
}

TEST(MjdOffsetDate, OperatorDecrementPrefixReturnsSelfAfterModification) {
  MjdodStub ds(0);
  Date& dr = ds;

  EXPECT_EQ(-1, (--dr).mod_julian_day());
}

TEST(MjdOffsetDate, OperatorIncreaseAssignmentIncreasesModJulianDayByArgument) {
  MjdodStub ds(0);
  Date& dr = ds;

  dr += 5;

  EXPECT_EQ(5, dr.mod_julian_day());
  EXPECT_EQ(5, ds.mod_julian_day());
}

TEST(MjdOffsetDate, OperatorIncreaseAssignmentReturnsSelfAfterModification) {
  MjdodStub ds(0);
  Date& dr = ds;

  EXPECT_EQ(5, (dr += 5).mod_julian_day());
}

TEST(MjdOffsetDate, OperatorDecreaseAssignmentDecreasesModJulianDayByArgument) {
  MjdodStub ds(0);
  Date& dr = ds;

  dr -= 5;

  EXPECT_EQ(-5, dr.mod_julian_day());
  EXPECT_EQ(-5, ds.mod_julian_day());
}

TEST(MjdOffsetDate, OperatorDecreaseAssignmentReturnsSelfAfterModification) {
  MjdodStub ds(0);
  Date& dr = ds;

  EXPECT_EQ(-5, (dr -= 5).mod_julian_day());
}
