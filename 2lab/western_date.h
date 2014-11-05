#pragma once

#include <vector>
#include <string>

#include "mjd_offset_date.h"

namespace lab2 {
  class WesternDate : public MjdOffsetDate {
  public:
    using MjdOffsetDate::MjdOffsetDate; // Inherit constructors

    virtual inline int days_per_week() const override { return 7; }
    virtual inline int months_per_year() const override { return 12; }

    virtual int year()            const override;
    virtual int month()           const override;
    virtual int day()             const override;

    virtual inline int week_day() const override {
      return ((WEEKDAY_OF_MOD_JULIAN_DAY + mod_julian_day()) % days_per_week()) + 1;
    }

    virtual inline int days_this_month() const override {
      const int m = month();
      return  month_lengths[m - 1] + ((m == 2) ? 1 : 0);
    }

    virtual inline std::string week_day_name() const override { return day_names[week_day() - 1]; }
    virtual inline std::string month_name()    const override { return month_names[month() - 1]; }

  protected:
    static const int WEEKDAY_OF_MOD_JULIAN_DAY = 2; // monday = 0, sunday = 6

    static const std::vector<std::string> day_names;
    static const std::vector<std::string> month_names;
    static const std::vector<int> month_lengths;

    inline bool is_leap_year() const { return is_leap_year(year()); }
    inline bool is_valid_date(int year, int month, int day) const {
      return month <= 12 && month >= 1 && day >= 1 && day <= (month_lengths[month-1] + (month == 2 && is_leap_year(year) ? 1 : 0));
    }

    virtual bool is_leap_year(int year) const = 0;
    virtual int ymd_to_mjd_offset(int year, int month, int day) const = 0;

    struct DateDecomposition {
      int year;
      int day;
    };
    virtual DateDecomposition getDecomposition() const = 0;
  };
}

