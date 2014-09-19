#include <stdexcept>
#include <cmath>
#include <algorithm> //sort
#include "vector.h"

typedef unsigned int T;

Vector::Vector() : count(0), max_size(DEFAULT_SIZE), data(new T[max_size]) {
}

Vector::Vector(const Vector& other) : count(other.count), max_size(other.max_size), data(new T[max_size]) {
  for(size_t i = 0; i < count; ++i) {
    data[i] = other.data[i];
  }
}

Vector::Vector(const std::initializer_list<T>& list) : count(list.size()), max_size(1 << static_cast<int>(ceil(log2(count)))), data(new T[max_size]) {
  size_t i;
  typename std::initializer_list<T>::iterator item;
  for(i = 0, item = list.begin(); item != list.end(); ++i, ++item) {
    data[i] = *item;
  }
}

Vector::Vector(size_t size) : count(size), max_size(1 << static_cast<int>(ceil(log2(count)))), data(new T[max_size]) {
  for(size_t i = 0; i < count; ++i) {
    data[i] = T();
  }
}

Vector::Vector(size_t size, T element) : count(size), max_size(1 << static_cast<int>(ceil(log2(count)))), data(new T[max_size]) {
  for(size_t i = 0; i < count; ++i) {
    data[i] = element;
  }
}

Vector::~Vector() {
}

T& Vector::operator[](size_t index) {
  if(index < 0 || index >= count) {
    throw std::out_of_range("Index out of range");
  }
  return data[index];
}

const T Vector::operator[](size_t index) const {
  if(index < 0 || index >= count) {
    throw std::out_of_range("Index out of range");
  }

  return data[index];
}

Vector& Vector::operator=(const Vector& other) {
  if(&other == this) {
    return  *this;
  }

  if(other.count > max_size) {
    increase_memory(other.count, false);
  }

  count = other.size();
  for(size_t i = 0; i < other.count; ++i) {
    data[i] = other[i];
  }

  return *this;
}

Vector& Vector::operator=(const std::initializer_list<T>& list) {
  if(list.size() > max_size) {
    increase_memory(list.size(), false);
  }

  count = list.size();
  size_t i = 0;
  typename std::initializer_list<T>::iterator item = list.begin();
  while(item != list.end()) {
    data[i++] = *(item++);
  }

  return *this;
}


Vector& Vector::push_back(const T& element) {
  return insert(count, element);
}

Vector& Vector::insert(size_t index, const T& element) {
  if(index > count) {
    std::stringstream msg;
    msg << "Attempted to insert at index " << index << ", expected <= " << count;
    throw std::out_of_range(msg.str());
  }
  if(max_size < count + 1) {
    increase_memory(count + 1);
  }

  for(size_t i = count; i > index; ) {
    data[i] = data[--i];
  }

  data[index] = element;
  ++count;

  return *this;
}

Vector& Vector::erase(size_t index) {
  if(index >= count) {
    std::stringstream msg;
    msg << "Attempted to insert at index " << index << ", expected < " << count;
    throw std::out_of_range(msg.str());
  }
  for(size_t i = index; i < count; ++i) {
    data[i] = data[i+1];
  }
  --count;
  return *this;
}

Vector& Vector::clear() {
  count = 0;
  return *this;
}

Vector& Vector::sort(bool ascending) {
  T* begin = data.get();
  T* end = data.get() + count;
  if(ascending) {
    std::sort(begin, end);
  } else {
    std::sort(begin, end, [](const T& a, const T& b) { return b < a; });
  }
  return *this;
}

Vector& Vector::unique_sort(bool ascending) {
  sort(ascending);

  T* begin = data.get();
  T* end = data.get() + count;
  T* new_end = std::unique(begin, end);

  count = new_end - begin;
  return *this;
}

bool Vector::exists(const T& element) const {
  T* end = data.get() + count;
  return std::find(data.get(), end, element) != end;
}

size_t Vector::size() const {
  return count;
}

void Vector::increase_memory(int num_elements, bool copy) {
  size_t new_max_size = (1 << static_cast<int>(ceil(log2(num_elements))));
  if(new_max_size < max_size) {
    throw std::invalid_argument("Vector already large enough");
  }

  std::unique_ptr<T[]> new_data(new T[new_max_size]);

  if(copy) {
    for(size_t i = 0; i < count; i++) {
      new_data[i] = data[i];
    }
  }

  data = std::move(new_data);
  max_size = new_max_size;
}
