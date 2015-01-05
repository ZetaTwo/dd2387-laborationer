#pragma once

#include <kth_cprog_template_container.hpp>
#include <mutex>

//#define LOCK_GLOBAL

template<typename T>
struct LockValuePair {
  T value;
  std::mutex lock;

  LockValuePair() {}
  LockValuePair(const LockValuePair<T>& other) : value(other.value) {}
  LockValuePair(const T& other) : value(other) {}
  LockValuePair(const T&& other) : value(other) {}

  LockValuePair& operator=(const LockValuePair<T>& other) {
    if (this != &other) {
      value = other.value;
    }

    return *this;
  }

  bool operator==(const LockValuePair<T>& other) const {
    return value == other.value;
  }

  friend bool operator==(const T& value, const LockValuePair<T>& other) {
    return value == other.value;
  }

  operator T&() const {
    return value;
  }

  operator T() const {
    return value;
  }
};

template<typename T>
#ifdef LOCK_GLOBAL
class SafeVector : public Vector < T > {
  std::mutex lock;
#else
class SafeVector : public Vector<LockValuePair<T> > {
#endif

public:
  SafeVector() {};
  //SafeVector(const Vector<T>& other) : Vector(other) {};
  SafeVector(const std::initializer_list<T>& list);
  SafeVector(Vector<T>&& other) : Vector(other) {}; //Move
  explicit SafeVector(size_t size) : Vector(size) {};
  SafeVector(size_t size, const T& element);

  void safeswap(size_t index1, size_t index2) {
#ifdef LOCK_GLOBAL
    lock.lock();
    std::swap((*this)[index1], (*this)[index2]);
    lock.unlock();
#else
    if (index1 > index2) {
      std::swap(index1, index2);
    }
    (*this)[index1].lock.lock();
    (*this)[index2].lock.lock();
    std::swap((*this)[index1], (*this)[index2]);
    (*this)[index2].lock.unlock();
    (*this)[index1].lock.unlock();
#endif
  }
};

template<typename T>
SafeVector<T>::SafeVector(const std::initializer_list<T>& list) : Vector(list.size()) {
  size_t i;
  typename std::initializer_list<T>::iterator item;
  for (i = 0, item = list.begin(); item != list.end(); ++i, ++item) {
    (*this)[i].value = *item;
  }
}

template<typename T>
SafeVector<T>::SafeVector(size_t size, const T& element) : Vector(size) {
  for (size_t i = 0; i < count; ++i) {
    (*this)[i].value = element;
  }
}