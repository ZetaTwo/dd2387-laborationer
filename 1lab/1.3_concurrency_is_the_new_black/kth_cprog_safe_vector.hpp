#pragma once

#include <kth_cprog_template_container.hpp>
#include <mutex>
#include <algorithm>

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

  LockValuePair& operator=(const T& other) {
    value = other;
    return *this;
  }

  bool operator==(const LockValuePair<T>& other) const {
    return value == other.value;
  }

  friend bool operator==(const T& value, const LockValuePair<T>& other) {
    return value == other.value;
  }

  operator T&() {
    return value;
  }

  operator const T&() const {
    return value;
  }
};

template<typename T>
class SafeVector : public Vector<LockValuePair<T> > {
  typedef LockValuePair<T> vector_datatype;

public:
  SafeVector() {};
  //SafeVector(const Vector<T>& other) : Vector(other) {};
  SafeVector(const std::initializer_list<T>& list);
  SafeVector(Vector<T>&& other) : Vector<vector_datatype>(other) {}; //Move
  explicit SafeVector(size_t size) : Vector<vector_datatype>(size) {};
  SafeVector(size_t size, const T& element) : Vector<vector_datatype>(size, element) {}

  void safeswap(size_t index1, size_t index2);
};

template<typename T>
void SafeVector<T>::safeswap(size_t index1, size_t index2) {
  if (index1 > index2) {
    std::swap(index1, index2);
  }

  std::lock_guard<std::mutex>
    index1_lock((*this)[index1].lock),
    index2_lock((*this)[index2].lock)
  ;

  std::swap((*this)[index1], (*this)[index2]);
};

template<typename T>
SafeVector<T>::SafeVector(const std::initializer_list<T>& list) : Vector<vector_datatype>(list.size()) {
  std::copy(list.begin(), list.end(), this->begin());
}

template<typename T>
class SuperSafeVector : public Vector < T > {
  typedef T vector_datatype;
  std::mutex lock;

public:
  SuperSafeVector() {};
  //SuperSafeVector(const Vector<T>& other) : Vector(other) {};
  SuperSafeVector(const std::initializer_list<T>& list) : Vector<vector_datatype>(list) {}
  SuperSafeVector(Vector<T>&& other) : Vector<vector_datatype>(other) {}; //Move
  explicit SuperSafeVector(size_t size) : Vector<vector_datatype>(size) {};
  SuperSafeVector(size_t size, const T& element) : Vector<vector_datatype>(size, element) {}

  void safeswap(size_t index1, size_t index2);
};

template<typename T>
void SuperSafeVector<T>::safeswap(size_t index1, size_t index2) {
  std::lock_guard<std::mutex> global_lock(lock);
  std::swap((*this)[index1], (*this)[index2]);
};
