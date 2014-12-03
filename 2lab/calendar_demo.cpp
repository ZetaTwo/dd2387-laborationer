#include <iostream>
#include <string>

#include "gregorian.h"
#include "calendar.h"
#include "kattistime.h"

using namespace lab2;

using std::cout;
using std::endl;

typedef Calendar<Gregorian>::RecurringEvent RecurringEvent;

int main() {
  set_k_time(0);

  const std::string granny = "Besöka mormor på månen";
  const std::string move = "Flytta till Mars";

  Calendar<Gregorian> c;
  cout << c << endl;
  c.set_date(2332, 1, 1);

  c.add_event(granny, 29, 2);
  c.add_event(granny, 5, 3);
  cout << c << endl;

  c.move_event(Gregorian{2332, 2, 29}, Gregorian{2332, 3, 1}, granny);
  cout << c << endl;

  const RecurringEvent training{"Rymdfotbollsträning", Gregorian{2047, 11, 23}, RecurringEvent::RecurringType::WEEKLY, Gregorian{2332, 3, 7}};
  const RecurringEvent meditation{"Meditation", Gregorian{2047, 11, 23}, RecurringEvent::RecurringType::DAILY, 3};

  c.add_recurring_event(training);
  c.add_recurring_event(meditation);
  c.add_event(granny, 15, 3);
  c.add_event(move, 28, 3);
  cout << c << endl;

  c.cancel_recurring_event_instance(training, Gregorian{2332, 1, 11});
  cout << c << endl;

  c.add_related_event(Gregorian{2332, 3, 28}, 170, move, "Inflyttning");
  cout << c << endl;

  c.move_event(Gregorian{2332, 3, 28}, Gregorian{2332, 5, 17}, move);
  cout << c << endl;

  c.print_events(Gregorian{2332, 2, 15}, Gregorian{2332, 3, 15});

  c.remove_recurring_event(meditation);
  cout << c << endl;

}
