#include "western_date.h"

namespace lab2 {
  const std::vector<std::string> WesternDate::day_names = {
    "monday",
    "tuesday",
    "wednesday",
    "thursday",
    "friday",
    "saturday",
    "sunday",
  };
  const std::vector<std::string> WesternDate::month_names = {
    "january",
    "february",
    "march",
    "april",
    "may",
    "june",
    "july",
    "august",
    "september",
    "october",
    "november",
    "december",
  };
  const std::vector<int> WesternDate::month_lengths = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  int WesternDate::year() const {
    const DateDecomposition d = getDecomposition();
    return d.year;
  }

  int WesternDate::month() const {
    const DateDecomposition d = getDecomposition();
    int day = d.day;
    int month = 0;
    while(day >= month_lengths[month] + (month == 1 && is_leap_year() ? 1 : 0)) {
      day -= month_lengths[month] + (month == 1 && is_leap_year() ? 1 : 0);
      ++month;
    }
    return month + 1;
  }

  int WesternDate::day() const {
    const DateDecomposition d = getDecomposition();
    int day = d.day;
    int month = 0;
    while(day >= month_lengths[month] + (month == 1 && is_leap_year() ? 1 : 0)) {
      day -= month_lengths[month] + (month == 1 && is_leap_year() ? 1 : 0);
      ++month;
    }
    return day + 1;
  }

  WesternDate& WesternDate::add_month(int months) {
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

  WesternDate& WesternDate::add_one_month() {
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

  WesternDate& WesternDate::subtract_one_month() {
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

  WesternDate& WesternDate::add_year(int years) {
    const int year_after = year() + years;

    if(is_valid_date(year_after, month(), day())) {
      this->set(ymd_to_mjd_offset(year_after, month(), day()));
    } else {
      this->set(ymd_to_mjd_offset(year_after, month(), month_lengths[1]));
    }

    return *this;
  }

}
