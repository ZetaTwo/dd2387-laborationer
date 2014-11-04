#include "western_date.h"

namespace lab2 {
  const std::vector<std::string> WesternDate::day_names = {
    "monday",
    "tuesday",
    "wednesday",
    "thursday",
    "friday",
    "saturday",
    "sunday",
  };
  const std::vector<std::string> WesternDate::month_names = {
    "january",
    "february",
    "march",
    "april",
    "may",
    "june",
    "july",
    "august",
    "september",
    "october",
    "november",
    "december",
  };
  const std::vector<int> WesternDate::month_lengths = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  int WesternDate::year() const {
    const DateDecomposition d = getDecomposition();
    return d.year;
  }
  int WesternDate::month() const {
    const DateDecomposition d = getDecomposition();
    //TODO: month
    return 0;
  }
  int WesternDate::day() const {
    const DateDecomposition d = getDecomposition();
    //TODO: day
    return 0;
  }
  int WesternDate::week_day() const {
    const DateDecomposition d = getDecomposition();
    //TODO: week day
    return 0;
  };
}
