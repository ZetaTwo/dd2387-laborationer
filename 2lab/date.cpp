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
  return os << d.year() << "-" << d.month() << "-" << d.day();
}

}
