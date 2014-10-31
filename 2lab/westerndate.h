#pragma once

#include <vector>
#include <string>

#include "mjd_offset_date.h"

namespace lab2 {
  class WesternDate : public MjdOffsetDate {
  public:
    WesternDate();
    ~WesternDate();

    virtual int days_per_week() const inline override { return 7; }
    virtual int months_per_year() const inline override { return 12; }

  protected:
    static const std::vector<std::string> day_names;
    static const std::vector<std::string> month_names;
  };
}

