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

    virtual int year()            const override;
    virtual int month()           const override;
    virtual int day()             const override;
    virtual int week_day()        const override;
    virtual inline int days_this_month() const override {
      const int m = month();
      return  month_lengths[m - 1] + ((m == 2) ? 1 : 0);
    }

    virtual inline std::string week_day_name() const override { return day_names[week_day() - 1]; }
    virtual inline std::string month_name()    const override { return month_names[month() - 1]; }

  protected:
    static const std::vector<std::string> day_names;
    static const std::vector<std::string> month_names;
    static const std::vector<int> month_lengths;

    virtual bool is_leap_year()   const = 0;
    struct DateDecomposition {
      int year;
      int day;
    };
    virtual DateDecomposition getDecomposition() const = 0;
  };
}

