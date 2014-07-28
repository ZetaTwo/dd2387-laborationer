#pragma once

#include <memory> //unique_ptr<T>
#include <initializer_list>
#include <sstream>

typedef unsigned int T;

class Vector {
public:
  //Constructors & destructors
  Vector();
  Vector(const Vector& other);
  Vector(const std::initializer_list<T>& list);
  Vector(Vector&& other); //Move
  explicit Vector(size_t size);
  Vector(size_t size, T element);
  ~Vector();

  //Operators
  T& operator[](size_t index);
  const T operator[](size_t index) const;
  Vector& operator=(const Vector& other);
  Vector& operator=(const std::initializer_list<T>& list);
  Vector& operator=(Vector&& other); //Move

  //Modify vector
  Vector& push_back(const T& element);
  Vector& insert(size_t index, const T& element);
  Vector& erase(size_t index);
  Vector& clear();
  Vector& sort(bool ascending = true);
  Vector& unique_sort(bool ascending = true);

  //Lookup in vector
  bool exists(const T& element) const;
  size_t size() const;
private:
  static const int DEFAULT_SIZE = 16;

  size_t count; //Actual number of elements in the vector
  size_t max_size; //Allocated memory for elements. Will be 2^n for some n
  std::unique_ptr<T[]> data; //A pointer to the vector data

  void increase_memory(int num_elements, bool copy = true); //Increases memory to fit at least num_elements number of elements
};
