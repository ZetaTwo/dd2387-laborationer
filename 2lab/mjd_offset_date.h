#pragma once
#include "date.h"

namespace lab2 {

  class MjdOffsetDate : public Date {
  protected:
    int mjd_offset;

  public:
    MjdOffsetDate();
    MjdOffsetDate(int mjd_offset);
    MjdOffsetDate(const Date& original);

    virtual MjdOffsetDate& operator=(const Date& other) override;

    virtual inline int mod_julian_day() const override { return mjd_offset; }

    virtual MjdOffsetDate& operator++() override;
    virtual MjdOffsetDate& operator--() override;
    virtual MjdOffsetDate& operator+=(int) override;
    virtual MjdOffsetDate& operator-=(int) override;
  };

}
