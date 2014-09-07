#include <sstream>
#include "hello.h"

std::string hello(std::string helloee, size_t times) {
  std::stringstream ss;

  ss << "Hello,";
  for(size_t i = 0; i < times; ++i) {
    ss << " " << helloee;
  }
  ss << "!";

  return ss.str();
}
