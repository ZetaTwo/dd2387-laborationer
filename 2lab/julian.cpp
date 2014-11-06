#include <cmath>
#include <stdexcept>
#include <sstream>
#include <algorithm>

#include "kattistime.h"
#include "julian.h"

namespace lab2 {

  JulianDate::JulianDate() : WesternDate(utc_seconds_to_mjd_offset(k_time(nullptr))) {}

  JulianDate::JulianDate(const int year, const int month, const int day) : WesternDate(ymd_to_mjd_offset(year, month, day)) {}

  JulianDate::JulianDate(const Date& original) : WesternDate(original.mod_julian_day()) {}

  JulianDate::JulianDate(const Date* const original) : JulianDate(*original) {}

  int JulianDate::ymd_to_mjd_offset(const int year, const int month, const int day) const {
    if (!is_valid_date(is_leap_year_util(year), month, day)) {
      std::stringstream ss;
      ss << "Invalid Julian date: " << year << "-" << month << "-" << day;
      throw std::out_of_range(ss.str());
    }

    // Source: https://en.wikipedia.org/wiki/Julian_day#Converting_Julian_or_Julian_calendar_date_to_Julian_Day_Number
    const int a = (14 - month) / 12;
    const int y = year + 4800 - a;
    const int m = month + 12 * a - 3;

    return day
      + ((153 * m + 2) / 5)
      + 365L * y + (y / 4)
      - 32083L - 2400001LL;
  }

  JulianDate::DateDecomposition JulianDate::getDecomposition() const {
    const int D4 = 365 * 4 + 1;
    const int D1 = 365;

    const int d = mod_julian_day() - JULIAN_DAY_ZERO_MJD_OFFSET;

    const int c4 = d / D4;
    const int d4 = d % D4;

    const int cp1 = std::min(d4 / (D1 + 1), 1);
    const int dp1 = d4 - cp1 * (D1 + 1);
    const int cb1 = cp1 * dp1 / D1;
    const int db1 = dp1 - cb1 * D1;

    return DateDecomposition{4 * c4 + cp1 + cb1, db1};
  }

}
