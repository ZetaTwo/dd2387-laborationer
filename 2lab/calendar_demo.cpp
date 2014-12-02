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

  c.add_recurring_event(RecurringEvent{"Rymdfotbollsträning", Gregorian{2047, 11, 23}, RecurringEvent::RecurringType::WEEKLY});
  c.add_event("Besöka mormor på månen", 15, 3);
  c.add_event("Flytta till Mars", 28, 3);
  cout << c << endl;

}
