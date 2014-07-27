#include "kth_cprog_vektor.cpp"

template<class T, size_t n>
class Hypercube : public Vector<Hypercube<T, n-1> > {
public:
  Hypercube() : Vector<Hypercube<T, n-1> >() {};
  Hypercube(size_t s) : Vector<Hypercube<T, n-1> >(s, Hypercube<T, n-1>(s)) {};
};

template<class T>
class Hypercube<T, 1> : public Vector<T> {
public:
  Hypercube() : Vector<T>() {};
  Hypercube(size_t s) : Vector<T>(s) {};
};
