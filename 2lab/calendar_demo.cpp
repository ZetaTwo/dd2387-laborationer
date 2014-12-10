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

  const RecurringEvent training{"Rymdfotbollsträning", Gregorian{2331, 11, 23}, RecurringEvent::RecurringType::WEEKLY, Gregorian{2332, 3, 7}};
  const RecurringEvent spacesuit{"Kontrollera rymddräkten", Gregorian{2331, 11, 23}, RecurringEvent::RecurringType::MONTHLY, 3};

  c.add_recurring_event(training);
  c.add_recurring_event(spacesuit);
  c.add_event(granny, 15, 3);
  c.add_event(move, 28, 3);
  cout << c << endl;

  c.cancel_recurring_event_instance(training, Gregorian{2332, 1, 11});
  cout << c << endl;

  c.add_related_event(Gregorian{2332, 3, 28}, 170, move, "Inflyttning");
  cout << c << endl;

  c.add_related_event(Gregorian{2332, 9, 14}, 14, "Inflyttning", "Inflyttningsfest");
  cout << c << endl;

  c.move_event(Gregorian{2332, 3, 28}, Gregorian{2332, 5, 17}, move);
  cout << c << endl;

  c.move_event(Gregorian{2332, 5, 17}, Gregorian{2332, 5, 18}, move);
  cout << c << endl;

  // After this, Inflyttningsfest should not move when Inflyttning moves
  c.remove_event("Inflyttningsfest", 18, 11, 2332);
  c.add_event("Inflyttningsfest", 18, 11, 2332);
  cout << c << endl;

  c.move_event(Gregorian{2332, 5, 18}, Gregorian{2332, 5, 19}, move);
  cout << c << endl;

  c.print_events(Gregorian{2332, 2, 15}, Gregorian{2332, 3, 15});

  c.remove_recurring_event(spacesuit);
  cout << c << endl;

  c.add_birthday("Mormor", Gregorian{2016, 2, 29});
  cout << c << endl;

  cout << c.compute_age("Mormor", Gregorian{2332, 2, 28}) << endl;
  cout << c.compute_age("Mormor", Gregorian{2332, 2, 29}) << endl;
  cout << c.compute_age("Mormor", Gregorian{2332, 3, 1}) << endl;
  cout << c.compute_age("Mormor", Gregorian{2333, 2, 27}) << endl;
  cout << c.compute_age("Mormor", Gregorian{2333, 2, 28}) << endl;

  c.print_calendar(cout, Gregorian{2332, 2, 15});
  c.print_calendar(cout, Gregorian{2333, 2, 15});

  c.set_format(c.format::cal);
  cout << c << endl;

  c.set_date(2332, 1, 4);
  cout << c << endl;

}
