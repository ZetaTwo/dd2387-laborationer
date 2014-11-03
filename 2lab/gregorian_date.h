#include "western_date.h"

namespace lab2 {
  class GregorianDate : public WesternDate {
  protected:
    static const int UTC_EPOCH_MJD_OFFSET = 40587; // Offset of 1970-01-01 (MJD is 1858-11-17)

    virtual DateDecomposition getDecomposition() const override;
    virtual inline bool is_leap_year() const override { return is_leap_year(year()); };

  public:
    // Date API methods
    GregorianDate() {}
    GregorianDate(int year, int month, int day) {}

    virtual Date& add_year (int years  = 1) override { return *this; }
    virtual Date& add_month(int months = 1) override { return *this; }

    // Utility functions
    static inline bool is_leap_year(int year) { return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0); }
  };
}
