#include "western_date.h"

namespace lab2 {
  class GregorianDate : public WesternDate {
  public:
    // Utility functions
    static inline bool is_leap_year(int year) { return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0); }
  };
}
