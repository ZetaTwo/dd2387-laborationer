#include "date.h"

#include <iomanip>
using namespace std;

namespace lab2 {
  Date::~Date() {}

  std::ostream& operator<<(std::ostream& os, const Date& d) {
    return os << setw(4) << setfill('0') << d.year() << "-" << setw(2) << d.month() << "-" << setw(2) << d.day();
  }
}