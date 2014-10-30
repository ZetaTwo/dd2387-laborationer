#include "date.h"

namespace lab2 {

Date::Date() : mjd_offset(0) {
}

Date::Date(int mjd_offset) : mjd_offset(mjd_offset) {
}

Date::Date(const Date& original) : mjd_offset(original.mod_julian_day()) {
}

Date& Date::operator=(const Date& other) {
  mjd_offset = other.mod_julian_day();
  return *this;
}

int Date::mod_julian_day() const {
  return mjd_offset;
}

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

Date& Date::operator++() {
  ++mjd_offset;
  return *this;
}

Date& Date::operator--() {
  --mjd_offset;
  return *this;
}

Date& Date::operator+=(int days) {
  mjd_offset += days;
  return *this;
}

Date& Date::operator-=(int days) {
  return operator+=(-days);
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
  return os << d.year() << "-" << d.month() << "-" << d.day();
}

}
