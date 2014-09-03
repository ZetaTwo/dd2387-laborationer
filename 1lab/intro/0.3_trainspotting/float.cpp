#include<iostream>
using namespace std;

int main() {
  float y = 3.1415;

  if(y == 3.1415) {
    cout << y << " == 3.1415" << endl;
  } else {
    cout << y << " != 3.1415" << endl;
  }

  if(y == 3.1415f) {
    cout << y << " == 3.1415f" << endl;
  } else {
    cout << y << " != 3.1415f" << endl;
  }
}
