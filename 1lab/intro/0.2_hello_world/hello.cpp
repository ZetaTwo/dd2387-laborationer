#include "hello.h"

void hello(std::ostream& out, const std::string& helloee, const int times) {
  out << "Hello,";
  for(int i = 0; i < times; ++i) {
    out << " " << helloee;
  }
  out << "!";
}
