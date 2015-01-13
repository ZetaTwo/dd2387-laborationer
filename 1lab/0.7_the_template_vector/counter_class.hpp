#pragma once

struct CounterClass {
  CounterClass(int id) : id(id) { inc(); }
  CounterClass() : id(0) { inc(); }
  CounterClass(CounterClass const& o) : id(o.id) { inc(); }
  ~CounterClass()          { dec(); }

  operator int() const {
    return id;
  }

  static void inc() {
    ++object_count;
  }
  static void dec() {
    --object_count;
  }

  static unsigned int object_count;
  int id;
};

unsigned int CounterClass::object_count = 0;