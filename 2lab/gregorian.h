#pragma once
#include "western_date.h"

namespace lab2 {
  class GregorianDate : public WesternDate {
  protected:
    static const int GREGORIAN_DAY_ZERO_MJD_OFFSET = -678941; // MJD number of Gregorian 0000-01-01

    // Utility functions
    virtual inline bool is_leap_year(int year) const override {
        return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    }
    virtual int ymd_to_mjd_offset(int year, int month, int day) const override;
    virtual DateDecomposition getDecomposition() const override;

  public:
    // Date API methods
    GregorianDate();
    GregorianDate(int year, int month, int day);
    GregorianDate(const Date& original);
  };

  typedef GregorianDate Gregorian;
}
