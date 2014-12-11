#pragma once
#include "western_date.h"

namespace lab2 {
  class GregorianDate : public WesternDate {
  protected:
    static const int GREGORIAN_DAY_ZERO_MJD_OFFSET = -678941; // MJD number of Gregorian 0000-01-01

    // Utility functions
    static inline bool is_leap_year_util(const int year) {
      return ((year % 400) == 0) || (((year % 4) == 0) && ((year % 100) != 0));
    }
    virtual inline bool is_leap_year(const int year) const override {
      return is_leap_year_util(year);
    }
    virtual inline bool is_leap_year() const override {
      return is_leap_year_util(year());
    }
    virtual int ymd_to_mjd_offset(int year, int month, int day) const override;
    virtual DateDecomposition getDecomposition() const override;

  public:
    // Date API methods
    GregorianDate();
    GregorianDate(int year, int month, int day);
    GregorianDate(const Date& original);

    virtual GregorianDate& operator++() override;
    virtual GregorianDate& operator--() override;
    GregorianDate operator++(int);
    GregorianDate operator--(int);
  };

  typedef GregorianDate Gregorian;
}
