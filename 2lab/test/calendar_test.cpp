#include <gtest/gtest.h>
#include <string>
#include "kattistime.h"
#include "calendar.h"
#include "gregorian.h"

using ::testing::TestWithParam;
using ::testing::Values;
using std::get;

using lab2::Calendar;
using lab2::Gregorian;
using std::string;
typedef lab2::Calendar<Gregorian>::RecurringEvent RecurringEvent;
typedef RecurringEvent::RecurringType RecurringType;

TEST(Calendar, MoveEventMovesEventFromOriginDateToTargetDate) {
  const Gregorian from { 2014, 11, 7 };
  const Gregorian to   { 2014, 11, 8 };
  const string event = "foo";

  set_k_time(0);
  Calendar<Gregorian> cal;

  cal.add_event(event, from.day(), from.month(), from.year());

  ASSERT_EQ(1, cal.get_static_events().at(from).size());
  ASSERT_EQ(event, cal.get_static_events().at(from).front());
  ASSERT_THROW({
    cal.get_static_events().at(to);
  }, std::out_of_range);

  const bool success = cal.move_event(from, to, event);
  EXPECT_TRUE(success);

  EXPECT_EQ(0, cal.get_static_events().at(from).size());
  EXPECT_EQ(1, cal.get_static_events().at(to).size());
  EXPECT_EQ(event, cal.get_static_events().at(to).front());
}

TEST(Calendar, MoveEventReturnsFalseIfEventDoesNotExistAtOriginDate) {
  const Gregorian from { 2014, 11, 7 };
  const Gregorian to   { 2014, 11, 8 };
  const string event = "foo";

  set_k_time(0);
  Calendar<Gregorian> cal;

  ASSERT_THROW({
    cal.get_static_events().at(from);
  }, std::out_of_range);
  ASSERT_THROW({
    cal.get_static_events().at(to);
  }, std::out_of_range);

  const bool success = cal.move_event(from, to, event);
  EXPECT_FALSE(success);
}

TEST(Calendar, MoveEventReturnsFalseAndDoesNothingIfEventAlreadyExistsAtTargetDate) {
  const Gregorian from { 2014, 11, 7 };
  const Gregorian to   { 2014, 11, 8 };
  const string event = "foo";

  set_k_time(0);
  Calendar<Gregorian> cal;

  cal.add_event(event, from.day(), from.month(), from.year());
  cal.add_event(event, to.day(), to.month(), to.year());

  ASSERT_EQ(1, cal.get_static_events().at(from).size());
  ASSERT_EQ(1, cal.get_static_events().at(to).size());
  ASSERT_EQ(event, cal.get_static_events().at(from).front());
  ASSERT_EQ(event, cal.get_static_events().at(to).front());

  const bool success = cal.move_event(from, to, event);
  EXPECT_FALSE(success);

  EXPECT_EQ(1, cal.get_static_events().at(from).size());
  EXPECT_EQ(1, cal.get_static_events().at(to).size());
  EXPECT_EQ(event, cal.get_static_events().at(from).front());
  EXPECT_EQ(event, cal.get_static_events().at(to).front());
}

TEST(Calendar, AddRelatedEventAddsEventAtGivenOffsetRelativeToBaseEvent) {
  const Gregorian base_date { 2014, 11, 7 };
  const string base_event = "foo";
  const int related_days = 1;
  const string related_event = "bar";

  Gregorian related_date{base_date};
  related_date += related_days;

  set_k_time(0);
  Calendar<Gregorian> cal;

  cal.add_event(base_event, base_date.day(), base_date.month(), base_date.year());

  ASSERT_EQ(1, cal.get_static_events().at(base_date).size());
  ASSERT_EQ(base_event, cal.get_static_events().at(base_date).front());
  ASSERT_THROW({
    cal.get_static_events().at(related_date);
  }, std::out_of_range);

  const bool success = cal.add_related_event(base_date, related_days, base_event, related_event);
  EXPECT_TRUE(success);

  EXPECT_EQ(1, cal.get_static_events().at(base_date).size());
  EXPECT_EQ(1, cal.get_static_events().at(base_date).size());
  EXPECT_EQ(base_event, cal.get_static_events().at(base_date).front());
  EXPECT_EQ(related_event, cal.get_static_events().at(related_date).front());
}

TEST(Calendar, AddRelatedEventReturnsFalseAndDoesNothingIfBaseEventDoesNotExist) {
  const Gregorian base_date { 2014, 11, 7 };
  const string base_event = "foo";
  const int related_days = 1;
  const string related_event = "bar";

  Gregorian related_date{base_date};
  related_date += related_days;

  set_k_time(0);
  Calendar<Gregorian> cal;

  ASSERT_THROW({
    cal.get_static_events().at(base_date);
  }, std::out_of_range);

  const bool success = cal.add_related_event(base_date, related_days, base_event, related_event);
  EXPECT_FALSE(success);

  EXPECT_THROW({
    cal.get_static_events().at(base_date);
  }, std::out_of_range);
  EXPECT_THROW({
    cal.get_static_events().at(related_date);
  }, std::out_of_range);
}

TEST(Calendar, AddRelatedEventReturnsFalseAndDoesNothingIfRelativeEventCollidesWithExistingEvent) {
  const Gregorian base_date { 2014, 11, 7 };
  const string base_event = "foo";
  const int related_days = 1;
  const string related_event = "bar";

  Gregorian related_date{base_date};
  related_date += related_days;

  set_k_time(0);
  Calendar<Gregorian> cal;

  cal.add_event(base_event, base_date.day(), base_date.month(), base_date.year());
  cal.add_event(related_event, related_date.day(), related_date.month(), related_date.year());

  ASSERT_EQ(1, cal.get_static_events().at(base_date).size());
  ASSERT_EQ(base_event, cal.get_static_events().at(base_date).front());
  ASSERT_EQ(1, cal.get_static_events().at(related_date).size());
  ASSERT_EQ(related_event, cal.get_static_events().at(related_date).front());

  const bool success = cal.add_related_event(base_date, related_days, base_event, related_event);
  EXPECT_FALSE(success);

  EXPECT_EQ(1, cal.get_static_events().at(base_date).size());
  EXPECT_EQ(base_event, cal.get_static_events().at(base_date).front());
  EXPECT_EQ(1, cal.get_static_events().at(related_date).size());
  EXPECT_EQ(related_event, cal.get_static_events().at(related_date).front());
}

TEST(Calendar, RelatedEventIsMovedWhenBaseEventIsMoved) {
  const Gregorian base_date { 2014, 11, 7 };
  const int move_base_days = 7;
  const string base_event = "foo";
  const int related_days = 1;
  const string related_event = "bar";

  Gregorian related_date{base_date};
  related_date += related_days;

  Gregorian moved_base_date{base_date};
  moved_base_date += move_base_days;

  Gregorian moved_related_date{related_date};
  moved_related_date += move_base_days;

  set_k_time(0);
  Calendar<Gregorian> cal;

  cal.add_event(base_event, base_date.day(), base_date.month(), base_date.year());
  cal.add_related_event(base_date, related_days, base_event, related_event);

  ASSERT_EQ(1, cal.get_static_events().at(base_date).size());
  ASSERT_EQ(base_event, cal.get_static_events().at(base_date).front());
  ASSERT_EQ(1, cal.get_static_events().at(related_date).size());
  ASSERT_EQ(related_event, cal.get_static_events().at(related_date).front());

  const bool success = cal.move_event(base_date, moved_base_date, base_event);
  EXPECT_TRUE(success);

  EXPECT_EQ(0, cal.get_static_events().at(base_date).size());
  EXPECT_EQ(0, cal.get_static_events().at(related_date).size());

  EXPECT_EQ(1, cal.get_static_events().at(moved_base_date).size());
  EXPECT_EQ(1, cal.get_static_events().at(moved_related_date).size());
  EXPECT_EQ(base_event, cal.get_static_events().at(moved_base_date).front());
  EXPECT_EQ(related_event, cal.get_static_events().at(moved_related_date).front());
}

class BirthdayTest : public TestWithParam<std::tuple<int, int, int, int, int, int, int>> {};
INSTANTIATE_TEST_CASE_P(Calendar, BirthdayTest, Values(
  // birthday y, m, d, test day y, m, d, expected age
  std::tuple<int, int, int, int, int, int, int>{ 2000,  2, 29, 2000,  2, 29,  0 },
  std::tuple<int, int, int, int, int, int, int>{ 2000,  2, 29, 2000,  3,  1,  0 },
  std::tuple<int, int, int, int, int, int, int>{ 2000,  2, 29, 2004,  2, 29,  4 },
  std::tuple<int, int, int, int, int, int, int>{ 2000,  2, 29, 2005,  2, 28,  5 },
  std::tuple<int, int, int, int, int, int, int>{ 1995, 10, 30, 2027, 10, 29, 31 },
  std::tuple<int, int, int, int, int, int, int>{ 1995, 10, 30, 2027, 10, 30, 32 },
  std::tuple<int, int, int, int, int, int, int>{ 1995, 10, 30, 2027, 12, 24, 32 }
));

TEST_P(BirthdayTest, BirthdaysAreComputedCorrectly) {
  const Gregorian birthday { get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()) };
  const Gregorian test_day { get<3>(GetParam()), get<4>(GetParam()), get<5>(GetParam()) };
  const int expected_age = get<6>(GetParam());
  const std::string name = "Alexander";

  set_k_time(0);
  Calendar<Gregorian> cal;

  cal.add_birthday(name, birthday);

  EXPECT_EQ(expected_age, cal.compute_age(name, test_day));
}

TEST(Calendar, RecurringEventCanRecurDailyForever) {
  const Gregorian begin_date{2000, 12, 24};
  const string event = "Vattna blommorna";
  const unsigned int period_multiplier = 3;

  set_k_time(0);
  Calendar<Gregorian> cal;

  cal.add_recurring_event(RecurringEvent{event, begin_date, RecurringType::DAILY, period_multiplier});

  for(Gregorian d{begin_date}; d.year() < 4000; d += period_multiplier) {
    const std::list<string> day_events = cal.get_events(d);
    EXPECT_EQ(1, day_events.size());
    EXPECT_EQ(event, day_events.front());
  }
}

TEST(Calendar, RecurringEventCanRecurWeeklyForever) {
  const Gregorian begin_date{2000, 12, 24};
  const string event = "Fäktning";
  const unsigned int period_multiplier = 2;

  set_k_time(0);
  Calendar<Gregorian> cal;

  cal.add_recurring_event(RecurringEvent{event, begin_date, RecurringType::WEEKLY, period_multiplier});

  for(Gregorian d{begin_date}; d.year() < 4000; d += 7 * period_multiplier) {
    const std::list<string> day_events = cal.get_events(d);
    EXPECT_EQ(1, day_events.size());
    EXPECT_EQ(event, day_events.front());
  }
}

TEST(Calendar, RecurringEventCanRecurMonthlyForever) {
  const Gregorian begin_date{2000, 12, 24};
  const string event = "Kvartalsrapport";
  const unsigned int period_multiplier = 3;

  set_k_time(0);
  Calendar<Gregorian> cal;

  cal.add_recurring_event(RecurringEvent{event, begin_date, RecurringType::MONTHLY, period_multiplier});

  for(Gregorian d{begin_date}; d.year() < 4000; d.add_month(period_multiplier)) {
    const std::list<string> day_events = cal.get_events(d);
    EXPECT_EQ(1, day_events.size());
    EXPECT_EQ(event, day_events.front());
  }
}

TEST(Calendar, RecurringEventCanRecurYearlyForever) {
  const Gregorian begin_date{2000, 12, 24};
  const string event = "Julafton";
  const unsigned int period_multiplier = 5;

  set_k_time(0);
  Calendar<Gregorian> cal;

  cal.add_recurring_event(RecurringEvent{event, begin_date, RecurringType::YEARLY, period_multiplier});

  for(Gregorian y{begin_date}; y.year() < 4000; y.add_year(period_multiplier)) {
    const std::list<string> day_events = cal.get_events(y);
    EXPECT_EQ(1, day_events.size());
    EXPECT_EQ(event, day_events.front());
  }
}

TEST(Calendar, RecurringEventsCanBeLimited) {
  const Gregorian begin_date{2014, 2, 5};
  const Gregorian end_date{2014, 9, 25};
  const string event = "Fysikalen-rep";

  set_k_time(0);
  Calendar<Gregorian> cal;

  cal.add_recurring_event(RecurringEvent{event, begin_date, RecurringType::WEEKLY, end_date});

  EXPECT_THROW({
    cal.get_events(Gregorian{end_date.year(), end_date.month(), end_date.day() + 7});
  }, std::out_of_range);
}
