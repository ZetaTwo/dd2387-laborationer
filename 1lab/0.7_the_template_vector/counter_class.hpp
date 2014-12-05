#pragma once

struct CounterClass {
  CounterClass(int id) : id(id) { ++object_count; }
  CounterClass() : id(0)          { ++object_count; }
  CounterClass(CounterClass const& o) : id(o.id) { ++object_count; }
  ~CounterClass()          { --object_count; }

  static unsigned int object_count;
  int id;
};

unsigned int CounterClass::object_count = 0;