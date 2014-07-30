#include "kth_cprog_vektor.cpp"

template <>
class Vector<bool> {
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

  //Iterators
  class iterator : public std::iterator<std::random_access_iterator_tag, bool>
  {
    bool* p;
  public:
    iterator() {}
    iterator(bool* x) :p(x) {}
    iterator(const iterator& mit) : p(mit.p) {}
    iterator& operator++() { ++p; return *this; }
    iterator operator++(int) { iterator tmp(*this); operator++(); return tmp; }
    iterator& operator--() { --p; return *this; }
    iterator operator--(int) { iterator tmp(*this); operator--(); return tmp; }
    iterator operator-(size_t index) const { iterator tmp(*this); tmp.p -= index; return tmp; }
    size_t operator-(const iterator &other) const { return p - other.p; }
    bool operator==(const iterator& rhs) const { return p == rhs.p; }
    bool operator!=(const iterator& rhs) const { return p != rhs.p; }
    bool& operator[](size_t index) { return *(p + index); }
    bool& operator*() { return *p; }
    bool* operator->() const { return p; }
  };

  class const_iterator : public std::iterator<std::random_access_iterator_tag, const bool>
  {
    bool* p;
  public:
    const_iterator() {}
    const_iterator(bool* x) : p(x) {}
    const_iterator(const const_iterator& mit) : p(mit.p) {}
    const_iterator& operator++() { ++p; return *this; }
    const_iterator operator++(int) { const_iterator tmp(*this); operator++(); return tmp; }
    const_iterator& operator--() { --p; return *this; }
    const_iterator operator--(int) { const_iterator tmp(*this); operator--(); return tmp; }
    const_iterator operator-(size_t index) const { const_iterator tmp(*this); tmp.p -= index; return tmp; }
    size_t operator-(const const_iterator& other) const { return p - other.p; }
    bool operator==(const const_iterator& rhs) const { return p == rhs.p; }
    bool operator!=(const const_iterator& rhs) const { return p != rhs.p; }
    bool& operator[](size_t index) { return *(p + index); }
    bool& operator*() { return *p; }
    bool const * operator->() const { return p; }
  };

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
  std::unique_ptr<unsigned int[]> data; //A pointer to the vector data (Note: 8*sizeof(unsigned int) elements per index)

  void increase_memory(int num_elements, bool copy = true); //Increases memory to fit at least num_elements number of elements
};

//Member implementations
Vector<bool>::Vector()
{

}

Vector<bool>::Vector(const Vector<bool>& other)
{

}

Vector<bool>::Vector(const std::initializer_list<bool>& list)
{

}

Vector<bool>::Vector(Vector<bool>&& other)
{

}

Vector<bool>::Vector(size_t size)
{

}

Vector<bool>::Vector(size_t size, bool element)
{

}

Vector<bool>::~Vector()
{

}

bool& Vector<bool>::operator[](size_t index) {
  bool a = true;
  return a;
}

const bool Vector<bool>::operator[](size_t index) const {
  return false;
}

Vector<bool>& Vector<bool>::operator=(const Vector<bool>& other)
{
  return *this;
}

Vector<bool>& Vector<bool>::operator=(const std::initializer_list<bool>& list)
{
  return *this;
}

Vector<bool>& Vector<bool>::operator=(Vector<bool>&& other)
{
  return *this;
}

Vector<bool>& Vector<bool>::push_back(const bool& element)
{
  return *this;
}

Vector<bool>& Vector<bool>::insert(size_t index, const bool& element)
{
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

bool Vector<bool>::exists(const bool& element) const
{
  return false;
}

size_t Vector<bool>::size() const
{
  return 0;
}

Vector<bool>::iterator Vector<bool>::begin() {
  bool a;
  return iterator(&a);
}

Vector<bool>::iterator Vector<bool>::end() {
  bool a;
  return iterator(&a);
}

Vector<bool>::const_iterator Vector<bool>::begin() const {
  bool a;
  return const_iterator(&a);
}

Vector<bool>::const_iterator Vector<bool>::end() const {
  bool a;
  return const_iterator(&a);
}

Vector<bool>::reverse_iterator Vector<bool>::rbegin() {
  bool a;
  return reverse_iterator(&a);
}

Vector<bool>::reverse_iterator Vector<bool>::rend() {
  bool a;
  return reverse_iterator(&a);
}

Vector<bool>::const_reverse_iterator Vector<bool>::rbegin() const {
  bool a;
  return const_reverse_iterator(&a);
}

Vector<bool>::const_reverse_iterator Vector<bool>::rend() const {
  bool a;
  return const_reverse_iterator(&a);
}

//Iterator implementations