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

  Calendar<Gregorian> c;
  cout << c << endl;
  c.set_date(2048, 1, 1);

  c.add_event(granny, 29, 2);
  c.add_event(granny, 5, 3);
  cout << c << endl;

  c.move_event(Gregorian{2048, 2, 29}, Gregorian{2048, 3, 1}, granny);
  cout << c << endl;

  const RecurringEvent training{"Rymdfotbollsträning", Gregorian{2047, 11, 23}, RecurringEvent::RecurringType::WEEKLY};

  c.add_recurring_event(training);
  c.add_event(granny, 15, 3);
  c.add_event("Flytta till Mars", 28, 3);
  cout << c << endl;

  c.cancel_recurring_event_instance(training, Gregorian{2048, 1, 11});
  cout << c << endl;

}
