#pragma once
#include <string>
#include <ostream>
#include <map>
#include <set>
#include <stdexcept>
#include "date.h"

namespace lab2 {

  template<class D>
  class Calendar {
    private:
      static const int UNSPECIFIED_EVENT_DATE_PART = -1;
      typedef std::string Event;
      typedef std::map<const D, std::set<Event>> EventCollection;

      D current_date;
      EventCollection events;

      D fill_blanks_in_date(int day, int month, int year) const;

    public:
      Calendar();
      Calendar(const Calendar& original);

      Calendar& operator=(const Calendar& other);

      bool set_date(int year, int month, int day);

      bool add_event(const Event& event,
        int day   = UNSPECIFIED_EVENT_DATE_PART,
        int month = UNSPECIFIED_EVENT_DATE_PART,
        int year  = UNSPECIFIED_EVENT_DATE_PART);
      bool remove_event(const Event& event,
        int day   = UNSPECIFIED_EVENT_DATE_PART,
        int month = UNSPECIFIED_EVENT_DATE_PART,
        int year  = UNSPECIFIED_EVENT_DATE_PART);

      std::ostream& printTo(std::ostream& os) const;
  };

  template<class D>
  std::ostream& operator<<(std::ostream& os, const Calendar<D>& cal);

  // Implementations

  template<class D>
  Calendar<D>::Calendar() : current_date(D{}), events(EventCollection{}) {}

  template<class D>
  Calendar<D>::Calendar(const Calendar& original) : current_date(original.current_date), events(original.events) {}

  template<class D>
  Calendar<D>& Calendar<D>::operator=(const Calendar& original) {
    current_date = original.current_date;
    events = original.events;
  }

  template<class D>
  D Calendar<D>::fill_blanks_in_date(int day, int month, int year) const {
    if(day == UNSPECIFIED_EVENT_DATE_PART) {
      day = current_date.day();
    }
    if(month == UNSPECIFIED_EVENT_DATE_PART) {
      month = current_date.month();
    }
    if(year == UNSPECIFIED_EVENT_DATE_PART) {
      year = current_date.year();
    }
    return D{year, month, day};
  }

  template<class D>
  bool Calendar<D>::set_date(const int year, const int month, const int day) {
    try {
      current_date = D{year, month, day};
      return true;
    } catch(std::out_of_range e) {
      return false;
    }
  }

  template<class D>
  bool Calendar<D>::add_event(const Event& event, int day, int month, int year) {
    const D target_date = fill_blanks_in_date(day, month, year);
    return events[target_date].insert(event).second;
  }

  template<class D>
  bool Calendar<D>::remove_event(const Event& event, int day, int month, int year) {
    const D target_date = fill_blanks_in_date(day, month, year);
    return events[target_date].erase(event) > 0;
  }

  template<class D>
  std::ostream& Calendar<D>::printTo(std::ostream& os) const {
    for(typename EventCollection::const_iterator it = events.lower_bound(current_date);
        it != events.end();
        ++it) {
      for(const Event event : it->second) {
        os << it->first << " : " << event << std::endl;
      }
    }
    return os;
  }

  template<class D>
  std::ostream& operator<<(std::ostream& os, const Calendar<D>& cal) {
    return cal.printTo(os);;
  }

}
