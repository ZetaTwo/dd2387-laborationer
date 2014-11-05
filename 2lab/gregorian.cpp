#include <cmath>
#include <stdexcept>
#include <sstream>
#include "kattistime.h"
#include "gregorian.h"

namespace lab2 {

  GregorianDate::GregorianDate() {
    const time_t now = k_time(nullptr);
    mjd_offset = now / (60*60*24) + UTC_EPOCH_MJD_OFFSET;

    if(now % (60*60*24) < 0) {
      --mjd_offset;
    }
  }

  GregorianDate::GregorianDate(const int year, const int month, const int day) : WesternDate(ymd_to_mjd_offset(year, month, day)) {}

  int GregorianDate::ymd_to_mjd_offset(const int year, const int month, const int day) const {
    if(!is_valid_date(year, month, day)) {
      std::stringstream ss;
      ss << "Invalid Gregorian date: " << year << "-" << month << "-" << day;
      throw std::out_of_range(ss.str());
    }

    // Source: https://en.wikipedia.org/wiki/Julian_day#Converting_Julian_or_Gregorian_calendar_date_to_Julian_Day_Number
    const int a = (14 - month) / 12;
    const int y = year + 4800 - a;
    const int m = month + 12 * a - 3;

    return day
      + ((153 * m + 2) / 5)
      + 365L * y + (y / 4)
      - (y / 100)
      + (y / 400)
      - 32045L - 2400001LL;
  }

  GregorianDate::GregorianDate(const Date& original) : WesternDate(original.mod_julian_day()) {}

  GregorianDate::DateDecomposition GregorianDate::getDecomposition() const {
    const int D400 = 365 * 400 + 100 - 3;
    const int D100 = 365 * 100 +  25 - 1;
    const int D4   = 365 *   4 +   1;
    const int D1   = 365;

    const int d = mod_julian_day() - GREGORIAN_DAY_ZERO_MJD_OFFSET;

    const int c400 = d / D400;
    const int d400 = d % D400;

    const int cp100 = std::min(d400 / (D100 + 1), 1);
    const int dp100 = d400 - cp100 * (D100 + 1);
    const int cb100 = dp100 / D100;
    const int db100 = dp100 % D100;

    const int cp4 = cp100 * std::min(db100 / (D4 - 1), 1);
    const int dp4 = db100 - cp4 * (D4 - 1);
    const int cb4 = dp4 / D4;
    const int db4 = dp4 % D4;

    const int cp1 = (1 - cp100 * (1 - cp4)) * std::min(db4 / (D1 + 1), 1);
    const int dp1 =  db4 - cp1 * (D1 + 1);
    const int cb1 = dp1 / D1;
    const int db1 = dp1 % D1;

    return DateDecomposition{400 * c400 + 100 * (cp100 + cb100) + 4 * (cp4 + cb4) + cp1 + cb1, db1};
  }

  GregorianDate& GregorianDate::add_month(int months) {
    if(months > 0) {
      for(int i = 0; i < months; ++i) {
        add_one_month();
      }
    } else if(months < 0) {
      for(int i = 0; i > months; --i) {
        subtract_one_month();
      }
    }
    return *this;
  }

  GregorianDate& GregorianDate::add_one_month() {
    const int month_after = std::max((month() + 1) % (months_per_year() + 1), 1);
    const int year_after = year() + (month_after == 1 ? 1 : 0);
    const int current_day = day();

    if(is_valid_date(year_after, month_after, current_day)) {
      this->set(ymd_to_mjd_offset(year_after, month_after, current_day));
    } else {
      *this += 30;
    }

    return *this;
  }

  GregorianDate& GregorianDate::subtract_one_month() {
    const int current_month = month();
    const int month_after = current_month == 1 ? months_per_year() : current_month - 1;
    const int year_after = year() - (month_after == 12 ? 1 : 0);
    const int current_day = day();

    if(is_valid_date(year_after, month_after, current_day)) {
      this->set(ymd_to_mjd_offset(year_after, month_after, current_day));
    } else {
      *this -= 30;
    }

    return *this;
  }

  GregorianDate& GregorianDate::add_year(int years) {
    const int year_after = year() + years;

    if(is_valid_date(year_after, month(), day())) {
      this->set(ymd_to_mjd_offset(year_after, month(), day()));
    } else {
      this->set(ymd_to_mjd_offset(year_after, month(), month_lengths[1]));
    }

    return *this;
  }

}
