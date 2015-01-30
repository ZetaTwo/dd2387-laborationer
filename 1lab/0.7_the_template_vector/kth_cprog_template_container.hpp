#pragma once

#include <memory> //unique_ptr<T>
#include <stdexcept>
#include <initializer_list>
#include <cmath>
#include <sstream>
#include <algorithm> //sort
#include <functional>

#define EXCEPTION_SAFE

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

  typedef const T* const_iterator;
  typedef T* iterator;

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

  typedef T value_type;

private:

  static const size_t DEFAULT_SIZE = 16;

  size_t count; //Actual number of elements in the vector
  size_t max_size; //Allocated memory for elements. Will be 2^n for some n

  static void release(T* del, std::allocator<T>& allocator, size_t count, size_t max_size);
  typedef std::unique_ptr<T[], std::function<void(T*)>> data_ptr;

  std::allocator<T> allocator;
  data_ptr data; //A pointer to the vector data
 
  static void increase_memory(Vector<T>& vector, size_t num_elements, bool copy = true); //Increases memory to fit at least num_elements number of elements
  //static void release(Vector<T>& vector, data_ptr& data, size_t count, size_t max_size);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector);

//Member implementations
template<typename T>
Vector<T>::Vector() : count(0), max_size(DEFAULT_SIZE), data(allocator.allocate(max_size), std::function<void(T*)>([&](T* d) { release(d, allocator, count, max_size); })) {
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other) : count(other.count), max_size(other.max_size), data(allocator.allocate(max_size), std::function<void(T*)>([&](T* d) { release(d, allocator, count, max_size); })) {
  for(size_t i = 0; i < count; ++i) {
    allocator.construct(&data[i], other.data[i]);
  }
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T>& list) : count(list.size()), max_size(1 << static_cast<int>(ceil(log2(count)))), data(allocator.allocate(max_size), std::function<void(T*)>([&](T* d) { release(d, allocator, count, max_size); })) {
  size_t i;
  typename std::initializer_list<T>::iterator item;
  for(i = 0, item = list.begin(); item != list.end(); ++i, ++item) {
    allocator.construct(&data[i], *item);
  }
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other) : data(std::move(other.data)), count(other.count), max_size(other.max_size) {
  //TODO: Is this really the best way?
  data = data_ptr(data.release(), std::function<void(T*)>([&](T* d) { release(d, allocator, count, max_size); }));

  other.count = 0;
  other.max_size = 0;
}

template<typename T>
Vector<T>::Vector(size_t size) : count(size), max_size(1 << static_cast<int>(ceil(log2(count)))), data(allocator.allocate(max_size), std::function<void(T*)>([&](T* d) { release(d, allocator, count, max_size); })) {
  for(size_t i = 0; i < count; ++i) {
    allocator.construct(&data[i], T{});
  }
}

template<typename T>
Vector<T>::Vector(size_t size, const T& element) : count(size), max_size(1 << static_cast<int>(ceil(log2(count)))), data(allocator.allocate(max_size), std::function<void(T*)>([&](T* d) { release(d, allocator, count, max_size); })) {
  for(size_t i = 0; i < count; ++i) {
    allocator.construct(&data[i], element);
  }
}

template<typename T>
Vector<T>::~Vector() {
}

template<typename T>
void Vector<T>::release(T* data, std::allocator<T>& allocator, size_t count, size_t max_size) {
  for (size_t i = 0; i < count; ++i) {
    allocator.destroy(&data[i]);
  }
  allocator.deallocate(data, max_size);
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

#ifdef EXCEPTION_SAFE
  try {
    Vector<T> copy(other);
    std::swap(*this, copy);
  }
  catch(...) {
    throw;
  }
#else

  //Make sure we have enough room
  if(other.count > max_size) {
    increase_memory(*this, other.count, false);
  }
  else {
    clear();
  }

  //Create new copies
  count = other.size();
  for (size_t i = 0; i < count; ++i) {
    allocator.construct(&data[i], other[i]);
  }
#endif

  return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
  if (this == &other) {
    return *this;
  }

  //TODO: Is this really the best way?
  data = std::move(other.data);
  data = data_ptr(data.release(), std::function<void(T*)>([&](T* d) { release(d, allocator, count, max_size); }));

  count = other.count;
  max_size = other.max_size;

  //Reset movee
  other.count = 0;
  other.max_size = 0;

  return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const std::initializer_list<T>& list) {

#ifdef EXCEPTION_SAFE
  try {
    Vector<T> copy(list);
    std::swap(*this, copy);
  }
  catch (...) {
    throw;
  }
#else

  //Make sure we have enough room
  if(list.size() > max_size) {
    increase_memory(*this, list.size(), false);
  }
  else {
    clear();
  }

  //Construct new copies
  count = list.size();
  size_t i;
  typename std::initializer_list<T>::iterator item;
  for(i = 0, item = list.begin(); item != list.end(); ++i, ++item) {
    allocator.construct(&data[i], *item);
  }

#endif

  return *this;
}

template<typename T>
Vector<T>& Vector<T>::push_back(const T& element) {
  return insert(count, element);
}

template<typename T>
Vector<T>& Vector<T>::insert(size_t index, const T& element) {

#ifdef EXCEPTION_SAFE
  try {
    Vector<T> copy(*this);
    Vector<T>& that = copy;
#else
  Vector<T>& that = *this;
#endif

  if (index > that.count) {
    std::stringstream msg;
    msg << "Attempted to insert at index " << index << ", expected <= " << that.count;
    throw std::out_of_range(msg.str());
  }
  if (that.max_size < that.count + 1) {
    increase_memory(that, that.count + 1);
  }

  that.allocator.construct(&that.data[that.count]);

  size_t i;
  try {
    for (i = that.count; i > index; i--) {
      that.data[i] = std::move_if_noexcept(that.data[i - 1]);
    }
  }
  catch (...) {
    that.count = i;
    throw;
  }

  that.data[index] = element;
  ++that.count;

#ifdef EXCEPTION_SAFE
  std::swap(*this, copy);
  }
catch (...) {
  throw;
}
#endif

  return *this;
}

template<typename T>
Vector<T>& Vector<T>::erase(size_t index) {


#ifdef EXCEPTION_SAFE
  try {
    Vector<T> copy(*this);
    Vector<T>& that = copy;
#else
  Vector<T>& that = *this;
#endif

  if (index >= that.count) {
    std::stringstream msg;
    msg << "Attempted to insert at index " << index << ", expected < " << that.count;
    throw std::out_of_range(msg.str());
  }

  size_t i;
  that.allocator.destroy(&that.data[index]);
  try {
    for (i = index; i < that.count - 1; i++) {
      that.data[i] = std::move_if_noexcept(that.data[i + 1]);
    }
  }
  catch (...) {
    that.count = i;
    throw;
  }
  
  --that.count;


#ifdef EXCEPTION_SAFE
  std::swap(*this, copy);
  }
catch (...) {
  throw;
}
#endif

  return *this;
}

template<typename T>
Vector<T>& Vector<T>::clear() {

#ifdef EXCEPTION_SAFE
  try {
    Vector<T> copy(*this);
    Vector<T>& that = copy;
#else
  Vector<T>& that = *this;
#endif

  for (size_t i = 0; i < that.count; ++i) {
    that.allocator.destroy(&that.data[i]);
  }
  that.count = 0;

#ifdef EXCEPTION_SAFE
  std::swap(*this, copy);
  }
catch (...) {
  throw;
}
#endif

  return *this;
}

template<typename T>
Vector<T>& Vector<T>::reset() {


#ifdef EXCEPTION_SAFE
  try {
    Vector<T> copy(*this);
    Vector<T>& that = copy;
#else
  Vector<T>& that = *this;
#endif

  for (size_t i = 0; i < that.count; i++) {
    that.data[i] = T{};
  }

#ifdef EXCEPTION_SAFE
  std::swap(*this, copy);
  }
catch (...) {
  throw;
}
#endif

  return *this;
}

template<typename T>
Vector<T>& Vector<T>::sort(bool ascending) {

#ifdef EXCEPTION_SAFE
  try {
    Vector<T> copy(*this);
    Vector<T>& that = copy;
#else
  Vector<T>& that = *this;
#endif

  T* begin = that.data.get();
  T* end = that.data.get() + that.count;
  if(ascending) {
    std::sort(begin, end);
  } else {
    std::sort(begin, end, std::greater<T>());
  }


#ifdef EXCEPTION_SAFE
  std::swap(*this, copy);
  }
catch (...) {
  throw;
}
#endif

  return *this;
}

template<typename T>
Vector<T>& Vector<T>::unique_sort(bool ascending) {

#ifdef EXCEPTION_SAFE
  try {
    Vector<T> copy(*this);
    Vector<T>& that = copy;
#else
  Vector<T>& that = *this;
#endif

  T* begin = that.data.get();
  T* end = that.data.get() + that.count;
  if (ascending) {
    std::sort(begin, end);
  }
  else {
    std::sort(begin, end, std::greater<T>());
  }
  T* new_end = std::unique(begin, end);

  that.count = new_end - begin;

#ifdef EXCEPTION_SAFE
  std::swap(*this, copy);
  }
catch (...) {
  throw;
}
#endif

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
void Vector<T>::increase_memory(Vector<T>& vector, size_t num_elements, bool copy) {
  size_t new_max_size = (1 << static_cast<int>(ceil(log2(num_elements))));
  if (new_max_size < vector.max_size) {
    throw std::invalid_argument("Vector already large enough");
  }

  size_t copied = 0;
  data_ptr new_data(vector.allocator.allocate(new_max_size), std::function<void(T*)>([&](T* d) { vector.release(d, vector.allocator, copied, vector.max_size); }));

  if(copy) {
    for (; copied < vector.count; copied++) {
      vector.allocator.construct(&new_data[copied], std::move_if_noexcept(vector.data[copied]));
    }
  }

  //TODO: Is this really the best way?
  vector.data = data_ptr(new_data.release(), std::function<void(T*)>([&](T* d) { vector.release(d, vector.allocator, vector.count, vector.max_size); }));

  vector.max_size = new_max_size;
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
