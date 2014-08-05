#include "kth_cprog_vektor.cpp"
#include <climits> // CHAR_BIT

template <>
class Vector<bool> {
  typedef unsigned int storage_type; static const unsigned int STORAGE_BLOCK_ALL_TRUE = -1;
  typedef unsigned char subindex_type;
  static const size_t STORAGE_BLOCK_SIZE = sizeof(storage_type) * CHAR_BIT;
  static const subindex_type MAX_SUBINDEX = STORAGE_BLOCK_SIZE - 1;

  class bool_proxy;

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
  bool_proxy operator[](size_t index);
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

  static const size_t DEFAULT_SIZE = STORAGE_BLOCK_SIZE;

  size_t count; //Actual number of elements in the vector
  size_t max_size; //Allocated memory for elements. Will be STORAGE_BLOCK_SIZE*2^n for some n
  std::unique_ptr<storage_type[]> data; //A pointer to the vector data (Note: 8*sizeof(unsigned int) elements per index)

  void increase_memory(size_t num_elements, bool copy = true); //Increases memory to fit at least num_elements number of elements
  size_t storage_size() const; // How many storage blocks are allocated
  const size_t initial_size(const size_t& minimumSize) const; // Return a suitable max_size >= minimumSize
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

    return *this;
  }
  operator const bool () const {
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

    return STORAGE_BLOCK_SIZE * (element - other.element) + (index - other.index);
  }
  bool operator==(const const_iterator& rhs) const { 
    return element == rhs.element && index == rhs.index;
  }
  bool operator!=(const const_iterator& rhs) const { 
    return !(*this == rhs);
  }
  bool_proxy operator[](size_t index) {
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

    return STORAGE_BLOCK_SIZE * (element - other.element) + (index - other.index);
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

//Member implementations
Vector<bool>::Vector() : count(0), max_size(DEFAULT_SIZE), data(new storage_type[storage_size()]) {
}

Vector<bool>::Vector(const Vector<bool>& other) : count(other.count), max_size(other.max_size), data(new storage_type[storage_size()]) {
  for(size_t i = 0; i <= storage_size(); ++i) {
    data[i] = other.data[i];
  }
}

Vector<bool>::Vector(const std::initializer_list<bool>& list) : count(list.size()), max_size(initial_size(count)), data(new storage_type[storage_size()]) {
  size_t listIndex;
  std::initializer_list<bool>::iterator item;

  size_t blockIndex = 0;
  size_t blockSubindex = 0;
  storage_type blockData = 0;

  for(listIndex = 0, item = list.begin(); item != list.end(); ++item, ++listIndex, ++blockSubindex) {
    if(*item) {
      blockData += (1 << blockSubindex);
    }

    if(blockSubindex == STORAGE_BLOCK_SIZE) {
      data[blockIndex++] = blockData;
      blockData = 0;
      blockSubindex = 0;
    }
  }

  if(blockData != 0) {
    data[blockIndex] = blockData;
  }
}

Vector<bool>::Vector(Vector<bool>&& other) {
}

Vector<bool>::Vector(size_t size) : count(size), max_size(initial_size(count)), data(new storage_type[storage_size()]) {
  for(size_t i = 0; i < storage_size(); ++i) {
    data[i] = 0;
  }
}

Vector<bool>::Vector(size_t size, bool element) : count(size), max_size(initial_size(count)), data(new storage_type[storage_size()]) {
  const storage_type value = element ? STORAGE_BLOCK_ALL_TRUE : 0;
  for(size_t i = 0; i < storage_size(); ++i) {
    data[i] = value;
  }
}

Vector<bool>::~Vector() {
}

Vector<bool>::bool_proxy Vector<bool>::operator[](size_t index) {
  if(index >= count) {
    std::stringstream msg;
    msg << "Index out of range: " << index << " (expected range 0 - " << (count-1) << ", inclusive)";
    throw std::out_of_range(msg.str());
  }
  return bool_proxy(data.get() + (index / STORAGE_BLOCK_SIZE), index % STORAGE_BLOCK_SIZE);
}

const bool Vector<bool>::operator[](size_t index) const {
  if(index >= count) {
    std::stringstream msg;
    msg << "Index out of range: " << index << " (expected range 0 - " << (count-1) << ", inclusive)";
    throw std::out_of_range(msg.str());
  }
  return (data[index / STORAGE_BLOCK_SIZE] & (1 << index)) != 0;
}

Vector<bool>& Vector<bool>::operator=(const Vector<bool>& other) {
  if(&other == this) {
    return *this;
  }

  if(other.count > max_size) {
    increase_memory(other.count, false);
  }

  count = other.size();
  for(size_t i = 0; i < other.storage_size(); ++i) {
    data[i] = other.data[i];
  }

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
  for(size_t i = 0; i <= size() / STORAGE_BLOCK_SIZE; i++) {
    result.data[i] = ~data[i];
  }

  return result;
}
Vector<bool> Vector<bool>::operator&(const Vector<bool>& other) const {
  if(size() != other.size()) {
    throw std::invalid_argument("Vectors must be of same size");
  }

  Vector<bool> result(count);
  for(size_t i = 0; i <= count / STORAGE_BLOCK_SIZE; i++) {
    result.data[i] = data[i] & other.data[i];
  }

  return result;
}
Vector<bool> Vector<bool>::operator|(const Vector<bool>& other) const {
  if(size() != other.size()) {
    throw std::invalid_argument("Vectors must be of same size");
  }

  Vector<bool> result(count);
  for(size_t i = 0; i <= count / STORAGE_BLOCK_SIZE; i++) {
    result.data[i] = data[i] | other.data[i];
  }

  return result;
}
Vector<bool> Vector<bool>::operator^(const Vector<bool>& other) const {
  if(size() != other.size()) {
    throw std::invalid_argument("Vectors must be of same size");
  }

  Vector<bool> result(count);
  for(size_t i = 0; i <= count / STORAGE_BLOCK_SIZE; i++) {
    result.data[i] = data[i] ^ other.data[i];
  }

  return result;
}

bool Vector<bool>::operator==(const Vector<bool>& other) const {
  if(size() != other.size()) {
    return false;
  }

  //Check all except last element
  for(size_t i = 0; i < count / STORAGE_BLOCK_SIZE; i++) {
    if(data[i] != other.data[i]) {
      return false;
    }
  }

  //Check last element
  if(((data[count / STORAGE_BLOCK_SIZE]) & (1 << count % MAX_SUBINDEX)) !=
    ((other.data[count / STORAGE_BLOCK_SIZE]) & (1 << count % MAX_SUBINDEX))) {
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
  count = 0;
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
  return count;
}

size_t Vector<bool>::weight1() const {
  size_t result = 0;

  for(size_t i = 0; i <= size() / STORAGE_BLOCK_SIZE; i++) {
    size_t count = data[i] - ((data[i] >> 1) & 033333333333) - ((data[i] >> 2) & 011111111111);
    result += ((count + (count >> 3)) & 030707070707) % 63;
  }

  return result;
}

size_t Vector<bool>::weight2() const {
  size_t result = 0;

  for(size_t i = 0; i <= size() / STORAGE_BLOCK_SIZE; i++) {
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

  for(size_t i = 0; i <= size() / STORAGE_BLOCK_SIZE; i++) {
    while(data[i] > 0) {         // until all bits are zero
      if((data[i] & (1 << (sizeof(storage_type)-1))) == (1 << (sizeof(storage_type)-1))) {   // check upper bit
        result++;
      }
      data[i] <<= 1;              // shift bits, removing upper bit
    }
  }

  return result;
}

void Vector<bool>::increase_memory(size_t num_elements, bool copy) { //Increases memory to fit at least num_elements number of elements
  size_t previous_storage_size = storage_size();

  size_t new_max_size = initial_size(num_elements);
  if(new_max_size < max_size) {
    throw std::invalid_argument("Vector already large enough");
  }

  max_size = new_max_size;
  std::unique_ptr<storage_type[]> new_data(new storage_type[storage_size()]);

  if(copy) {
    for(size_t i = 0; i < previous_storage_size; i++) {
      new_data[i] = data[i];
    }
  }

  data = std::move(new_data);
}

inline size_t Vector<bool>::storage_size() const {
  return max_size / STORAGE_BLOCK_SIZE;
}

inline const size_t Vector<bool>::initial_size(const size_t& minimumSize) const {
  return STORAGE_BLOCK_SIZE << static_cast<int>(ceil(log2(std::max(1.0, minimumSize/static_cast<double>(STORAGE_BLOCK_SIZE)))));
}


Vector<bool>::iterator Vector<bool>::begin() {
  return iterator(&data[0], 0);
}

Vector<bool>::iterator Vector<bool>::end() {
  return iterator(&data[count / STORAGE_BLOCK_SIZE], count % MAX_SUBINDEX);
}

Vector<bool>::const_iterator Vector<bool>::begin() const {
  return const_iterator(&data[0], 0);
}

Vector<bool>::const_iterator Vector<bool>::end() const {
  return const_iterator(&data[count / STORAGE_BLOCK_SIZE], count % MAX_SUBINDEX);
}

Vector<bool>::reverse_iterator Vector<bool>::rbegin() {
  return reverse_iterator(iterator(&data[count / STORAGE_BLOCK_SIZE], count % MAX_SUBINDEX));
}

Vector<bool>::reverse_iterator Vector<bool>::rend() {
  return reverse_iterator(iterator(&data[0], 0));
}

Vector<bool>::const_reverse_iterator Vector<bool>::rbegin() const {
  return const_reverse_iterator(const_iterator(&data[count / STORAGE_BLOCK_SIZE], count % MAX_SUBINDEX));
}

Vector<bool>::const_reverse_iterator Vector<bool>::rend() const {
  return const_reverse_iterator(const_iterator(&data[0], 0));
}

