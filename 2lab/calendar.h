#pragma once
#include <string>
#include <ostream>
#include <map>
#include <list>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include "date.h"

namespace lab2 {

  template<class D>
  class Calendar {
      typedef std::string Event;
      typedef std::map<const D, std::list<Event> > EventCollection;

      D current_date;
      EventCollection events;

    public:
      class RecurringEvent {
        public:
          enum RecurringType {
            DAILY,
            WEEKLY,
            MONTHLY,
            YEARLY
          };

        private:
          D begin_date;   // Inclusive
          Date* end_date; // Inclusive

          RecurringType recurring_type;

          const int period_multiplier;

          const std::string event;

        public:

          RecurringEvent(const std::string& event, const Date& begin_date, RecurringType recurringType);
          RecurringEvent(const std::string& event, const Date& begin_date, RecurringType recurringType, const Date& end_date);
          RecurringEvent(const std::string& event, const Date& begin_date, RecurringType recurringType, unsigned int period_multiplier);
          RecurringEvent(const std::string& event, const Date& begin_date, RecurringType recurringType, const Date& end_date, unsigned int period_multiplier);

          ~RecurringEvent();

          class const_iterator : std::iterator<std::forward_iterator_tag, const D> {
              D current_date;
            public:
              const_iterator();
              const_iterator& operator++();
              const_iterator  operator++(int);
              bool operator==(const const_iterator& rhs) const;
              bool operator!=(const const_iterator& rhs) const;
              bool operator> (const const_iterator& rhs) const;
              bool operator< (const const_iterator& rhs) const;
              const Date& operator*()  const;
              const Date* operator->() const;
          };

          const_iterator begin() const;
          const_iterator end()   const;
      };

      Calendar();

      template<class D_other>
      Calendar(const Calendar<D_other>& original);

      inline const Date& get_date() const { return current_date; }
      inline const EventCollection& get_static_events() const { return events; }

      bool set_date(int year, int month, int day);

      bool add_event(const Event& event, int day, int month, int year);
      inline bool add_event(const Event& event, const int day, const int month) {
        return add_event(event, day, month, current_date.year());
      }
      inline bool add_event(const Event& event, const int day) {
        return add_event(event, day, current_date.month());
      }
      inline bool add_event(const Event& event) {
        return add_event(event, current_date.day());
      }

      bool remove_event(const Event& event, int day, int month, int year);
      inline bool remove_event(const Event& event, const int day, const int month) {
        return remove_event(event, day, month, current_date.year());
      }
      inline bool remove_event(const Event& event, const int day) {
        return remove_event(event, day, current_date.month());
      }
      inline bool remove_event(const Event& event) {
        return remove_event(event, current_date.day());
      }

      bool move_event(const Date& from, const Date& to, Event event);
      bool add_related_event(const Date& rel_date, int days, std::string rel_event, std::string new_event);
      bool add_birthday(const std::string& name, const Date& birthday);
      bool compute_age(const std::string& name, const Date& target_day);

      bool add_recurring_event(const RecurringEvent& recurring_event);

      friend std::ostream& operator<<(std::ostream& os, const Calendar& cal) {
        for(typename EventCollection::const_iterator it = cal.get_static_events().lower_bound(cal.get_date());
            it != cal.get_static_events().end();
            ++it) {
          if (it->first <= cal.get_date()) {
            continue;
          }
          for(const Event event : it->second) {
            os << it->first << " : " << event << std::endl;
          }
        }
        return os;
      }
  };

  // Implementations

  template<class D>
  Calendar<D>::Calendar() : current_date(D{}), events(EventCollection{}) {}

  template<class D>
  template<class D_other>
  Calendar<D>::Calendar(const Calendar<D_other>& original) : current_date(original.get_date()), events(EventCollection{}) {
    for(const std::pair<const D_other, const std::list<std::string>> date_and_events : original.get_static_events()) {
      events[date_and_events.first] = date_and_events.second;
    }
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
      const D target_date{year, month, day};
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
      const D target_date{year, month, day};
     
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

}
