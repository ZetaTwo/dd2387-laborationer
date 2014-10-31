#pragma once

#include <vector>
#include <string>

#include "mjd_offset_date.h"

namespace lab2 {
  class WesternDate : public MjdOffsetDate {
  public:
    using MjdOffsetDate::MjdOffsetDate; // Inherit constructors

    virtual inline int days_per_week() const override { return 7; }
    virtual inline int months_per_year() const override { return 12; }

  protected:
    static const std::vector<std::string> day_names;
    static const std::vector<std::string> month_names;
  };
}

