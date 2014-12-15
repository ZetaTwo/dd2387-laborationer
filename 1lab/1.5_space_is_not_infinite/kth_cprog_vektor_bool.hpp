#pragma once
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
  bool_proxy& operator=(const bool value) {
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
  const_iterator();
  const_iterator(storage_type* element, subindex_type index);
  const_iterator(const const_iterator& mit);
  const_iterator& operator++();
  const_iterator operator++(int);
  const_iterator& operator+=(difference_type);
  const_iterator& operator--();
  const_iterator operator--(int);
  const_iterator& operator-=(difference_type);
  const_iterator operator+(difference_type) const;
  const_iterator operator-(difference_type offset) const;
  difference_type operator-(const const_iterator& other) const;
  bool operator==(const const_iterator& rhs) const;
  bool operator!=(const const_iterator& rhs) const;
  bool operator<(const const_iterator& rhs) const;
  bool operator>(const const_iterator& rhs) const;
  bool operator>=(const const_iterator& rhs) const;
  bool operator<=(const const_iterator& rhs) const;
  bool_proxy operator[](difference_type index);
  bool operator*();
};

Vector<bool>::const_iterator operator+(const Vector<bool>::const_iterator::difference_type&, const Vector<bool>::const_iterator& it);

class Vector<bool>::iterator : public Vector<bool>::const_iterator {
  storage_type const* element;
  subindex_type index;

public:
  iterator();
  iterator(storage_type* element, subindex_type index);
  iterator(const iterator& mit);
  iterator& operator++();
  iterator operator++(int);
  iterator& operator+=(difference_type);
  iterator& operator--();
  iterator operator--(int);
  iterator& operator-=(difference_type);
  iterator operator+(difference_type offset) const;
  iterator operator-(difference_type offset) const;
  difference_type operator-(const iterator& other) const;
  bool operator==(const iterator& rhs) const;
  bool operator!=(const iterator& rhs) const;
  bool operator[](difference_type index);
  bool operator*();
};

Vector<bool>::iterator operator+(const Vector<bool>::iterator::difference_type&, const Vector<bool>::iterator& it);
