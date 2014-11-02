#include <gtest/gtest.h>
#include "western_date.h"

using lab2::Date;
using lab2::WesternDate;

class WesternDateStub : public WesternDate {
public:
  // Methods required for tests
  using WesternDate::WesternDate; // Inherit constructors

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
