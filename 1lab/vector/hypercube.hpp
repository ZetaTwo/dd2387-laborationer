#include "kth_cprog_vektor.cpp"

template<class T, size_t n>
class Hypercube : public Vector<Hypercube<T, n-1> > {
public:
  Hypercube();
  Hypercube(size_t s);
};

template<class T>
class Hypercube<T, 1> : public Vector<T> {
public:
  Hypercube();
  Hypercube(size_t s);
};

template<class T, size_t n>
Hypercube<T, n>::Hypercube() : Vector<Hypercube<T, n-1> >() {};
template<class T, size_t n>
Hypercube<T, n>::Hypercube(size_t s) : Vector<Hypercube<T, n-1> >(s, Hypercube<T, n-1>(s)) {};

template<class T>
Hypercube<T, 1>::Hypercube() : Vector<T>() {};
template<class T>
Hypercube<T, 1>::Hypercube(size_t s) : Vector<T>(s) {};
