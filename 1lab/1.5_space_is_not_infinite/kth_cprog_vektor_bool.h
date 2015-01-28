#pragma once
#include "kth_cprog_template_container.hpp"
#include <climits> // CHAR_BIT

class VectorBoolConstIterator;
class VectorBoolIterator;
class VectorBoolProxy;

template <>
class Vector<bool> {
  typedef unsigned int storage_type; static const unsigned int STORAGE_BLOCK_ALL_TRUE = -1;
  typedef unsigned char subindex_type;

  static const size_t STORAGE_BLOCK_SIZE = sizeof(storage_type) * CHAR_BIT;
  static const subindex_type MAX_SUBINDEX = STORAGE_BLOCK_SIZE - 1;

  typedef VectorBoolProxy bool_proxy; friend class VectorBoolProxy;

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
  bool operator[](size_t index) const;
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
  Vector<bool>& push_back(bool element);
  Vector<bool>& insert(size_t index, bool element);
  Vector<bool>& erase(size_t index);
  Vector<bool>& clear();
  Vector<bool>& sort(bool ascending = true);
  Vector<bool>& unique_sort(bool ascending = true);

  //Lookup in vector
  bool exists(bool element) const;
  size_t size() const;

  size_t weight() const;
  size_t weight1() const;

  //Iterators
public:
  typedef VectorBoolConstIterator const_iterator; friend class VectorBoolConstIterator;
  typedef VectorBoolIterator iterator; friend class VectorBoolIterator;
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
  static Vector<bool> from_integer(unsigned int numeric);

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
class VectorBoolProxy {
private:
  typedef Vector<bool>::storage_type storage_type;
  typedef Vector<bool>::subindex_type subindex_type;

  storage_type* element;
  subindex_type index;
public:
  VectorBoolProxy(storage_type* element, subindex_type index);
  VectorBoolProxy& operator=(const bool value);
  operator const bool () const;
};

class VectorBoolConstIterator : public std::iterator<std::random_access_iterator_tag, const bool> {
protected:
  typedef Vector<bool>::storage_type storage_type;
  typedef Vector<bool>::subindex_type subindex_type;

  subindex_type index;
  storage_type * element;
  
public:
  VectorBoolConstIterator();
  VectorBoolConstIterator(storage_type* element, subindex_type index);
  VectorBoolConstIterator(const VectorBoolConstIterator& mit);
  VectorBoolConstIterator& operator=(const VectorBoolConstIterator& mit);
  VectorBoolConstIterator& operator++();
  VectorBoolConstIterator operator++(int);
  VectorBoolConstIterator& operator+=(difference_type distance);
  VectorBoolConstIterator& operator--();
  VectorBoolConstIterator operator--(int);
  VectorBoolConstIterator& operator-=(difference_type distance);
  VectorBoolConstIterator operator+(difference_type offset) const;
  VectorBoolConstIterator operator-(difference_type offset) const;
  difference_type operator-(const VectorBoolConstIterator& other) const;
  bool operator==(const VectorBoolConstIterator& rhs) const;
  bool operator!=(const VectorBoolConstIterator& rhs) const;
  bool operator<(const VectorBoolConstIterator& rhs) const;
  bool operator>(const VectorBoolConstIterator& rhs) const;
  bool operator>=(const VectorBoolConstIterator& rhs) const;
  bool operator<=(const VectorBoolConstIterator& rhs) const;
  value_type operator[](difference_type offset) const;
  value_type operator*() const;
};

VectorBoolConstIterator operator+(const VectorBoolConstIterator::difference_type&, const VectorBoolConstIterator& it);

class VectorBoolIterator : public VectorBoolConstIterator {
public:
  typedef bool value_type;
  typedef void pointer;
  typedef VectorBoolProxy reference;

  VectorBoolIterator();
  VectorBoolIterator(storage_type* element, subindex_type index);
  VectorBoolIterator(const VectorBoolIterator& mit);
  VectorBoolIterator& operator=(const VectorBoolIterator& mit);
  VectorBoolIterator& operator++();
  VectorBoolIterator operator++(int);
  VectorBoolIterator& operator+=(difference_type distance);
  VectorBoolIterator& operator--();
  VectorBoolIterator operator--(int);
  VectorBoolIterator& operator-=(difference_type distance);
  VectorBoolIterator operator+(difference_type offset) const;
  VectorBoolIterator operator-(difference_type offset) const;
  difference_type operator-(const VectorBoolIterator& other) const;
  reference operator[](difference_type offset) const;
  reference operator*() const;
};

VectorBoolIterator operator+(const VectorBoolIterator::difference_type&, const VectorBoolIterator& it);
