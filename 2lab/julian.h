#pragma once
#include "western_date.h"

namespace lab2 {
  class JulianDate : public WesternDate {
  protected:
    static const int JULIAN_DAY_ZERO_MJD_OFFSET = -678943; // MJD number of Julian 0000-01-01

    // Utility functions
    virtual inline bool is_leap_year() const override { return is_leap_year_util(year()); }
    virtual inline bool is_leap_year(int year) const override { return is_leap_year_util(year); }
    static inline bool is_leap_year_util(int year) { return year % 4 == 0; }

    virtual int ymd_to_mjd_offset(int year, int month, int day) const override;
    virtual DateDecomposition getDecomposition() const override;

  public:
    // Date API methods
    JulianDate();
    JulianDate(int year, int month, int day);
    JulianDate(const Date& original);
    JulianDate(const Date* original);

    virtual JulianDate&& operator++(int) override;
    virtual JulianDate&& operator--(int) override;
  };

  typedef JulianDate Julian;
}
