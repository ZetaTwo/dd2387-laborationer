#include <gtest/gtest.h>
#include "date.h"

using lab2::Date;

class DateStub : public Date {
private:
  int mjd_offset;

public:
  // Methods required for tests
  explicit DateStub(int mjd_offset) : mjd_offset(mjd_offset) {}
  int mod_julian_day() const override { return mjd_offset; }

  int year()           const override { return 1; }
  int month()          const override { return 2; }
  int day()            const override { return 3; }

  // Methods under test:
  //  int  Date::operator- (const Date& other) const;
  //  bool Date::operator==(const Date& other) const;
  //  bool Date::operator!=(const Date& other) const;
  //  bool Date::operator< (const Date& other) const;
  //  bool Date::operator<=(const Date& other) const;
  //  bool Date::operator> (const Date& other) const;
  //  bool Date::operator>=(const Date& other) const;
  //  std::ostream& operator<<(std::ostream&, const Date&);

  // Dummy implementations for virtual methods
  virtual DateStub& operator=(const Date& other) override { return *this; }
  virtual int week_day()        const override { return 0; }
  virtual int days_per_week()   const override { return 0; }
  virtual int days_this_month() const override { return 0; }
  virtual int months_per_year() const override { return 0; }
  virtual std::string week_day_name() const override { return ""; }
  virtual std::string month_name()    const override { return ""; }
  virtual Date& operator++() override { return *this; }
  virtual Date& operator--() override { return *this; }
  virtual Date& operator+=(int days) override { return *this; }
  virtual Date& operator-=(int days) override { return *this; }
  virtual Date& add_year (int years  = 1) override { return *this; }
  virtual Date& add_month(int months = 1) override { return *this; }
};


TEST(Date, OperatorMinusReturnsTheRightValue) {
  const DateStub ds0(0);
  const DateStub ds1(1);

  EXPECT_EQ(1, ds1 - ds0);
}

TEST(Date, OperatorMinusIsAntisymmetric) {
  const DateStub ds0(0);
  const DateStub ds1(1);

  EXPECT_EQ(ds1 - ds0, -(ds0 - ds1));
}

TEST(Date, OperatorMinusReturnsZeroForSelf) {
  const DateStub ds(0);
  const DateStub& dsr = ds;

  EXPECT_EQ(0, ds - ds);
  EXPECT_EQ(0, ds - dsr);
  EXPECT_EQ(0, dsr - dsr);
}

TEST(Date, OperatorEqualsReturnsTrueForEqualDates) {
  const DateStub dsa(0);
  const DateStub dsb(0);
  const DateStub& dsar = dsa;
  const DateStub& dsbr = dsb;

  EXPECT_TRUE(dsa  == dsb);
  EXPECT_TRUE(dsa  == dsbr);
  EXPECT_TRUE(dsar == dsb);
  EXPECT_TRUE(dsar == dsbr);
}

TEST(Date, OperatorEqualsReturnsFalseForUnequalDates) {
  const DateStub dsa(0);
  const DateStub dsb(1);
  const DateStub& dsar = dsa;
  const DateStub& dsbr = dsb;

  EXPECT_FALSE(dsa  == dsb);
  EXPECT_FALSE(dsa  == dsbr);
  EXPECT_FALSE(dsar == dsb);
  EXPECT_FALSE(dsar == dsbr);
}

TEST(Date, OperatorEqualsIsSymmetricWhenTrue) {
  const DateStub dsa(0);
  const DateStub dsb(1);

  EXPECT_EQ(dsa == dsb, dsb == dsa);
}

TEST(Date, OperatorEqualsIsSymmetricWhenFalse) {
  const DateStub dsa(0);
  const DateStub dsb(0);

  EXPECT_EQ(dsa == dsb, dsb == dsa);
}

TEST(Date, OperatorEqualsIsTrueForSelf) {
  const DateStub ds(0);
  const DateStub& dsr = ds;
  EXPECT_TRUE(ds == ds);
  EXPECT_TRUE(ds == dsr);
}

TEST(Date, OperatorNotEqualsReturnsFalseForEqualDates) {
  const DateStub dsa(0);
  const DateStub dsb(0);
  const DateStub& dsar = dsa;
  const DateStub& dsbr = dsb;

  EXPECT_FALSE(dsa  != dsb);
  EXPECT_FALSE(dsa  != dsbr);
  EXPECT_FALSE(dsar != dsb);
  EXPECT_FALSE(dsar != dsbr);
}

TEST(Date, OperatorNotEqualsReturnsTrueForUnequalDates) {
  const DateStub dsa(0);
  const DateStub dsb(1);
  const DateStub& dsar = dsa;
  const DateStub& dsbr = dsb;

  EXPECT_TRUE(dsa  != dsb);
  EXPECT_TRUE(dsa  != dsbr);
  EXPECT_TRUE(dsar != dsb);
  EXPECT_TRUE(dsar != dsbr);
}

TEST(Date, OperatorNotEqualsIsSymmetricWhenFalse) {
  const DateStub dsa(0);
  const DateStub dsb(1);

  EXPECT_EQ(dsa != dsb, dsb != dsa);
}

TEST(Date, OperatorNotEqualsIsSymmetricWhenTrue) {
  const DateStub dsa(0);
  const DateStub dsb(0);

  EXPECT_EQ(dsa != dsb, dsb != dsa);
}

TEST(Date, OperatorNotEqualsIsFalseForSelf) {
  const DateStub ds(0);
  const DateStub& dsr = ds;
  EXPECT_FALSE(ds != ds);
  EXPECT_FALSE(ds != dsr);
}

TEST(Date, OperatorLessThanReturnsFalseForEqualDates) {
  const DateStub dsa(0);
  const DateStub dsb(0);
  const DateStub& dsar = dsa;
  const DateStub& dsbr = dsb;

  EXPECT_FALSE(dsa  < dsb);
  EXPECT_FALSE(dsa  < dsbr);
  EXPECT_FALSE(dsar < dsb);
  EXPECT_FALSE(dsar < dsbr);
}

TEST(Date, OperatorLessThanReturnsTrueIfLess) {
  const DateStub dsa(0);
  const DateStub dsb(1);
  const DateStub& dsar = dsa;
  const DateStub& dsbr = dsb;

  EXPECT_TRUE(dsa  < dsb);
  EXPECT_TRUE(dsa  < dsbr);
  EXPECT_TRUE(dsar < dsb);
  EXPECT_TRUE(dsar < dsbr);
}

TEST(Date, OperatorLessThanReturnsFalseIfGreater) {
  const DateStub dsa(1);
  const DateStub dsb(0);
  const DateStub& dsar = dsa;
  const DateStub& dsbr = dsb;

  EXPECT_FALSE(dsa  < dsb);
  EXPECT_FALSE(dsa  < dsbr);
  EXPECT_FALSE(dsar < dsb);
  EXPECT_FALSE(dsar < dsbr);
}

TEST(Date, OperatorLessThanIsAntiSymmetric) {
  const DateStub dsa(0);
  const DateStub dsb(1);

  EXPECT_EQ(dsa < dsb, !(dsb < dsa));
}

TEST(Date, OperatorLessThanIsFalseForSelf) {
  const DateStub ds(0);
  const DateStub& dsr = ds;
  EXPECT_FALSE(ds < ds);
  EXPECT_FALSE(ds < dsr);
}
