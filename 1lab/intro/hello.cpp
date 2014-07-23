#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;

int main(int argc, char** argv) {
  string addressee = "world";
  int helloTimes = 1;

  if(argc > 1) {
    int helloArgIndex;
    int i = atoi(argv[1]);
    if(i > 0) {
      helloTimes = i;
      helloArgIndex = 2;
    } else {
      helloArgIndex = 1;
    }

    if(argc > helloArgIndex) {
      addressee = argv[helloArgIndex];
    }
  }

  cout << "Hello";
  for(int i=0; i<helloTimes; ++i) {
    cout << " " << addressee;
  }
  cout << "!" << endl;
}
