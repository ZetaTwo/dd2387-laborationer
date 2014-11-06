#pragma once

#include <memory> //unique_ptr<unsigned int>
#include <stdexcept>
#include <initializer_list>
#include <cmath>
#include <sstream>
#include <algorithm> //sort

class UIntVector {
public:
  //Constructors & destructors
  UIntVector();
  UIntVector(const UIntVector& other);
  UIntVector(const std::initializer_list<unsigned int>& list);
  UIntVector(UIntVector&& other); //Move
  explicit UIntVector(size_t size);
  UIntVector(size_t size, unsigned int element);
  ~UIntVector();

  //Operators
  unsigned int& operator[](size_t index);
  const unsigned int operator[](size_t index) const;
  UIntVector& operator=(const UIntVector& other);
  UIntVector& operator=(const std::initializer_list<unsigned int>& list);
  UIntVector& operator=(UIntVector&& other); //Move

  //Modify vector
  UIntVector& push_back(const unsigned int& element);
  UIntVector& insert(size_t index, const unsigned int& element);
  UIntVector& erase(size_t index);
  UIntVector& clear();
  UIntVector& reset();
  UIntVector& sort(bool ascending = true);
  UIntVector& unique_sort(bool ascending = true);

  //Lookup in vector
  bool exists(const unsigned int& element) const;
  size_t size() const;
  size_t capacity() const;

  //Iterators
  class const_iterator : public std::iterator<std::random_access_iterator_tag, const unsigned int>
  {
    unsigned int* p;
  public:
    const_iterator() {}
    const_iterator(unsigned int* x) : p(x) {}
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
    unsigned int& operator[](size_t index) { return *(p + index); }
    unsigned int& operator*() { return *p; }
    unsigned int const * operator->() const { return p; }
  };

  class iterator : public const_iterator
  {
    unsigned int* p;
  public:
    iterator() {}
    iterator(unsigned int* x) :p(x) {}
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
    unsigned int& operator[](size_t index) { return *(p + index); }
    unsigned int& operator*() { return *p; }
    unsigned int* operator->() const { return p; }
  };

  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  iterator begin();
  iterator end();
  iterator find(unsigned int value);
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator find(unsigned int value) const;

  reverse_iterator rbegin();
  reverse_iterator rend();
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

private:

  static const size_t DEFAULT_SIZE = 16;

  size_t count; //Actual number of elements in the vector
  size_t max_size; //Allocated memory for elements. Will be 2^n for some n
  std::unique_ptr<unsigned int[]> data; //A pointer to the vector data

  void increase_memory(size_t num_elements, bool copy = true); //Increases memory to fit at least num_elements number of elements
};


std::ostream& operator<<(std::ostream& os, const UIntVector& vector);

//Member implementations

UIntVector::UIntVector() : count(0), max_size(DEFAULT_SIZE), data(new unsigned int[max_size]) {
}


UIntVector::UIntVector(const UIntVector& other) : count(other.count), max_size(other.max_size), data(new unsigned int[max_size]) {
  for(size_t i = 0; i < count; ++i) {
    data[i] = other.data[i];
  }
}


UIntVector::UIntVector(const std::initializer_list<unsigned int>& list) : count(list.size()), max_size(1 << static_cast<int>(ceil(log2(count)))), data(new unsigned int[max_size]) {
  size_t i;
  std::initializer_list<unsigned int>::iterator item;
  for(i = 0, item = list.begin(); item != list.end(); ++i, ++item) {
    data[i] = *item;
  }
}


UIntVector::UIntVector(UIntVector&& other) : data(std::move(other.data)), count(other.count), max_size(other.max_size) {
  other.count = 0;
  other.max_size = 0;
}


UIntVector::UIntVector(size_t size) : count(size), max_size(1 << static_cast<int>(ceil(log2(count)))), data(new unsigned int[max_size]) {
  for(size_t i = 0; i < count; ++i) {
    data[i] = {};
  }
}


UIntVector::UIntVector(size_t size, unsigned int element) : count(size), max_size(1 << static_cast<int>(ceil(log2(count)))), data(new unsigned int[max_size]) {
  for(size_t i = 0; i < count; ++i) {
    data[i] = element;
  }
}


UIntVector::~UIntVector() {
  count = 0;
  max_size = 0;
}


unsigned int& UIntVector::operator[](size_t index) {
  if(index >= count) {
    throw std::out_of_range("Index out of range");
  }
  return data[index];
}


const unsigned int UIntVector::operator[](size_t index) const {
  if(index >= count) {
    throw std::out_of_range("Index out of range");
  }

  return data[index];
}



UIntVector& UIntVector::operator=(const UIntVector& other) {
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


UIntVector& UIntVector::operator=(UIntVector&& other) {
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


UIntVector& UIntVector::operator=(const std::initializer_list<unsigned int>& list) {
  if(list.size() > max_size) {
    increase_memory(list.size(), false);
  }

  count = list.size();
  size_t i;
  std::initializer_list<unsigned int>::iterator item;
  for(i = 0, item = list.begin(); item != list.end(); ++i, ++item) {
    data[i] = *item;
  }

  return *this;
}


UIntVector& UIntVector::push_back(const unsigned int& element) {
  return insert(count, element);
}


UIntVector& UIntVector::insert(size_t index, const unsigned int& element) {
  if(index > count) {
    std::stringstream msg;
    msg << "Attempted to insert at index " << index << ", expected <= " << count;
    throw std::out_of_range(msg.str());
  }
  if(max_size < count + 1) {
    increase_memory(count + 1);
  }

  for(size_t i = count; i > index; i--) {
    data[i] = data[i-1];
  }

  data[index] = element;
  ++count;

  return *this;
}


UIntVector& UIntVector::erase(size_t index) {
  if(index >= count) {
    std::stringstream msg;
    msg << "Attempted to insert at index " << index << ", expected < " << count;
    throw std::out_of_range(msg.str());
  }
  for(size_t i = index; i < count-1; i++ ) {
    data[i] = data[i+1];
  }
  --count;
  return *this;
}


UIntVector& UIntVector::clear() {
  count = 0;
  return *this;
}


UIntVector& UIntVector::reset() {
  for (size_t i = 0; i < count; i++) {
    data[i] = {};
  }

  return *this;
}


UIntVector& UIntVector::sort(bool ascending) {
  unsigned int* begin = data.get();
  unsigned int* end = data.get() + count;
  if(ascending) {
    std::sort(begin, end);
  } else {
    std::sort(begin, end, [](const unsigned int& a, const unsigned int& b) { return b < a; });
  }
  return *this;
}


UIntVector& UIntVector::unique_sort(bool ascending) {
  sort(ascending);

  unsigned int* begin = data.get();
  unsigned int* end = data.get() + count;
  unsigned int* new_end = std::unique(begin, end);

  count = new_end - begin;
  return *this;
}


bool UIntVector::exists(const unsigned int& element) const {
  unsigned int* end = data.get() + count;
  return std::find(data.get(), end, element) != end;
}


size_t UIntVector::size() const {
  return count;
}


size_t UIntVector::capacity() const {
  return max_size;
}


void UIntVector::increase_memory(size_t num_elements, bool copy) {
  size_t new_max_size = (1 << static_cast<int>(ceil(log2(num_elements))));
  if(new_max_size < max_size) {
    throw std::invalid_argument("Vector already large enough");
  }

  std::unique_ptr<unsigned int[]> new_data(new unsigned int[new_max_size]);

  if(copy) {
    for(size_t i = 0; i < count; i++) {
      new_data[i] = data[i];
    }
  }

  data = std::move(new_data);
  max_size = new_max_size;
}


UIntVector::iterator UIntVector::begin() {
  return iterator(&data[0]);
}


UIntVector::iterator UIntVector::end() {
  return iterator(&data[count]);
}


UIntVector::iterator UIntVector::find(unsigned int value) {
  UIntVector::iterator el = begin();
  for (; el != end(); el++) {
    if (*el == value) {
      return el;
    }
  }

  return el;
}


UIntVector::reverse_iterator UIntVector::rbegin() {
  return reverse_iterator(&data[count]);
}


UIntVector::reverse_iterator UIntVector::rend() {
  return reverse_iterator(&data[0]);
}


UIntVector::const_iterator UIntVector::begin() const {
  return const_iterator(&data[0]);
}


UIntVector::const_iterator UIntVector::end() const {
  return const_iterator(&data[count]);
}


UIntVector::const_iterator UIntVector::find(unsigned int value) const {
  UIntVector::const_iterator el = begin();
  for (; el != end(); el++) {
    if (*el == value) {
      return el;
    }
  }

  return el;
}


UIntVector::const_reverse_iterator UIntVector::rbegin() const {
  return const_reverse_iterator(&data[count]);
}


UIntVector::const_reverse_iterator UIntVector::rend() const {
  return const_reverse_iterator(&data[0]);
}


std::ostream& operator<<(std::ostream& os, const UIntVector& vector) {
  os << "[";
  if(vector.size() > 0) {
    os << vector[0];
    for(auto item = ++vector.begin(); item != vector.end(); ++item) {
      os << ", " << *item;
    }
  }
  os << "]";
  return os;
}
