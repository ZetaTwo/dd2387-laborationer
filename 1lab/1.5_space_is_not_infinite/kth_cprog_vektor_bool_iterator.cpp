#include <cmath>
#include "kth_cprog_vektor_bool.h"

using std::floor;

Vector<bool>::bool_proxy::bool_proxy(storage_type* element, subindex_type index) :
  element(element),
  index(index) {}

Vector<bool>::bool_proxy& Vector<bool>::bool_proxy::operator=(const bool value) {
  if(value) {
    *element |= 1 << index;
  } else {
    *element &= ~(1 << index);
  }

  return *this;
}

Vector<bool>::bool_proxy::operator const bool () const {
  return ((*element) & (1 << index)) != 0;
}

Vector<bool>::const_iterator::const_iterator() {}

Vector<bool>::const_iterator::const_iterator(storage_type* element, subindex_type index) :
  element(element),
  index(index) {}

Vector<bool>::const_iterator::const_iterator(const const_iterator& mit) :
  element(mit.element),
  index(mit.index) {}

Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator++() {
  if(++index > MAX_SUBINDEX) {
    ++element;
    index = 0;
  }
  return *this;
}

Vector<bool>::const_iterator Vector<bool>::const_iterator::operator++(int) {
  const_iterator tmp(*this);
  operator++();
  return tmp;
}

Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator+=(const difference_type distance) {
  element += static_cast<difference_type>(floor(static_cast<double>(index + distance) / STORAGE_BLOCK_SIZE));
  index = ((index + distance) % STORAGE_BLOCK_SIZE + STORAGE_BLOCK_SIZE) % STORAGE_BLOCK_SIZE;
  return *this;
}

Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator--() {
  if(index == 0) {
    --element;
    index = MAX_SUBINDEX;
  } else {
    --index;
  }
  return *this;
}

Vector<bool>::const_iterator Vector<bool>::const_iterator::operator--(int) {
  const_iterator tmp(*this);
  operator--();
  return tmp;
}

Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator-=(difference_type distance) {
  return *this += (-distance);
}

Vector<bool>::const_iterator Vector<bool>::const_iterator::operator+(difference_type offset) const {
  return Vector<bool>::const_iterator{*this} += offset;
}

Vector<bool>::const_iterator Vector<bool>::const_iterator::operator-(difference_type offset) const {
  return *this + (-offset);
}

Vector<bool>::const_iterator::difference_type Vector<bool>::const_iterator::operator-(const const_iterator& other) const {
  return STORAGE_BLOCK_SIZE * (element - other.element) + (index - other.index);
}

bool Vector<bool>::const_iterator::operator==(const const_iterator& rhs) const {
  return element == rhs.element && index == rhs.index;
}

bool Vector<bool>::const_iterator::operator!=(const const_iterator& rhs) const {
  return !(*this == rhs);
}

bool Vector<bool>::const_iterator::operator<(const const_iterator& rhs) const {
  return element < rhs.element || (element == rhs.element && index < rhs.index);
}

bool Vector<bool>::const_iterator::operator>(const const_iterator& rhs) const {
  return element > rhs.element || (element == rhs.element && index > rhs.index);
}

bool Vector<bool>::const_iterator::operator>=(const const_iterator& rhs) const {
  return element > rhs.element || (element == rhs.element && index >= rhs.index);
}

bool Vector<bool>::const_iterator::operator<=(const const_iterator& rhs) const {
  return element < rhs.element || (element == rhs.element && index <= rhs.index);
}

Vector<bool>::bool_proxy Vector<bool>::const_iterator::operator[](difference_type index) {
  return bool_proxy(element, index);
}

bool Vector<bool>::const_iterator::operator*() {
  return bool_proxy(element, index);
}

Vector<bool>::const_iterator operator+(const Vector<bool>::const_iterator::difference_type& distance, const Vector<bool>::const_iterator& it) {
  return it + distance;
}

Vector<bool>::iterator::iterator() {}

Vector<bool>::iterator::iterator(storage_type* element, subindex_type index) :
  element(element),
  index(index) {}

Vector<bool>::iterator::iterator(const iterator& mit) :
  element(mit.element),
  index(mit.index) {}

Vector<bool>::iterator& Vector<bool>::iterator::operator++() {
  if(++index > MAX_SUBINDEX) {
    ++element;
    index = 0;
  }
  return *this;
}

Vector<bool>::iterator Vector<bool>::iterator::operator++(int) {
  iterator tmp(*this);
  operator++();
  return tmp;
}

Vector<bool>::iterator& Vector<bool>::iterator::operator+=(difference_type distance) {
  element += static_cast<difference_type>(floor(static_cast<double>(index + distance) / STORAGE_BLOCK_SIZE));
  index = ((index + distance) % STORAGE_BLOCK_SIZE + STORAGE_BLOCK_SIZE) % STORAGE_BLOCK_SIZE;
  return *this;
}

Vector<bool>::iterator& Vector<bool>::iterator::operator--() {
  if(index == 0) {
    --element;
    index = MAX_SUBINDEX;
  } else {
    --index;
  }
  return *this;
}

Vector<bool>::iterator Vector<bool>::iterator::operator--(int) {
  iterator tmp(*this);
  operator--();
  return tmp;
}

Vector<bool>::iterator& Vector<bool>::iterator::operator-=(difference_type distance) {
  return *this += (-distance);
}

Vector<bool>::iterator Vector<bool>::iterator::operator+(difference_type offset) const {
  return Vector<bool>::iterator{*this} += offset;
}

Vector<bool>::iterator Vector<bool>::iterator::operator-(difference_type offset) const {
  return *this + (-offset);
}

Vector<bool>::iterator::difference_type Vector<bool>::iterator::operator-(const iterator& other) const {
  return STORAGE_BLOCK_SIZE * (element - other.element) + (index - other.index);
}

bool Vector<bool>::iterator::operator==(const iterator& rhs) const {
  return element == rhs.element && index == rhs.index;
}

bool Vector<bool>::iterator::operator!=(const iterator& rhs) const {
  return !(*this == rhs);
}

bool Vector<bool>::iterator::operator[](difference_type index) {
  return ((*element) & (1 << index)) != 0;
}

bool Vector<bool>::iterator::operator*() {
  return ((*element) & (1 << index)) != 0;
}

Vector<bool>::iterator operator+(const Vector<bool>::iterator::difference_type& distance, const Vector<bool>::iterator& it) {
  return it + distance;
}
