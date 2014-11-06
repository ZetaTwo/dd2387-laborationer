#pragma once

#include <vector>
#include <string>

#include "mjd_offset_date.h"

namespace lab2 {
  class WesternDate : public MjdOffsetDate {
  public:
    static const int UTC_EPOCH_MJD_OFFSET = 40587; // MJD muber of Greg 1970-01-01 (MJD is Greg 1858-11-17)

    WesternDate() {};
    WesternDate(int mjd_offset) : MjdOffsetDate(mjd_offset) {};
    WesternDate(const Date& original) : MjdOffsetDate(original) {};

    virtual inline int days_per_week() const override { return 7; }
    virtual inline int months_per_year() const override { return 12; }

    virtual int year()            const override;
    virtual int month()           const override;
    virtual int day()             const override;

    virtual inline int week_day() const override {
      return ((((WEEKDAY_OF_MOD_JULIAN_DAY + mod_julian_day()) % days_per_week()) + days_per_week()) % days_per_week()) + 1;
    }

    virtual inline int days_this_month() const override {
      const int m = month();
      return  month_lengths[m - 1] + ((m == 2 && is_leap_year()) ? 1 : 0);
    }

    virtual inline std::string week_day_name() const override { return day_names[week_day() - 1]; }
    virtual inline std::string month_name()    const override { return month_names[month() - 1]; }

    virtual WesternDate& add_year (int years  = 1) override;
    virtual WesternDate& add_month(int months = 1) override;

  protected:
    static const int WEEKDAY_OF_MOD_JULIAN_DAY = 2; // monday = 0, sunday = 6

    static const std::vector<std::string> day_names;
    static const std::vector<std::string> month_names;
    static const std::vector<int> month_lengths;

    virtual inline bool is_leap_year() const = 0;
    virtual inline bool is_leap_year(const int year) const = 0;
    static inline bool is_valid_date(const bool leapyear, const int month, const int day) {
      return month <= 12 && month >= 1 && day >= 1 && day <= (month_lengths[month - 1] + (month == 2 && leapyear ? 1 : 0));
    }

    static int utc_seconds_to_mjd_offset(time_t utc_seconds);

    virtual int ymd_to_mjd_offset(int year, int month, int day) const = 0;

    WesternDate& add_one_month();
    WesternDate& subtract_one_month();

    struct DateDecomposition {
      int year;
      int day;
    };
    virtual DateDecomposition getDecomposition() const = 0;
  };
}

