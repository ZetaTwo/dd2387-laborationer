#include <algorithm>

#include "kth_cprog_vektor_bool.h"

using std::copy_n;
using std::fill_n;

Vector<bool>::Vector() : count(0), max_size(DEFAULT_SIZE), data(new storage_type[storage_size()]) {
}

Vector<bool>::Vector(const Vector<bool>& other) : count(other.count), max_size(other.max_size), data(new storage_type[storage_size()]) {
  copy_n(other.data.get(), other.storage_size(), data.get());
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

Vector<bool>::Vector(size_t size) : Vector<bool>(size, false) {
}

Vector<bool>::Vector(size_t size, bool element) : count(size), max_size(initial_size(count)), data(new storage_type[storage_size()]) {
  fill_n(data.get(), storage_size(), element ? STORAGE_BLOCK_ALL_TRUE : 0);
}

Vector<bool>::~Vector() {
}

VectorBoolProxy Vector<bool>::operator[](size_t index) {
  if(index >= count) {
    std::stringstream msg;
    msg << "Index out of range: " << index << ", expected range [0 - " << count << ")";
    throw std::out_of_range(msg.str());
  }
  return bool_proxy(data.get() + (index / STORAGE_BLOCK_SIZE), index % STORAGE_BLOCK_SIZE);
}

bool Vector<bool>::operator[](size_t index) const {
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

  copy_n(other.data.get(), other.storage_size(), data.get());

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

Vector<bool>& Vector<bool>::push_back(bool element) {
  return insert(count, element);
}

Vector<bool>& Vector<bool>::insert(const size_t index, bool element) {
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
  if(erase_storage_index + 1 < storage_size()) {
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

  if(num_front >= size()) {
    return *this;
  }

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

bool Vector<bool>::exists(const bool element) const {
  for(size_t i = 0; i < count / STORAGE_BLOCK_SIZE; ++i) {
    if((element ? data[i] : ~data[i]) != 0) {
      return true;
    }
  }
  if(size() % STORAGE_BLOCK_SIZE != 0) {
    const storage_type d = data[count / STORAGE_BLOCK_SIZE];
    if((element ? d : ~d) % (1 << count % STORAGE_BLOCK_SIZE) != 0) {
      return true;
    }
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
  return iterator(data.get(), 0);
}

Vector<bool>::iterator Vector<bool>::end() {
  return iterator(&data[count / STORAGE_BLOCK_SIZE], count % STORAGE_BLOCK_SIZE);
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
  return const_iterator(data.get(), 0);
}

Vector<bool>::const_iterator Vector<bool>::end() const {
  return const_iterator(&data[count / STORAGE_BLOCK_SIZE], count % STORAGE_BLOCK_SIZE);
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
}

Vector<bool>::reverse_iterator Vector<bool>::rend() {
  return reverse_iterator(begin());
}

Vector<bool>::const_reverse_iterator Vector<bool>::rbegin() const {
  return const_reverse_iterator(const_iterator(data.get() + (count / STORAGE_BLOCK_SIZE), count % STORAGE_BLOCK_SIZE));
}

Vector<bool>::const_reverse_iterator Vector<bool>::rend() const {
  return const_reverse_iterator(const_iterator(data.get(), 0));
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

Vector<bool> Vector<bool>::from_integer(const unsigned int vec_i) {
  const size_t UNSIGNED_INT_SIZE = sizeof(unsigned int) * CHAR_BIT;
  Vector<bool> result(UNSIGNED_INT_SIZE);

  for(size_t i = 0; i < UNSIGNED_INT_SIZE; ++i) {
    result[i] = ((vec_i >> i) & 1) == 1;
  }

  return result;
}

VectorBoolProxy::VectorBoolProxy(storage_type* element, subindex_type index) :
  element(element),
  index(index) {}

VectorBoolProxy& VectorBoolProxy::operator=(VectorBoolProxy&& other) {
  return (*this) = static_cast<bool>(other);
}

VectorBoolProxy& VectorBoolProxy::operator=(const bool value) {
  if(value) {
    *element |= 1 << index;
  } else {
    *element &= ~(1 << index);
  }

  return *this;
}

VectorBoolProxy::operator const bool () const {
  return ((*element) & (1 << index)) != 0;
}

void swap(VectorBoolProxy p1, VectorBoolProxy p2) {
  const bool v1 = p1, v2 = p2;
  p1 = v2, p2 = v1;
}
