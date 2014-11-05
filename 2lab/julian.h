#pragma once
#include "western_date.h"

namespace lab2 {
  class JulianDate : public WesternDate {
  protected:
    static const int JULIAN_DAY_ZERO_MJD_OFFSET = -678943; // MJD number of Julian 0000-01-01

    // Utility functions
    virtual inline bool is_leap_year(int year) const override {
        return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    }
    virtual int ymd_to_mjd_offset(int year, int month, int day) const override;
    virtual DateDecomposition getDecomposition() const override;

  public:
    // Date API methods
    JulianDate();
    JulianDate(int year, int month, int day);
    JulianDate(const Date& original);
    JulianDate(const Date* original);
  };

  typedef JulianDate Julian;
}
