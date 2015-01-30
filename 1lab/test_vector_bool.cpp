#include "kth_cprog_vektor_bool.h"

#include <algorithm>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector) {
  os << "[";
  if(vector.size() > 0) {
    os << vector[0];
    for(size_t i = 1; i < vector.size(); ++i) {
      os << ", " << vector[i];
    }
  }
  os << "] (std::vector)";
  return os;
}

int main() {
  std::vector<bool> stdv{1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, true, 0, false};
  Vector<bool> v(31);

  cout << v << endl;

  v[3] = true;

  cout << v << endl;

  Vector<bool> w;

  std::copy(v.begin(), v.end(), std::back_inserter(w));

  cout << std::distance(v.begin(), v.end()) << endl;
  cout << w << endl;

  Vector<bool>::const_iterator it = v.begin();

  std::advance(it, 2);

  v.clear();
  std::copy(stdv.begin(), stdv.end(), std::back_inserter(v));

  cout << stdv << endl;
  cout << v << endl;

  std::sort(stdv.begin(), stdv.end());
  std::sort(v.begin(), v.end());

  cout << stdv << endl;
  cout << v << endl;
}
