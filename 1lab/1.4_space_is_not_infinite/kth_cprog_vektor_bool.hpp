#include "kth_cprog_template_container.hpp"
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

  size_t weight() const;
  size_t weight1() const;

  //Iterators
public:
  class const_iterator;
  class iterator;

  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  iterator begin();
  iterator end();
  iterator find(bool value);
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator find(bool value) const;

  reverse_iterator rbegin() ;
  reverse_iterator rend();
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

  // Type conversions
  operator unsigned int() const;

private:

  static const size_t DEFAULT_SIZE = STORAGE_BLOCK_SIZE;

  size_t count; //Actual number of elements in the vector
  size_t max_size; //Allocated memory for elements. Will be STORAGE_BLOCK_SIZE*2^n for some n
  std::unique_ptr<storage_type[]> data; //A pointer to the vector data (Note: 8*sizeof(unsigned int) elements per index)

  void increase_memory(size_t num_elements, bool copy = true); //Increases memory to fit at least num_elements number of elements
  size_t storage_size() const; // How many storage blocks are allocated
  size_t initial_size(const size_t& minimumSize) const; // Return a suitable max_size >= minimumSize
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

  for(listIndex = 0, item = list.begin(); item != list.end(); ++item, ++listIndex, blockSubindex = (blockSubindex + 1) % STORAGE_BLOCK_SIZE) {
    if(*item) {
      blockData |= (1 << blockSubindex);
    }

    if(blockSubindex == MAX_SUBINDEX) {
      data[blockIndex++] = blockData;
      blockData = 0;
    }
  }

  if(blockData != 0) {
    data[blockIndex] = blockData;
  }
}

Vector<bool>::Vector(Vector<bool>&& other) : count(other.count), max_size(other.max_size), data(std::move(other.data)) {
  other.count = 0;
  other.max_size = 0;
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
    msg << "Index out of range: " << index << ", expected range [0 - " << count << ")";
    throw std::out_of_range(msg.str());
  }
  return bool_proxy(data.get() + (index / STORAGE_BLOCK_SIZE), index % STORAGE_BLOCK_SIZE);
}

const bool Vector<bool>::operator[](size_t index) const {
  if(index >= count) {
    std::stringstream msg;
    msg << "Index out of range: " << index << ", expected range [0 - " << count << ")";
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
  if(list.size() > max_size) {
    increase_memory(list.size(), false);
  }

  count = list.size();

  size_t listIndex;
  std::initializer_list<bool>::iterator item;

  size_t blockIndex = 0;
  size_t blockSubindex = 0;
  storage_type blockData = 0;

  for(listIndex = 0, item = list.begin(); item != list.end(); ++item, ++listIndex, ++blockSubindex) {
    if(*item) {
      blockData |= (1 << blockSubindex);
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

  return *this;
}

Vector<bool>& Vector<bool>::operator=(Vector<bool>&& other) {
  if (this != &other) {
    count = other.count;
    max_size = other.max_size;
    data = std::move(other.data);

    //Reset movee
    other.count = 0;
    other.max_size = 0;
  }

  return *this;
}

Vector<bool> Vector<bool>::operator~() const {
  Vector<bool> result(count);
  for(size_t i = 0; i < storage_size(); i++) {
    result.data[i] = ~data[i];
  }

  return result;
}
Vector<bool> Vector<bool>::operator&(const Vector<bool>& other) const {
  if(size() != other.size()) {
    throw std::invalid_argument("Vectors must be of same size");
  }

  Vector<bool> result(count);

  for (size_t i = 0; i < storage_size(); i++) {
    result.data[i] = data[i] & other.data[i];
  }

  return result;
}
Vector<bool> Vector<bool>::operator|(const Vector<bool>& other) const {
  if(size() != other.size()) {
    throw std::invalid_argument("Vectors must be of same size");
  }

  Vector<bool> result(count);

  for (size_t i = 0; i < storage_size(); i++) {
    result.data[i] = data[i] | other.data[i];
  }

  return result;
}
Vector<bool> Vector<bool>::operator^(const Vector<bool>& other) const {
  if(size() != other.size()) {
    throw std::invalid_argument("Vectors must be of same size");
  }

  Vector<bool> result(count);

  for (size_t i = 0; i < storage_size(); i++) {
    result.data[i] = data[i] ^ other.data[i];
  }

  return result;
}

bool Vector<bool>::operator==(const Vector<bool>& other) const {
  if(size() != other.size()) {
    return false;
  }

  if(size() == 0 || storage_size() == 0) {
    return true;
  }

  const size_t last_logical_block_index = (size()-1) / STORAGE_BLOCK_SIZE;

  for(size_t i = 0; i < last_logical_block_index; i++) {
    if(data[i] != other.data[i]) {
      return false;
    }
  }

  const size_t block_logical_end = size() % STORAGE_BLOCK_SIZE;

  storage_type last_block;
  storage_type other_last_block;

  if(block_logical_end == 0) {
    last_block = data[last_logical_block_index];
    other_last_block = other.data[last_logical_block_index];
  } else {
    const size_t block_size_mask = 1 << block_logical_end;
    last_block = data[last_logical_block_index] % block_size_mask;
    other_last_block = other.data[last_logical_block_index] % block_size_mask;
  }

  if(last_block != other_last_block) {
    return false;
  }

  return true;
}

bool Vector<bool>::operator!=(const Vector<bool>& other) const {
  return !(*this == other);
}

Vector<bool>& Vector<bool>::push_back(const bool& element) {
  return insert(count, element);
}

Vector<bool>& Vector<bool>::insert(const size_t index, const bool& element) {
  if(index > count) {
    std::stringstream msg;
    msg << "Attempted to insert at index " << index << ", expected <= " << count;
    throw std::out_of_range(msg.str());
  }
  if(max_size < count + 1) {
    increase_memory(count + 1);
  }

  const size_t insert_storage_index = index / STORAGE_BLOCK_SIZE;
  const size_t insert_subindex = index % STORAGE_BLOCK_SIZE;

  //TODO: <TrasigKod>
  size_t storage_index = storage_size() - 1;
  if(count % STORAGE_BLOCK_SIZE == 0) {
    data[storage_index] = 0;
  }
  for( ; storage_index > insert_storage_index; --storage_index) {
    data[storage_index] = (data[storage_index] << 1) | (data[storage_index-1] >> MAX_SUBINDEX);
  }

  const storage_type lowerBits = insert_subindex == 0 ? 0 : data[storage_index] % (1 << insert_subindex);
  const storage_type middleBit = (element ? (1 << insert_subindex) : 0);
  const storage_type upperBits = insert_subindex == MAX_SUBINDEX ? 0 : (data[storage_index] >> insert_subindex) << (insert_subindex + 1);
  data[storage_index] = lowerBits | middleBit | upperBits;
  //TODO: </TrasigKod>

  ++count;

  return *this;
}

Vector<bool>& Vector<bool>::erase(const size_t index) {
  if(index >= count) {
    std::stringstream msg;
    msg << "Attempted to erase index " << index << ", expected < " << count;
    throw std::out_of_range(msg.str());
  }

  const size_t erase_storage_index = index / STORAGE_BLOCK_SIZE;
  const size_t erase_subindex = index % STORAGE_BLOCK_SIZE;

  const storage_type lowerBits = erase_subindex == 0 ? 0 : data[erase_storage_index] % (1 << erase_subindex);
  const storage_type upperBits = erase_storage_index == storage_size() ? 0 : (data[erase_storage_index] >> (erase_subindex + 1)) << erase_subindex;
  data[erase_storage_index] = lowerBits | upperBits;
  if(erase_storage_index < storage_size()) {
    data[erase_storage_index] |= (data[erase_storage_index+1] & 1) << MAX_SUBINDEX;
  }

  for(size_t storage_index = erase_storage_index+1; storage_index < storage_size(); ++storage_index) {
    data[storage_index] >>= 1;
    if(storage_index + 1 < storage_size()) {
      data[storage_index] |= (data[storage_index+1] & 1) << MAX_SUBINDEX;
    }
  }

  --count;

  return *this;
}

Vector<bool>& Vector<bool>::clear() {
  count = 0;
  return *this;
}

Vector<bool>& Vector<bool>::sort(const bool ascending) {
  const storage_type front_block = ascending ? 0 : STORAGE_BLOCK_ALL_TRUE;
  const storage_type rear_block = ascending ? STORAGE_BLOCK_ALL_TRUE : 0;
  const size_t num_front = ascending ? count - weight() : weight();
  const size_t flip_block_index = num_front / STORAGE_BLOCK_SIZE;

  for(size_t i = 0; i < flip_block_index; ++i) {
    data[i] = front_block;
  }
  for(size_t i = flip_block_index; i < count / STORAGE_BLOCK_SIZE + (count % STORAGE_BLOCK_SIZE == 0 ? 0 : 1); ++i) {
    data[i] = rear_block;
  }

  data[flip_block_index] <<= num_front % STORAGE_BLOCK_SIZE;
  if(!ascending) {
    data[flip_block_index] |= STORAGE_BLOCK_ALL_TRUE % (1 << (num_front % STORAGE_BLOCK_SIZE));
  }

  return *this;
}

Vector<bool>& Vector<bool>::unique_sort(const bool ascending) {
  const size_t w = weight();
  const bool hasFalse = w < count;
  const bool hasTrue = w > 0;
  count = hasFalse + hasTrue;
  data[0] = ((hasFalse << static_cast<unsigned>(!ascending)) | (hasTrue << static_cast<unsigned>(ascending))) & (1 << static_cast<unsigned>(ascending));
  return *this;
}

bool Vector<bool>::exists(const bool& element) const {
  for(size_t i = 0; i < count / STORAGE_BLOCK_SIZE; ++i) {
    if((element ? data[i] : ~data[i]) != 0) {
      return true;
    }
  }
  const storage_type d = data[count / STORAGE_BLOCK_SIZE];
  if((element ? d : ~d) % (1 << count % STORAGE_BLOCK_SIZE) != 0) {
    return true;
  }
  return false;
}

size_t Vector<bool>::size() const {
  return count;
}

size_t Vector<bool>::weight() const {
  return weight1();
}

size_t Vector<bool>::weight1() const {
  size_t result = 0;

  if (size() % STORAGE_BLOCK_SIZE != 0) {
    data[size() / STORAGE_BLOCK_SIZE] %= 1 << (size() % STORAGE_BLOCK_SIZE);
  }
  const size_t max_index = (size() / STORAGE_BLOCK_SIZE) - ((size() > 0 && size() % STORAGE_BLOCK_SIZE == 0) ? 1 : 0);
  for (size_t i = 0; i <= max_index; i++) {
    size_t count = data[i] - ((data[i] >> 1) & 033333333333) - ((data[i] >> 2) & 011111111111);
    result += ((count + (count >> 3)) & 030707070707) % 63;
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

inline size_t Vector<bool>::initial_size(const size_t& minimumSize) const {
  return STORAGE_BLOCK_SIZE << static_cast<int>(ceil(log2(std::max(1.0, minimumSize/static_cast<double>(STORAGE_BLOCK_SIZE)))));
}


Vector<bool>::iterator Vector<bool>::begin() {
  return iterator(&data[0], 0);
}

Vector<bool>::iterator Vector<bool>::end() {
  return iterator(&data[count / STORAGE_BLOCK_SIZE], count % MAX_SUBINDEX);
}

Vector<bool>::iterator Vector<bool>::find(bool value) {
  Vector<bool>::iterator el = begin();
  for (; el != end(); el++) {
    if (*el == value) {
      return el;
    }
  }

  return el;
}

Vector<bool>::const_iterator Vector<bool>::begin() const {
  return const_iterator(&data[0], 0);
}

Vector<bool>::const_iterator Vector<bool>::end() const {
  return const_iterator(&data[count / STORAGE_BLOCK_SIZE], count % MAX_SUBINDEX);
}

Vector<bool>::const_iterator Vector<bool>::find(bool value) const {
  Vector<bool>::const_iterator el = begin();
  for (; el != end(); el++) {
    if (*el == value) {
      return el;
    }
  }

  return el;
}

Vector<bool>::reverse_iterator Vector<bool>::rbegin() {
  if (count == 0) {
    return rend();
  }

  return reverse_iterator(end());
  //return reverse_iterator(iterator(&data[count / STORAGE_BLOCK_SIZE], (count - 1) % MAX_SUBINDEX));
}

Vector<bool>::reverse_iterator Vector<bool>::rend() {
  return reverse_iterator(begin());
  //return reverse_iterator(iterator(&data[0] - 1, STORAGE_BLOCK_SIZE-1));
}

Vector<bool>::const_reverse_iterator Vector<bool>::rbegin() const {
  return const_reverse_iterator(const_iterator(&data[count / STORAGE_BLOCK_SIZE], count % MAX_SUBINDEX));
}

Vector<bool>::const_reverse_iterator Vector<bool>::rend() const {
  return const_reverse_iterator(const_iterator(&data[0], 0));
}

Vector<bool>::operator unsigned int() const {
  const size_t UNSIGNED_INT_SIZE = sizeof(unsigned int) * CHAR_BIT;
  if(size() > UNSIGNED_INT_SIZE) {
    std::stringstream ss;
    ss << "Vector is too big for type unsigned int: size " << size() << ", max is " << UNSIGNED_INT_SIZE << ".";
    throw std::runtime_error(ss.str());
  }

  unsigned int result = 0;

  for(size_t i = 0; i < size() && i < UNSIGNED_INT_SIZE; ++i) {
    if((*this)[i]) {
      result |= 1 << i;
    }
  }

  return result;
}
