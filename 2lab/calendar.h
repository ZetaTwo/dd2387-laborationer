#pragma once
#include <string>
#include <ostream>
#include <map>
#include <list>
#include <stdexcept>
#include <algorithm>
#include "date.h"

namespace lab2 {

  template<class D>
  class Calendar {
    private:
      static const int UNSPECIFIED_EVENT_DATE_PART = -1;
      D fill_blanks_in_date(int day, int month, int year) const;

    public:
      Calendar();

      typedef std::string Event;
      typedef std::map<const D, std::list<Event> > EventCollection;

      D current_date;
      EventCollection events;

      template<class D_other>
      Calendar(const Calendar<D_other>& original);

      template<class D_other>
      Calendar& operator=(const Calendar<D_other>& other);

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
  template<class D_other>
  Calendar<D>::Calendar(const Calendar<D_other>& original) : current_date(original.current_date), events(EventCollection{}) {
    for(const typename Calendar<D_other>::EventCollection::value_type date_and_events : original.events) {
      events[date_and_events.first] = date_and_events.second;
    }
  }

  template<class D>
  template<class D_other>
  Calendar<D>& Calendar<D>::operator=(const Calendar<D_other>& original) {
    current_date = original.current_date;
    for(const typename Calendar<D_other>::EventCollection::value_type date_and_events : original.events) {
      events[date_and_events.first] = date_and_events.second;
    }
    return *this;
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
    return D{ year, month, day };
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
  bool Calendar<D>::add_event(const Event& event, const int day, const int month, const int year) {
    try {
      const D target_date = fill_blanks_in_date(day, month, year);
      std::list<Event>::iterator it = std::find(events[target_date].begin(), events[target_date].end(), event);
      if (it == events[target_date].end()) {
        events[target_date].push_back(event);
        return true;
      }
      else {
        return false;
      }
    }
    catch (std::out_of_range e) {
      return false;
    }
  }

  template<class D>
  bool Calendar<D>::remove_event(const Event& event, const int day, const int month, const int year) {
    try {
      const D target_date = fill_blanks_in_date(day, month, year);
     
      std::list<Event>::iterator it = std::find(events[target_date].begin(), events[target_date].end(), event);
      if (it == events[target_date].end()) {
        return false;
      }
      events[target_date].erase(it);
      return true;
    }
    catch (std::out_of_range e) {
      return false;
    }
  }

  template<class D>
  std::ostream& Calendar<D>::printTo(std::ostream& os) const {
    for(typename EventCollection::const_iterator it = events.lower_bound(current_date);
        it != events.end();
        ++it) {
      if (it->first <= current_date) {
        continue;
      }
      for(const Event event : it->second) {
        os << it->first << " : " << event << std::endl;
      }
    }
    return os;
  }

  template<class D>
  std::ostream& operator<<(std::ostream& os, const Calendar<D>& cal) {
    return cal.printTo(os);
  }

}
