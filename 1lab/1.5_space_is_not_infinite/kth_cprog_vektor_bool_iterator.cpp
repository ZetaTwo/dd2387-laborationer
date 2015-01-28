#include <cmath>
#include "kth_cprog_vektor_bool.h"

using std::floor;

VectorBoolConstIterator::VectorBoolConstIterator() {}

VectorBoolConstIterator::VectorBoolConstIterator(storage_type* element, subindex_type index) :
  index(index),
  element(element) {}

VectorBoolConstIterator::VectorBoolConstIterator(const VectorBoolConstIterator& mit) :
  VectorBoolConstIterator(mit.element, mit.index) {}

VectorBoolConstIterator& VectorBoolConstIterator::operator=(const VectorBoolConstIterator& mit) {
  element = mit.element;
  index = mit.index;
  return *this;
}

VectorBoolConstIterator& VectorBoolConstIterator::operator++() {
  if(++index > Vector<bool>::MAX_SUBINDEX) {
    ++element;
    index = 0;
  }
  return *this;
}

VectorBoolConstIterator VectorBoolConstIterator::operator++(int) {
  VectorBoolConstIterator tmp(*this);
  operator++();
  return tmp;
}

VectorBoolConstIterator& VectorBoolConstIterator::operator+=(const difference_type distance) {
  element += static_cast<difference_type>(floor(static_cast<double>(index + distance) / Vector<bool>::STORAGE_BLOCK_SIZE));
  index = ((index + distance) % Vector<bool>::STORAGE_BLOCK_SIZE + Vector<bool>::STORAGE_BLOCK_SIZE) % Vector<bool>::STORAGE_BLOCK_SIZE;
  return *this;
}

VectorBoolConstIterator& VectorBoolConstIterator::operator--() {
  if(index == 0) {
    --element;
    index = Vector<bool>::MAX_SUBINDEX;
  } else {
    --index;
  }
  return *this;
}

VectorBoolConstIterator VectorBoolConstIterator::operator--(int) {
  VectorBoolConstIterator tmp(*this);
  operator--();
  return tmp;
}

VectorBoolConstIterator& VectorBoolConstIterator::operator-=(const difference_type distance) {
  return *this += (-distance);
}

VectorBoolConstIterator VectorBoolConstIterator::operator+(const difference_type offset) const {
  return VectorBoolConstIterator{*this} += offset;
}

VectorBoolConstIterator VectorBoolConstIterator::operator-(const difference_type offset) const {
  return *this + (-offset);
}

VectorBoolConstIterator::difference_type VectorBoolConstIterator::operator-(const VectorBoolConstIterator& other) const {
  return Vector<bool>::STORAGE_BLOCK_SIZE * (element - other.element) + (index - other.index);
}

bool VectorBoolConstIterator::operator==(const VectorBoolConstIterator& rhs) const {
  return element == rhs.element && index == rhs.index;
}

bool VectorBoolConstIterator::operator!=(const VectorBoolConstIterator& rhs) const {
  return !(*this == rhs);
}

bool VectorBoolConstIterator::operator<(const VectorBoolConstIterator& rhs) const {
  return element < rhs.element || (element == rhs.element && index < rhs.index);
}

bool VectorBoolConstIterator::operator>(const VectorBoolConstIterator& rhs) const {
  return element > rhs.element || (element == rhs.element && index > rhs.index);
}

bool VectorBoolConstIterator::operator>=(const VectorBoolConstIterator& rhs) const {
  return element > rhs.element || (element == rhs.element && index >= rhs.index);
}

bool VectorBoolConstIterator::operator<=(const VectorBoolConstIterator& rhs) const {
  return element < rhs.element || (element == rhs.element && index <= rhs.index);
}

VectorBoolConstIterator::value_type VectorBoolConstIterator::operator[](const difference_type offset) const {
  return *(*this + offset);
}

VectorBoolConstIterator::value_type VectorBoolConstIterator::operator*() const {
  return ((*element) & (1 << index)) != 0;
}

VectorBoolConstIterator operator+(const VectorBoolConstIterator::difference_type& distance, const VectorBoolConstIterator& it) {
  return it + distance;
}

VectorBoolIterator::VectorBoolIterator() {}

VectorBoolIterator::VectorBoolIterator(storage_type* const element, const subindex_type index) :
  VectorBoolConstIterator(element, index) {}

VectorBoolIterator::VectorBoolIterator(const VectorBoolIterator& mit) :
  VectorBoolConstIterator(mit.element, mit.index) {}

VectorBoolIterator& VectorBoolIterator::operator=(const VectorBoolIterator& mit) {
  element = mit.element;
  index = mit.index;
  return *this;
}

VectorBoolIterator& VectorBoolIterator::operator++() {
  if(++index > Vector<bool>::MAX_SUBINDEX) {
    ++element;
    index = 0;
  }
  return *this;
}

VectorBoolIterator VectorBoolIterator::operator++(int) {
  VectorBoolIterator tmp(*this);
  operator++();
  return tmp;
}

VectorBoolIterator& VectorBoolIterator::operator+=(const difference_type distance) {
  element += static_cast<difference_type>(floor(static_cast<double>(index + distance) / Vector<bool>::STORAGE_BLOCK_SIZE));
  index = ((index + distance) % Vector<bool>::STORAGE_BLOCK_SIZE + Vector<bool>::STORAGE_BLOCK_SIZE) % Vector<bool>::STORAGE_BLOCK_SIZE;
  return *this;
}

VectorBoolIterator& VectorBoolIterator::operator--() {
  if(index == 0) {
    --element;
    index = Vector<bool>::MAX_SUBINDEX;
  } else {
    --index;
  }
  return *this;
}

VectorBoolIterator VectorBoolIterator::operator--(int) {
  VectorBoolIterator tmp(*this);
  operator--();
  return tmp;
}

VectorBoolIterator& VectorBoolIterator::operator-=(const difference_type distance) {
  return *this += (-distance);
}

VectorBoolIterator VectorBoolIterator::operator+(const difference_type offset) const {
  return VectorBoolIterator{*this} += offset;
}

VectorBoolIterator VectorBoolIterator::operator-(const difference_type offset) const {
  return *this + (-offset);
}

VectorBoolIterator::difference_type VectorBoolIterator::operator-(const VectorBoolIterator& other) const {
  return Vector<bool>::STORAGE_BLOCK_SIZE * (element - other.element) + (index - other.index);
}

VectorBoolIterator::reference VectorBoolIterator::operator[](const difference_type offset) const {
  return *(*this + offset);
}

VectorBoolIterator::reference VectorBoolIterator::operator*() const {
  return reference(element, index);
}

VectorBoolIterator operator+(const VectorBoolIterator::difference_type& distance, const VectorBoolIterator& it) {
  return it + distance;
}
