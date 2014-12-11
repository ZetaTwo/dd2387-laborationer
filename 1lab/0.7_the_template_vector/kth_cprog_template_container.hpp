#pragma once

#include <memory> //unique_ptr<T>
#include <stdexcept>
#include <initializer_list>
#include <cmath>
#include <sstream>
#include <algorithm> //sort
#include <functional>

template<typename T> 
class Vector {
public:
  //Constructors & destructors
  Vector();
  Vector(const Vector<T>& other);
  Vector(const std::initializer_list<T>& list);
  Vector(Vector<T>&& other); //Move
  explicit Vector(size_t size);
  Vector(size_t size, const T& element);
  ~Vector();

  //Operators
  T& operator[](size_t index);
  const T operator[](size_t index) const;
  Vector<T>& operator=(const Vector<T>& other);
  Vector<T>& operator=(const std::initializer_list<T>& list);
  Vector<T>& operator=(Vector<T>&& other); //Move

  //Modify vector
  Vector<T>& push_back(const T& element);
  Vector<T>& insert(size_t index, const T& element);
  Vector<T>& erase(size_t index);
  Vector<T>& clear();
  Vector<T>& reset();
  Vector<T>& sort(bool ascending = true);
  Vector<T>& unique_sort(bool ascending = true);

  //Lookup in vector
  bool exists(const T& element) const;
  size_t size() const;
  size_t capacity() const;

  //Iterators
  class const_iterator : public std::iterator<std::random_access_iterator_tag, const T>
  {
    T* p;
  public:
    const_iterator() {}
    const_iterator(T* x) : p(x) {}
    const_iterator(const const_iterator& mit) : p(mit.p) {}
    const_iterator& operator++() { ++p; return *this; }
    const_iterator operator++(int) { const_iterator tmp(*this); operator++(); return tmp; }
    const_iterator& operator--() { --p; return *this; }
    const_iterator operator--(int) { const_iterator tmp(*this); operator--(); return tmp; }
    const_iterator operator-(size_t index) const { const_iterator tmp(*this); tmp.p -= index; return tmp; }
    size_t operator-(const const_iterator& other) const { return p - other.p; }
    bool operator==(const const_iterator& rhs) const { return p == rhs.p; }
    bool operator!=(const const_iterator& rhs) const { return p != rhs.p; }
    bool operator>(const const_iterator& rhs) const { return p > rhs.p; }
    bool operator<(const const_iterator& rhs) const { return p < rhs.p; }
    const T& operator[](size_t index) { return *(p + index); }
    const T& operator*() { return *p; }
    T const * operator->() const { return p; }
  };

  class iterator : public const_iterator
  {
    T* p;
  public:
    iterator() {}
    iterator(T* x) :p(x) {}
    iterator(const iterator& mit) : p(mit.p) {}
    iterator& operator++() { ++p; return *this; }
    iterator operator++(int) { iterator tmp(*this); operator++(); return tmp; }
    iterator& operator--() { --p; return *this; }
    iterator operator--(int) { iterator tmp(*this); operator--(); return tmp; }
    iterator operator-(size_t index) const { iterator tmp(*this); tmp.p -= index; return tmp; }
    size_t operator-(const iterator &other) const { return p - other.p; }
    bool operator==(const iterator& rhs) const { return p == rhs.p; }
    bool operator!=(const iterator& rhs) const { return p != rhs.p; }
    bool operator>(const iterator& rhs) const { return p > rhs.p; }
    bool operator<(const iterator& rhs) const { return p < rhs.p; }
    T& operator[](size_t index) { return *(p + index); }
    T& operator*() { return *p; }
    T* operator->() const { return p; }
  };

  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  iterator begin();
  iterator end();
  iterator find(T value);
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator find(T value) const;

  reverse_iterator rbegin();
  reverse_iterator rend();
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

private:

  static const size_t DEFAULT_SIZE = 16;

  size_t count; //Actual number of elements in the vector
  size_t max_size; //Allocated memory for elements. Will be 2^n for some n
  std::unique_ptr<T[]> data; //A pointer to the vector data
  std::allocator<T> allocator;

  void increase_memory(size_t num_elements, bool copy = true); //Increases memory to fit at least num_elements number of elements
  void release(std::unique_ptr<T[]>& data, size_t count, size_t max_size);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector);

//Member implementations
template<typename T>
Vector<T>::Vector() : count(0), max_size(DEFAULT_SIZE), data(allocator.allocate(max_size)) {
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other) : count(other.count), max_size(other.max_size), data(allocator.allocate(max_size)) {
  for(size_t i = 0; i < count; ++i) {
    allocator.construct(&data[i], other.data[i]);
  }
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T>& list) : count(list.size()), max_size(1 << static_cast<int>(ceil(log2(count)))), data(allocator.allocate(max_size)) {
  size_t i;
  typename std::initializer_list<T>::iterator item;
  for(i = 0, item = list.begin(); item != list.end(); ++i, ++item) {
    allocator.construct(&data[i], *item);
  }
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other) : data(std::move(other.data)), count(other.count), max_size(other.max_size) {
  /*for (size_t i = 0; i < count; ++i) {
    allocator.destroy(&other.data[i]);
  }*/

  other.count = 0;
  other.max_size = 0;
}

template<typename T>
Vector<T>::Vector(size_t size) : count(size), max_size(1 << static_cast<int>(ceil(log2(count)))), data(allocator.allocate(max_size)) {
  for(size_t i = 0; i < count; ++i) {
    allocator.construct(&data[i], T{});
  }
}

template<typename T>
Vector<T>::Vector(size_t size, const T& element) : count(size), max_size(1 << static_cast<int>(ceil(log2(count)))), data(allocator.allocate(max_size)) {
  for(size_t i = 0; i < count; ++i) {
    allocator.construct(&data[i], element);
  }
}

template<typename T>
Vector<T>::~Vector() {
  release(data, count, max_size);
  count = 0;
  max_size = 0;
}

template<typename T>
void Vector<T>::release(std::unique_ptr<T[]>& data, size_t count, size_t max_size) {
  for (size_t i = 0; i < count; ++i) {
    allocator.destroy(&data[i]);
  }
  allocator.deallocate(data.get(), max_size);
  data.release();
}

template<typename T>
T& Vector<T>::operator[](size_t index) {
  if(index >= count) {
    throw std::out_of_range("Index out of range");
  }
  return data[index];
}

template<typename T>
const T Vector<T>::operator[](size_t index) const {
  if(index >= count) {
    throw std::out_of_range("Index out of range");
  }

  return data[index];
}


template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
  if(&other == this) {
    return  *this;
  }

  if(other.count > max_size) {
    increase_memory(other.count, false);
  }

  count = other.size();
  for(size_t i = 0; i < other.count; ++i) {
    allocator.construct(&data[i], other[i]);
  }

  return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
  if (this != &other) {
    data = std::move(other.data);
    count = other.count;
    max_size = other.max_size;

    //Reset movee
    other.count = 0;
    other.max_size = 0;
  }

  return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const std::initializer_list<T>& list) {
  if(list.size() > max_size) {
    increase_memory(list.size(), false);
  }

  count = list.size();
  size_t i;
  typename std::initializer_list<T>::iterator item;
  for(i = 0, item = list.begin(); item != list.end(); ++i, ++item) {
    allocator.construct(&data[i], *item);
  }

  return *this;
}

template<typename T>
Vector<T>& Vector<T>::push_back(const T& element) {
  return insert(count, element);
}

template<typename T>
Vector<T>& Vector<T>::insert(size_t index, const T& element) {
  if(index > count) {
    std::stringstream msg;
    msg << "Attempted to insert at index " << index << ", expected <= " << count;
    throw std::out_of_range(msg.str());
  }
  if(max_size < count + 1) {
    increase_memory(count + 1);
  }

  size_t i;
  try {
    for (i = count; i > index; i--) {
      allocator.construct(&data[i], std::move_if_noexcept(data[i - 1]));
    }
  }
  catch (...) {
    count = i;
    throw;
  }

  if (index == count) {
    allocator.construct(&data[index], element);
  }
  else {
    data[index] = element;
  }
  ++count;

  return *this;
}

template<typename T>
Vector<T>& Vector<T>::erase(size_t index) {
  if(index >= count) {
    std::stringstream msg;
    msg << "Attempted to insert at index " << index << ", expected < " << count;
    throw std::out_of_range(msg.str());
  }

  size_t i;
  allocator.destroy(&data[index]);
  try {
    for (i = index; i < count - 1; i++) {
      data[i] = std::move_if_noexcept(data[i + 1]);
    }
  }
  catch (...) {
    count = i;
    throw;
  }
  
  --count;
  return *this;
}

template<typename T>
Vector<T>& Vector<T>::clear() {
  for (size_t i = 0; i < count; ++i) {
    allocator.destroy(&data[i]);
  }

  count = 0;
  return *this;
}

template<typename T>
Vector<T>& Vector<T>::reset() {
  for (size_t i = 0; i < count; i++) {
    data[i] = T{};
  }

  return *this;
}

template<typename T>
Vector<T>& Vector<T>::sort(bool ascending) {
  T* begin = data.get();
  T* end = data.get() + count;
  if(ascending) {
    std::sort(begin, end);
  } else {
    std::sort(begin, end, std::greater<T>());
  }
  return *this;
}

template<typename T>
Vector<T>& Vector<T>::unique_sort(bool ascending) {
  sort(ascending);

  T* begin = data.get();
  T* end = data.get() + count;
  T* new_end = std::unique(begin, end);

  count = new_end - begin;
  return *this;
}

template<typename T>
bool Vector<T>::exists(const T& element) const {
  T* end = data.get() + count;
  return std::find(data.get(), end, element) != end;
}

template<typename T>
size_t Vector<T>::size() const {
  return count;
}

template<typename T>
size_t Vector<T>::capacity() const {
  return max_size;
}

template<typename T>
void Vector<T>::increase_memory(size_t num_elements, bool copy) {
  size_t new_max_size = (1 << static_cast<int>(ceil(log2(num_elements))));
  if(new_max_size < max_size) {
    throw std::invalid_argument("Vector already large enough");
  }

  std::unique_ptr<T[]> new_data(allocator.allocate(new_max_size));

  if(copy) {
    for(size_t i = 0; i < count; i++) {
      allocator.construct(&new_data[i], std::move_if_noexcept(data[i]));
    }
  }

  release(data, count, max_size);
  data = std::move(new_data);
  max_size = new_max_size;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() {
  return iterator(&data[0]);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end() {
  return iterator(&data[count]);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::find(T value) {
  Vector<T>::iterator el = begin();
  for (; el != end(); el++) {
    if (*el == value) {
      return el;
    }
  }

  return el;
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() {
  return reverse_iterator(data.get() + count);
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend() {
  return reverse_iterator(data.get());
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
  return const_iterator(data.get());
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::end() const {
  return const_iterator(data.get() + count);
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::find(T value) const {
  Vector<T>::const_iterator el = begin();
  for (; el != end(); el++) {
    if (*el == value) {
      return el;
    }
  }

  return el;
}

template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const {
  return const_reverse_iterator(&data[count]);
}

template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rend() const {
  return const_reverse_iterator(&data[0]);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) {
  os << "[";
  if(vector.size() > 0) {
    os << vector[0];
    for(size_t i = 1; i < vector.size(); ++i) {
      os << ", " << vector[i];
    }
  }
  os << "]";
  return os;
}
