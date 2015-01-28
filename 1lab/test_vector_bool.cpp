#include "kth_cprog_vektor_bool.h"

#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;

int main() {
  Vector<bool> v(15);

  v[6] = true;
  v[7] = true;

  std::sort(v.begin(), v.end());
  cout << v << endl;
}
