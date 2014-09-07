#include "hello.h"

void hello(std::ostream& out, const std::string& helloee, const size_t times) {
  out << "Hello,";
  for(size_t i = 0; i < times; ++i) {
    out << " " << helloee;
  }
  out << "!";
}
