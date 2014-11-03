#include "western_date.h"

namespace lab2 {
  class GregorianDate : public WesternDate {
  protected:
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
