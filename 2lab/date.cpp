#include "date.h"

namespace lab2 {

  int Date::operator-(const Date& other) const {
    return mod_julian_day() - other.mod_julian_day();
  }

  bool Date::operator==(const Date& other) const {
    return mod_julian_day() == other.mod_julian_day();
  }

  bool Date::operator!=(const Date& other) const {
    return mod_julian_day() != other.mod_julian_day();
  }

  bool Date::operator<(const Date& other) const {
    return mod_julian_day() < other.mod_julian_day();
  }

  bool Date::operator<=(const Date& other) const {
    return mod_julian_day() <= other.mod_julian_day();
  }

  bool Date::operator>(const Date& other) const {
    return mod_julian_day() > other.mod_julian_day();
  }

  bool Date::operator>=(const Date& other) const {
    return mod_julian_day() >= other.mod_julian_day();
  }

  std::ostream& operator<<(std::ostream& os, const Date& d) {
    return os
      << (d.year() < 1000 ? "0" : "")
      << (d.year() < 100 ? "0" : "")
      << (d.year() < 10 ? "0" : "")
      << d.year()
      << "-"
      << (d.month() < 10 ? "0" : "") << d.month()
      << "-"
      << (d.day() < 10 ? "0" : "") << d.day()
      ;
  }

}
