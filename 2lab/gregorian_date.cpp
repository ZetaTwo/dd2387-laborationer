#include <cmath>
#include "kattistime.h"
#include "gregorian_date.h"

namespace lab2 {

  GregorianDate::GregorianDate() : WesternDate(std::floor(static_cast<double>(k_time(nullptr)) / (60*60*24)) + UTC_EPOCH_MJD_OFFSET) {}

  GregorianDate::GregorianDate(const int year, const int month, const int day) {
    const int a = std::floor((14 - month) / 12);
    const int y = year + 4800 - a;
    const int m = month + 12 * a - 3;

    mjd_offset = day
      + ((153 * m) / 5)
      + 365L * y + (y / 4)
      - (y / 100)
      + (y / 400)
      - 32045L - 2400001LL;
  }

}
