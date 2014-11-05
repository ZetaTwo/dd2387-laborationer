#include "western_date.h"

namespace lab2 {
  class GregorianDate : public WesternDate {
  protected:
    static const int UTC_EPOCH_MJD_OFFSET = 40587; // Offset of 1970-01-01 (MJD is 1858-11-17)
    static const int GREGORIAN_DAY_ZERO_MJD_OFFSET = -678941; // MJD number of Gregorian 0000-01-01

    virtual DateDecomposition getDecomposition() const override;
    virtual inline bool is_leap_year() const override { return is_leap_year(year()); };

    GregorianDate& add_one_month();
    GregorianDate& subtract_one_month();

  public:
    // Date API methods
    GregorianDate();
    GregorianDate(int year, int month, int day);
    GregorianDate(const Date& original);

    virtual GregorianDate& add_year (int years  = 1) override;
    virtual GregorianDate& add_month(int months = 1) override;

    // Utility functions
    static inline bool is_leap_year(int year) { return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0); }
    static inline bool is_valid_date(int year, int month, int day) {
      return month <= 12 && month >= 1 && day >= 1 && day <= (month_lengths[month-1] + (month == 2 && is_leap_year(year) ? 1 : 0));
    }
  };
}
