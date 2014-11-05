#pragma once
#include <string>
#include <ostream>
#include "date.h"

namespace lab2 {

  template<class D>
  class Calendar {
    private:
      static const int UNSPECIFIED_EVENT_DATE_PART = -1;

    public:
      Calendar();
      Calendar(const Calendar& original);

      Calendar& operator=(const Calendar& other);

      bool set_date(int year, int month, int day);

      bool add_event(std::string event,
        int day   = UNSPECIFIED_EVENT_DATE_PART,
        int month = UNSPECIFIED_EVENT_DATE_PART,
        int year  = UNSPECIFIED_EVENT_DATE_PART);
      bool remove_event(std::string event,
        int day   = UNSPECIFIED_EVENT_DATE_PART,
        int month = UNSPECIFIED_EVENT_DATE_PART,
        int year  = UNSPECIFIED_EVENT_DATE_PART);

      std::ostream& printTo(std::ostream& os) const;
  };

  template<class D>
  std::ostream& operator<<(std::ostream& os, const Calendar<D>& cal);
}
