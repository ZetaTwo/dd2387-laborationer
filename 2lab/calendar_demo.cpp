#include <iostream>

#include "gregorian.h"
#include "calendar.h"
#include "kattistime.h"

using namespace lab2;

using std::cout;
using std::endl;

typedef Calendar<Gregorian>::RecurringEvent RecurringEvent;

int main() {
  set_k_time(0);

  Calendar<Gregorian> c;
  cout << c << endl;
  c.set_date(2048, 1, 1);

  c.add_event("Besöka mormor på månen", 29, 2);
  c.add_event("Besöka mormor på månen", 5, 3);
  cout << c << endl;

  c.move_event(Gregorian{2048, 2, 29}, Gregorian{2048, 3, 1}, "Besöka mormor på månen");
  cout << c << endl;

  const RecurringEvent training{"Rymdfotbollsträning", Gregorian{2047, 11, 23}, RecurringEvent::RecurringType::WEEKLY};

  c.add_recurring_event(training);
  c.add_event("Besöka mormor på månen", 15, 3);
  c.add_event("Flytta till Mars", 28, 3);
  cout << c << endl;

  c.cancel_recurring_event_instance(training, Gregorian{2048, 1, 11});
  cout << c << endl;

}
