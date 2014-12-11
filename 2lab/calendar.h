#pragma once
#include <string>
#include <ostream>
#include <map>
#include <set>
#include <list>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <memory>
#include "date.h"

namespace lab2 {

  template<class D>
  class Calendar {
    public:
      enum format { list, cal, iCalendar };

    private:
      format current_format = list;

      typedef std::string Event;
      typedef std::map<const D, std::list<Event> > EventCollection;

      struct EventRelation {
        std::string dependee_event;
        std::string dependent_event;
        D dependee_date;
        int dependent_offset;

        D get_dependent_date() const;
      };

      D current_date;
      EventCollection events;
      std::list<EventRelation> event_relations;
      std::map<std::string, D> birthdays;

      bool event_exists_at_date(const Event& event, const Date& date) const;
      void remove_event_relations(const Event& event, const Date& date);
      void move_related_events(const Event& base_event, const Date& base_event_from, const Date& base_event_to);

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
          std::unique_ptr<Date> end_date; // Inclusive
          std::set<D> exceptions;

          RecurringType recurring_type;

          const int period_multiplier;

        public:
          const std::string event;

          RecurringEvent(const RecurringEvent& e);
          RecurringEvent(const std::string& event, const Date& begin_date, RecurringType recurring_type);
          RecurringEvent(const std::string& event, const Date& begin_date, RecurringType recurring_type, const Date& end_date);
          RecurringEvent(const std::string& event, const Date& begin_date, RecurringType recurring_type, unsigned int period_multiplier);
          RecurringEvent(const std::string& event, const Date& begin_date, RecurringType recurring_type, const Date& end_date, unsigned int period_multiplier);

          class const_iterator : std::iterator<std::forward_iterator_tag, const D> {
              const RecurringEvent& parent;
              D current_date;
            public:
              const_iterator(const RecurringEvent& parent);
              const_iterator& operator++();
              const_iterator  operator++(int);
              bool has_next() const;
              const Date& operator*()  const;
              const Date* operator->() const;
          };

          bool operator==(const RecurringEvent& other) const;
          bool occurs_on(const Date& date) const;
          bool add_exception(const Date& date);

          const_iterator begin() const;
      };

      Calendar();

      template<class D_other>
      Calendar(const Calendar<D_other>& original);

      inline const Date& get_date() const { return current_date; }
      inline const EventCollection& get_static_events() const { return events; }
      const std::list<Event> get_events(const Date& d) const;

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
      int compute_age(const std::string& name, const Date& target_day);

      bool add_recurring_event(const RecurringEvent& recurring_event);
      bool remove_recurring_event(const RecurringEvent& recurring_event);
      bool cancel_recurring_event_instance(const RecurringEvent& recurring_event, const Date& cancelDate);

      void set_format(const format& f) {
        current_format = f;
      }

      void print_events(const Date& begin_date, const Date& end_date) const;
      std::ostream& print_list(std::ostream& os) const;
      std::ostream& print_events(const Date& begin_date, const Date& end_date, std::ostream& os) const;
      std::ostream& print_calendar(std::ostream& os, const Date& month) const;
      std::ostream& print_ical(std::ostream& os) const;

      friend std::ostream& operator<<(std::ostream& os, const Calendar& calendar) {
        switch(calendar.current_format) {
        case cal:
          return calendar.print_calendar(os, calendar.get_date());
        }
        return calendar.print_list(os);
      }

    private:
      std::list<RecurringEvent> recurring_events;
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
  bool Calendar<D>::event_exists_at_date(const Event& event, const Date& date) const {
    try {
      const std::list<Event>& existingFromEvents = events.at(date);
      return std::find(
          existingFromEvents.begin(),
          existingFromEvents.end(),
          event
        ) != existingFromEvents.end();
    } catch(std::out_of_range e) {
      return false;
    }
  }

  template<class D>
  const std::list<typename Calendar<D>::Event> Calendar<D>::get_events(const Date& date) const {
    std::list<Event> result;

    try {
      std::copy(events.at(date).begin(), events.at(date).end(), std::back_inserter(result));
    } catch(std::out_of_range e) {
      // Whoops, looks like there were no static events on that day
    }

    for(const RecurringEvent& revent : recurring_events) {
      if(revent.occurs_on(date)) {
        result.push_back(revent.event);
      }
    }

    return result;
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

      remove_event_relations(event, target_date);

      return true;
    }
    catch (std::out_of_range e) {
      return false;
    }
  }

  template<class D>
  void Calendar<D>::remove_event_relations(const Event& event, const Date& target_date) {
    std::list<typename std::list<EventRelation>::iterator> dead_relations_iterators;
    std::list<EventRelation> relations_based_on_argument_event;

    // Copy EventRelations to another list so we can modify the original list in recursive remove_event calls
    for(
        typename std::list<EventRelation>::iterator rel_it = event_relations.begin();
        rel_it != event_relations.end();
        ++rel_it
        ) {
      const EventRelation& rel = *rel_it;
      if(rel.dependee_event == event && rel.dependee_date == target_date) {
        // This event is the base for other events related to it
        relations_based_on_argument_event.push_back(rel);
        dead_relations_iterators.push_back(rel_it);
      } else if(rel.dependent_event == event && rel.get_dependent_date() == target_date) {
        // This event is related to some other one, remove this dead relation
        dead_relations_iterators.push_back(rel_it);
      }
    }

    for(const typename std::list<EventRelation>::iterator rel_it : dead_relations_iterators) {
      event_relations.erase(rel_it);
    }
    for(const EventRelation rel : relations_based_on_argument_event) {
      const Date& dependent_date = rel.get_dependent_date();
      remove_event(rel.dependent_event, dependent_date.day(), dependent_date.month(), dependent_date.year());
    }
  }

  template<class D>
  bool Calendar<D>::move_event(const Date& from, const Date& to, Event event) {
    if(!event_exists_at_date(event, from) || event_exists_at_date(event, to)) {
      return false;
    }

    move_related_events(event, from, to);

    return add_event(event, to.day(), to.month(), to.year())
      && remove_event(event, from.day(), from.month(), from.year());
  }

  template<class D>
  void Calendar<D>::move_related_events(const Event& base_event, const Date& base_event_from, const Date& base_event_to) {
    std::list<EventRelation> relations_based_on_argument_event;

    // Copy EventRelations to another list so we can modify the original list in recursive move_event calls
    for(EventRelation& rel : event_relations) {
      if(rel.dependee_event == base_event && rel.dependee_date == base_event_from) {
        relations_based_on_argument_event.push_back(rel);
      }
    }
    for(EventRelation& rel : relations_based_on_argument_event) {
      D new_dependent_date = rel.get_dependent_date();
      new_dependent_date += (base_event_to - base_event_from);
      if(move_event(rel.get_dependent_date(), new_dependent_date, rel.dependent_event)) {
        rel.dependee_date = base_event_to;
        event_relations.push_back(rel);
      }
    }
  }

  template<class D>
  bool Calendar<D>::add_related_event(const Date& rel_date, int days, std::string rel_event, std::string new_event) {
    if(!event_exists_at_date(rel_event, rel_date)) {
      return false;
    }
    D new_date = rel_date;
    new_date += days;
    if(add_event(new_event, new_date.day(), new_date.month(), new_date.year())) {
      event_relations.push_back(EventRelation{rel_event, new_event, rel_date, days});
      return true;
    }
    return false;
  }

  template<class D>
  bool Calendar<D>::add_birthday(const std::string& name, const Date& birthday) {
    if(birthdays.count(name) > 0) {
      return false;
    }
    birthdays[name] = birthday;
    return true;
  }

  template<class D>
  int Calendar<D>::compute_age(const std::string& name, const Date& target_date) {
    const Date& birthday = birthdays.at(name);
    const int year_diff = target_date.year() - birthday.year();
    if(target_date.month() < birthday.month()) {
      return year_diff - 1;
    }
    if(target_date.month() == birthday.month()) {
      const int year = target_date.year();
      const bool target_date_is_in_gregorian_leap_year =
          ((year % 400) == 0) || (((year % 4) == 0) && ((year % 100) != 0));

      if(birthday.month() == 2
          && birthday.day() == 29
          && target_date.day() == 28
          && !target_date_is_in_gregorian_leap_year) {
        return year_diff;
      }
      return year_diff - (target_date.day() < birthday.day() ? 1 : 0);
    }
    return year_diff;
  }

  template<class D>
  bool Calendar<D>::add_recurring_event(const RecurringEvent& recurring_event) {
    recurring_events.push_back(recurring_event);
    return true;
  }

  template<class D>
  bool Calendar<D>::remove_recurring_event(const RecurringEvent& recurring_event) {
    const size_t size_before = recurring_events.size();
    recurring_events.remove(recurring_event);
    return size_before > recurring_events.size();
  }

  template<class D>
  bool Calendar<D>::cancel_recurring_event_instance(const RecurringEvent& recurring_event, const Date& cancelDate) {
    auto it = std::find(recurring_events.begin(), recurring_events.end(), recurring_event);
    if(it != recurring_events.end()) {
      return it->add_exception(cancelDate);
    }
    return false;
  }

  template<class D>
  std::ostream& Calendar<D>::print_list(std::ostream& os) const {
    const typename EventCollection::const_reverse_iterator last_static_event_date_it = std::find_if(
      get_static_events().rbegin(),
      get_static_events().rend(),
      [](const typename EventCollection::const_reverse_iterator::value_type& pair) {
        return pair.second.size() > 0;
      }
    );

    if(last_static_event_date_it != get_static_events().rend()) {
      const Date& last_static_event_date = last_static_event_date_it->first;
      for(D iter_date = get_date(); iter_date <= last_static_event_date; ++iter_date) {
        for(const Event& e : get_events(iter_date)) {
          os << iter_date << " : " << e << std::endl;
        }
      }
    }

    return os;
  }

  template<class D>
  void Calendar<D>::print_events(const Date& begin_date, const Date& end_date) const {
    print_events(begin_date, end_date, std::cout);
  }

  template<class D>
  std::ostream& Calendar<D>::print_calendar(std::ostream& os, const Date& month) const {
    D first_day_of_month{month};
    first_day_of_month -= month.day() - 1;

    os << "     " << month.month_name() << " " << month.year() << std::endl;
    os << " må  ti  on  to  fr  lö  sö" << std::endl;

    for(int i = 0; i < first_day_of_month.week_day() - 1; ++i) {
      os << "    ";
    }
    for(D day = first_day_of_month; day.month() == month.month(); ++day) {
      if(day == get_date()) {
        os << "<";
      } else {
        os << " ";
      }
      if(day.day() < 10) {
        os << " ";
      }
      os << day.day();
      if(get_events(day).size() > 0) {
        os << "*";
      } else if(day == get_date()) {
        os << ">";
      } else if(day.week_day() < 7 && day.day() < month.days_this_month()) {
        os << " ";
      }
      if(day.week_day() == 7 || day.day() == month.days_this_month()) {
        os << std::endl;
      }
    }

    os << std::endl;

    for(D day = first_day_of_month; day.month() == month.month(); ++day) {
      for(const auto& e : get_events(day)) {
        os << "  " << day << ": " << e << std::endl;
      }
    }

    return os;
  }

  template<class D>
  std::ostream& Calendar<D>::print_events(const Date& begin_date, const Date& end_date, std::ostream& os) const {
    for(D iter_date = begin_date; iter_date <= end_date; ++iter_date) {
      for(Event e : get_events(iter_date)) {
        os << iter_date << " : " << e << std::endl;
      }
    }
    return os;
  }

  template<class D>
  std::ostream& Calendar<D>::print_ical(std::ostream& os) const {
    os << "BEGIN:VCALENDAR" << std::endl
       << "VERSION:2.0" << std::endl
       << "PRODID:-//carlsvemlun//A good (enough) calendar by <strike>Calle Svensson</strike> and Emil Lundberg and Calle Svensson//" << std::endl;

    return os << "END:VCALENDAR" << std::endl;
  }

  template<class D>
  D Calendar<D>::EventRelation::get_dependent_date() const {
    D result = dependee_date;
    result += dependent_offset;
    return result;
  }

  template<class D>
  Calendar<D>::RecurringEvent::RecurringEvent(const RecurringEvent& original) :
    begin_date(original.begin_date),
    end_date(original.end_date == nullptr ? nullptr : new D{*original.end_date}),
    recurring_type(original.recurring_type),
    period_multiplier(original.period_multiplier),
    event(original.event) {}

  template<class D>
  Calendar<D>::RecurringEvent::RecurringEvent(const std::string& event, const Date& begin_date, RecurringType recurring_type) :
    begin_date(begin_date),
    end_date(nullptr),
    recurring_type(recurring_type),
    period_multiplier(1),
    event(event) {}

  template<class D>
  Calendar<D>::RecurringEvent::RecurringEvent(const std::string& event, const Date& begin_date, RecurringType recurring_type, const Date& end_date) :
    begin_date(begin_date),
    end_date(new D{end_date}),
    recurring_type(recurring_type),
    period_multiplier(1),
    event(event) {}

  template<class D>
  Calendar<D>::RecurringEvent::RecurringEvent(const std::string& event, const Date& begin_date, RecurringType recurring_type, unsigned int period_multiplier) :
    begin_date(begin_date),
    end_date(nullptr),
    recurring_type(recurring_type),
    period_multiplier(period_multiplier),
    event(event) {}

  template<class D>
  Calendar<D>::RecurringEvent::RecurringEvent(const std::string& event, const Date& begin_date, RecurringType recurring_type, const Date& end_date, unsigned int period_multiplier) :
    begin_date(begin_date),
    end_date(new D{end_date}),
    recurring_type(recurring_type),
    period_multiplier(period_multiplier),
    event(event) {}

  template<class D>
  bool Calendar<D>::RecurringEvent::operator==(const RecurringEvent& other) const {
    return begin_date == other.begin_date && event == other.event;
  }

  template<class D>
  bool Calendar<D>::RecurringEvent::occurs_on(const Date& date) const {
    if(exceptions.count(date) > 0) {
      return false;
    }
    for(RecurringEvent::const_iterator it = begin(); *it <= date && it.has_next(); ++it) {
      if(*it == date) {
        return true;
      }
    }
    return false;
  }

  template<class D>
  bool Calendar<D>::RecurringEvent::add_exception(const Date& exception_date) {
    exceptions.insert(exception_date);
    return true;
  }

  template<class D>
  typename Calendar<D>::RecurringEvent::const_iterator Calendar<D>::RecurringEvent::begin() const {
    return const_iterator{*this};
  }


  template<class D>
  Calendar<D>::RecurringEvent::const_iterator::const_iterator(const RecurringEvent& parent) : parent(parent), current_date(parent.begin_date) {}

  template<class D>
  typename Calendar<D>::RecurringEvent::const_iterator& Calendar<D>::RecurringEvent::const_iterator::operator++() {
    switch(parent.recurring_type) {
    case DAILY:
      ++current_date;
      break;
    case WEEKLY:
      current_date += 7;
      break;
    case MONTHLY:
      current_date.add_month();
      break;
    case YEARLY:
      current_date.add_year();
      break;
    }
    return *this;
  }

  template<class D>
  typename Calendar<D>::RecurringEvent::const_iterator Calendar<D>::RecurringEvent::const_iterator::operator++(int) {
    const_iterator tmp(*this);
    operator++();
    return tmp;
  }

  template<class D>
  bool Calendar<D>::RecurringEvent::const_iterator::has_next() const {
    return parent.end_date == nullptr || current_date <= *parent.end_date;
  }

  template<class D>
  const Date& Calendar<D>::RecurringEvent::const_iterator::operator*()  const {
    return current_date;
  }

  template<class D>
  const Date* Calendar<D>::RecurringEvent::const_iterator::operator->() const {
    return &current_date;
  }

}
