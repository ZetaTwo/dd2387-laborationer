#include "kth_cprog_template_container.hpp"

template<class T, size_t n>
class Hypercube : Vector<Hypercube<T, n-1> > {
public:
  Hypercube() : Vector<Hypercube<T, n-1> >() {};
  Hypercube(size_t s) : Vector<Hypercube<T, n-1> >(s, Hypercube<T, n-1>(s)) {};

  using Vector<Hypercube<T, n-1>>::operator[];
};

template<class T>
class Hypercube<T, 1> : Vector<T> {
public:
  Hypercube() : Vector<T>() {};
  Hypercube(size_t s) : Vector<T>(s) {};

  using Vector<T>::operator[];
};
