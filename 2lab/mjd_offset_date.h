#pragma once
#include "date.h"

namespace lab2 {

class MjdOffsetDate : public Date {
protected:
  int mjd_offset;

public:
  MjdOffsetDate();
  explicit MjdOffsetDate(int mjd_offset);
  MjdOffsetDate(const Date& original);

  virtual MjdOffsetDate& operator=(const Date& other);

  virtual inline int mod_julian_day() const { return mjd_offset; }

  virtual MjdOffsetDate& operator++();
  virtual MjdOffsetDate& operator--();
  virtual MjdOffsetDate& operator+=(int);
  virtual MjdOffsetDate& operator-=(int);
};

}
