#include "kth_cprog_vektor.cpp"
#include <climits> // CHAR_BIT

template <>
class Vector<bool> {
  typedef unsigned int storage_type;
  typedef unsigned char subindex_type;
  static const size_t STORAGE_CELL_SIZE = sizeof(storage_type) * CHAR_BIT;
  static const subindex_type MAX_SUBINDEX = STORAGE_CELL_SIZE - 1;

public:
  //Constructors & destructors
  Vector();
  Vector(const Vector<bool>& other);
  Vector(const std::initializer_list<bool>& list);
  Vector(Vector<bool>&& other); //Move
  explicit Vector(size_t size);
  Vector(size_t size, bool element);
  ~Vector();

  //Operators
  bool& operator[](size_t index);
  const bool operator[](size_t index) const;
  Vector<bool>& operator=(const Vector<bool>& other);
  Vector<bool>& operator=(const std::initializer_list<bool>& list);
  Vector<bool>& operator=(Vector<bool>&& other); //Move

  Vector<bool> operator~() const;
  Vector<bool> operator&(const Vector<bool>& other) const;
  Vector<bool> operator|(const Vector<bool>& other) const;
  Vector<bool> operator^(const Vector<bool>& other) const;
  bool operator==(const Vector<bool>& other) const;
  bool operator!=(const Vector<bool>& other) const;

  //Modify vector
  Vector<bool>& push_back(const bool& element);
  Vector<bool>& insert(size_t index, const bool& element);
  Vector<bool>& erase(size_t index);
  Vector<bool>& clear();
  Vector<bool>& sort(bool ascending = true);
  Vector<bool>& unique_sort(bool ascending = true);

  //Lookup in vector
  bool exists(const bool& element) const;
  size_t size() const;

  size_t weight1() const;
  size_t weight2() const;
  size_t weight3() const;

  //Iterators
private:
  class bool_proxy;
public:
  class const_iterator;
  class iterator;

  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  reverse_iterator rbegin();
  reverse_iterator rend();
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

private:

  static const int DEFAULT_SIZE = 16;

  size_t count; //Actual number of elements in the vector
  size_t max_size; //Allocated memory for elements. Will be 2^n for some n
  std::unique_ptr<storage_type[]> data; //A pointer to the vector data (Note: 8*sizeof(unsigned int) elements per index)

  void increase_memory(int num_elements, bool copy = true); //Increases memory to fit at least num_elements number of elements
  inline size_t logicalToStorageSize(const size_t size) const; // How many storage cells (integers) are needed for this many bools
};

//Iterator classes
class Vector<bool>::bool_proxy {
private:
  storage_type* element;
  subindex_type index;
public:
  bool_proxy(storage_type* element, subindex_type index) : element(element), index(index) {}
  bool_proxy& operator=(const bool& value) {
    if(value) {
      *element |= 1 << index;
    } else {
      *element &= ~(1 << index);
    }
  }
  operator const bool & () const {
    return ((*element) & (1 << index)) != 0;
  }
};

class Vector<bool>::const_iterator : public std::iterator<std::random_access_iterator_tag, const bool> {
private:
  storage_type* element;
  subindex_type index;
  
public:
  const_iterator() {}
  const_iterator(storage_type* element, subindex_type index) : element(element), index(index) {}
  const_iterator(const const_iterator& mit) : element(mit.element), index(mit.index) {}
  const_iterator& operator++() {
    if(++index > MAX_SUBINDEX) {
      ++element;
      index = 0;
    }
    return *this;
  }
  const_iterator operator++(int) { const_iterator tmp(*this); operator++(); return tmp; }
  const_iterator& operator--() {
    if(index == 0) {
      --element;
      index = MAX_SUBINDEX;
    } else {
      --index;
    }
    return *this;
  }
  const_iterator operator--(int) { const_iterator tmp(*this); operator--(); return tmp; }
  const_iterator operator-(size_t offset) const {
    const_iterator tmp(*this);
    tmp.index -= (offset % MAX_SUBINDEX);
    tmp.element -= (offset / MAX_SUBINDEX);
    return tmp;
  }
  size_t operator-(const const_iterator& other) const {

    return STORAGE_CELL_SIZE * (element - other.element) + (index - other.index);
  }
  bool operator==(const const_iterator& rhs) const { 
    return element == rhs.element && index == rhs.index;
  }
  bool operator!=(const const_iterator& rhs) const { 
    return !(*this == rhs);
  }
  bool_proxy& operator[](size_t index) {
    return bool_proxy(element, index);
  }
  bool operator*() {
    return bool_proxy(element, index);
  }
};

class Vector<bool>::iterator : public Vector<bool>::const_iterator {
  storage_type const* element;
  subindex_type index;

public:
  iterator() {}
  iterator(storage_type* element, subindex_type index) : element(element), index(index) {}
  iterator(const iterator& mit) : element(mit.element), index(mit.index) {}
  iterator& operator++() {
    if(++index > MAX_SUBINDEX) {
      ++element;
      index = 0;
    }
    return *this;
  }
  iterator operator++(int) { iterator tmp(*this); operator++(); return tmp; }
  iterator& operator--() {
    if(index == 0) {
      --element;
      index = MAX_SUBINDEX;
    } else {
      --index;
    }
    return *this;
  }
  iterator operator--(int) { iterator tmp(*this); operator--(); return tmp; }
  iterator operator-(size_t offset) const {
    iterator tmp(*this);
    tmp.index -= (offset % MAX_SUBINDEX);
    tmp.element -= (offset / MAX_SUBINDEX);
    return tmp;
  }
  size_t operator-(const iterator& other) const {

    return STORAGE_CELL_SIZE * (element - other.element) + (index - other.index);
  }
  bool operator==(const iterator& rhs) const {
    return element == rhs.element && index == rhs.index;
  }
  bool operator!=(const iterator& rhs) const {
    return !(*this == rhs);
  }
  bool operator[](size_t index) {
    return ((*element) & (1 << index)) != 0;
  }
  bool operator*() {
    return ((*element) & (1 << index)) != 0;
  }
};

inline size_t roundUp(size_t size, size_t denominator) {
  return size % denominator ? size / denominator + 1 : size / denominator;
}

//Member implementations
Vector<bool>::Vector() : count(0), max_size(DEFAULT_SIZE), data(new storage_type[logicalToStorageSize(max_size)]) {
}

Vector<bool>::Vector(const Vector<bool>& other) {
}

Vector<bool>::Vector(const std::initializer_list<bool>& list) {
}

Vector<bool>::Vector(Vector<bool>&& other) {
}

Vector<bool>::Vector(size_t size) {
}

Vector<bool>::Vector(size_t size, bool element) {
}

Vector<bool>::~Vector() {
}

bool& Vector<bool>::operator[](size_t index) {
  bool a = true;
  return a;
}

const bool Vector<bool>::operator[](size_t index) const {
  return false;
}

Vector<bool>& Vector<bool>::operator=(const Vector<bool>& other) {
  return *this;
}

Vector<bool>& Vector<bool>::operator=(const std::initializer_list<bool>& list) {
  return *this;
}

Vector<bool>& Vector<bool>::operator=(Vector<bool>&& other) {
  return *this;
}

Vector<bool> Vector<bool>::operator~() const {
  Vector<bool> result(count);
  for(size_t i = 0; i <= size() / STORAGE_CELL_SIZE; i++) {
    result.data[i] = ~data[i];
  }

  return result;
}
Vector<bool> Vector<bool>::operator&(const Vector<bool>& other) const {
  if(size() != other.size()) {
    throw std::invalid_argument("Vectors must be of same size");
  }

  Vector<bool> result(count);
  for(size_t i = 0; i <= count / STORAGE_CELL_SIZE; i++) {
    result.data[i] = data[i] & other.data[i];
  }

  return result;
}
Vector<bool> Vector<bool>::operator|(const Vector<bool>& other) const {
  if(size() != other.size()) {
    throw std::invalid_argument("Vectors must be of same size");
  }

  Vector<bool> result(count);
  for(size_t i = 0; i <= count / STORAGE_CELL_SIZE; i++) {
    result.data[i] = data[i] | other.data[i];
  }

  return result;
}
Vector<bool> Vector<bool>::operator^(const Vector<bool>& other) const {
  if(size() != other.size()) {
    throw std::invalid_argument("Vectors must be of same size");
  }

  Vector<bool> result(count);
  for(size_t i = 0; i <= count / STORAGE_CELL_SIZE; i++) {
    result.data[i] = data[i] ^ other.data[i];
  }

  return result;
}

bool Vector<bool>::operator==(const Vector<bool>& other) const {
  if(size() != other.size()) {
    return false;
  }

  //Check all except last element
  for(size_t i = 0; i < count / STORAGE_CELL_SIZE; i++) {
    if(data[i] != other.data[i]) {
      return false;
    }
  }

  //Check last element
  if(((data[count / STORAGE_CELL_SIZE]) & (1 << count % MAX_SUBINDEX)) !=
    ((other.data[count / STORAGE_CELL_SIZE]) & (1 << count % MAX_SUBINDEX))) {
    return false;
  }

  return true;
}

bool Vector<bool>::operator!=(const Vector<bool>& other) const {
  return !(*this == other);
}

Vector<bool>& Vector<bool>::push_back(const bool& element) {
  return *this;
}

Vector<bool>& Vector<bool>::insert(size_t index, const bool& element) {
  return *this;
}

Vector<bool>& Vector<bool>::erase(size_t index) {
  return *this;
}

Vector<bool>& Vector<bool>::clear() {
  return *this;
}

Vector<bool>& Vector<bool>::sort(bool ascending) {
  return *this;
}

Vector<bool>& Vector<bool>::unique_sort(bool ascending) {
  return *this;
}

bool Vector<bool>::exists(const bool& element) const {
  return false;
}

size_t Vector<bool>::size() const {
  return 0;
}

size_t Vector<bool>::weight1() const {
  size_t result = 0;

  for(size_t i = 0; i <= size() / STORAGE_CELL_SIZE; i++) {
    size_t count = data[i] - ((data[i] >> 1) & 033333333333) - ((data[i] >> 2) & 011111111111);
    result += ((count + (count >> 3)) & 030707070707) % 63;
  }

  return result;
}

size_t Vector<bool>::weight2() const {
  size_t result = 0;

  for(size_t i = 0; i <= size() / STORAGE_CELL_SIZE; i++) {
    while(data[i] > 0) {         // until all bits are zero
      if((data[i] & 1) == 1) {   // check lower bit
        result++;
      }
      data[i] >>= 1;              // shift bits, removing lower bit
    }
  }

  return result;
}

size_t Vector<bool>::weight3() const {
  size_t result = 0;

  for(size_t i = 0; i <= size() / STORAGE_CELL_SIZE; i++) {
    while(data[i] > 0) {         // until all bits are zero
      if((data[i] & (1 << (sizeof(storage_type)-1))) == (1 << (sizeof(storage_type)-1))) {   // check upper bit
        result++;
      }
      data[i] <<= 1;              // shift bits, removing upper bit
    }
  }

  return result;
}

inline size_t Vector<bool>::logicalToStorageSize(const size_t logicalSize) const {
  return roundUp(logicalSize, STORAGE_CELL_SIZE);
}

Vector<bool>::iterator Vector<bool>::begin() {
  return iterator(&data[0], 0);
}

Vector<bool>::iterator Vector<bool>::end() {
  return iterator(&data[count / STORAGE_CELL_SIZE], count % MAX_SUBINDEX);
}

Vector<bool>::const_iterator Vector<bool>::begin() const {
  return const_iterator(&data[0], 0);
}

Vector<bool>::const_iterator Vector<bool>::end() const {
  return const_iterator(&data[count / STORAGE_CELL_SIZE], count % MAX_SUBINDEX);
}

Vector<bool>::reverse_iterator Vector<bool>::rbegin() {
  return reverse_iterator(iterator(&data[count / STORAGE_CELL_SIZE], count % MAX_SUBINDEX));
}

Vector<bool>::reverse_iterator Vector<bool>::rend() {
  return reverse_iterator(iterator(&data[0], 0));
}

Vector<bool>::const_reverse_iterator Vector<bool>::rbegin() const {
  return const_reverse_iterator(const_iterator(&data[count / STORAGE_CELL_SIZE], count % MAX_SUBINDEX));
}

Vector<bool>::const_reverse_iterator Vector<bool>::rend() const {
  return const_reverse_iterator(const_iterator(&data[0], 0));
}

