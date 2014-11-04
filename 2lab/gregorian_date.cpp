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

  GregorianDate::DateDecomposition GregorianDate::getDecomposition() const {
    const int D400 = 365 * 400 + 100 - 3;
    const int D100 = 365 * 100 +  25 - 1;
    const int D4   = 365 *   4 +   1;
    const int D1   = 365;

    const int d = mod_julian_day() - GREGORIAN_DAY_ZERO_MJD_OFFSET;

    const int c400 = d / D400;
    const int d400 = d % D400;

    const int cp100 = std::min(d400 / (D100 + 1), 1);
    const int dp100 = d400 - cp100 * (D100 + 1);
    const int cb100 = dp100 / D100;
    const int db100 = dp100 % D100;

    const int cp4 = cp100 * std::min(db100 / (D4 - 1), 1);
    const int dp4 = db100 - cp4 * (D4 - 1);
    const int cb4 = dp4 / D4;
    const int db4 = dp4 % D4;

    const int cp1 = (1 - cp100 * (1 - cp4)) * std::min(db4 / (D1 + 1), 1);
    const int dp1 =  db4 - cp1 * (D1 + 1);
    const int cb1 = dp1 / D1;
    const int db1 = dp1 % D1;

    return DateDecomposition{400 * c400 + 100 * (cp100 + cb100) + 4 * (cp4 + cb4) + cp1 + cb1, db1};
  }

}
