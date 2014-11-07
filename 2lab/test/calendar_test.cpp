#include <gtest/gtest.h>
#include <string>
#include "kattistime.h"
#include "calendar.h"
#include "gregorian.h"

using ::testing::TestWithParam;
using ::testing::Values;

using lab2::Calendar;
using lab2::Gregorian;
using std::string;

TEST(Calendar, MoveEventMovesEventFromOriginDateToTargetDate) {
  const Gregorian from { 2014, 11, 7 };
  const Gregorian to   { 2014, 11, 8 };
  const string event = "foo";

  set_k_time(0);
  Calendar<Gregorian> cal;

  cal.add_event(event, from.day(), from.month(), from.year());

  ASSERT_EQ(1, cal.get_events().at(from).size());
  ASSERT_EQ(event, cal.get_events().at(from).front());
  ASSERT_THROW({
    cal.get_events().at(to);
  }, std::out_of_range);

  const bool success = cal.move_event(from, to, event);
  EXPECT_TRUE(success);

  EXPECT_EQ(0, cal.get_events().at(from).size());
  EXPECT_EQ(1, cal.get_events().at(to).size());
  EXPECT_EQ(event, cal.get_events().at(to).front());
}

TEST(Calendar, MoveEventReturnsFalseIfEventDoesNotExistAtOriginDate) {
  const Gregorian from { 2014, 11, 7 };
  const Gregorian to   { 2014, 11, 8 };
  const string event = "foo";

  set_k_time(0);
  Calendar<Gregorian> cal;

  ASSERT_THROW({
    cal.get_events().at(from);
  }, std::out_of_range);
  ASSERT_THROW({
    cal.get_events().at(to);
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

  ASSERT_EQ(1, cal.get_events().at(from).size());
  ASSERT_EQ(1, cal.get_events().at(to).size());
  ASSERT_EQ(event, cal.get_events().at(from).front());
  ASSERT_EQ(event, cal.get_events().at(to).front());

  const bool success = cal.move_event(from, to, event);
  EXPECT_FALSE(success);

  EXPECT_EQ(1, cal.get_events().at(from).size());
  EXPECT_EQ(1, cal.get_events().at(to).size());
  EXPECT_EQ(event, cal.get_events().at(from).front());
  EXPECT_EQ(event, cal.get_events().at(to).front());
}
