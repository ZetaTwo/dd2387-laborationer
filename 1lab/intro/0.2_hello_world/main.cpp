#include<iostream>
#include<string>
#include<stdlib.h>
#include "hello.h"

int main(int argc, char** argv) {
  std::string helloee = "world";
  size_t times = 1;

  if(argc > 3) {
    std::cerr << "error: Too many arguments!" << std::endl;
    return 1;
  }
  if(argc > 1) {
    int i = atoi(argv[1]);
    if(i > 0) {
      times = i;
    } else {
      helloee = argv[1];

      if(argc > 2) {
        times = atoi(argv[2]);
        if(times <= 0) {
          std::cerr << "error: 2nd argument must be an integral greater than zero!" << std::endl;
          return 2;
        }
      }
    }
  }

  std::cout << hello(helloee, times) << std::endl;
}
