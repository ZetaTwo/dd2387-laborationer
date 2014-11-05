#include "mjd_offset_date.h"

namespace lab2 {

  MjdOffsetDate::MjdOffsetDate() : mjd_offset(0) {
  }

  MjdOffsetDate::MjdOffsetDate(int mjd_offset) : mjd_offset(mjd_offset) {
  }

  MjdOffsetDate::MjdOffsetDate(const Date& original) : mjd_offset(original.mod_julian_day()) {
  }

  MjdOffsetDate& MjdOffsetDate::operator=(const Date& other) {
    mjd_offset = other.mod_julian_day();
    return *this;
  }

  MjdOffsetDate& MjdOffsetDate::set(const int mjd_offset) {
    (*this).mjd_offset = mjd_offset;
    return *this;
  }

  MjdOffsetDate& MjdOffsetDate::operator++() {
    ++mjd_offset;
    return *this;
  }

  MjdOffsetDate& MjdOffsetDate::operator--() {
    --mjd_offset;
    return *this;
  }

  MjdOffsetDate& MjdOffsetDate::operator+=(int days) {
    mjd_offset += days;
    return *this;
  }

  MjdOffsetDate& MjdOffsetDate::operator-=(int days) {
    return operator+=(-days);
  }

}
