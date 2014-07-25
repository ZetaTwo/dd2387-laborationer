#pragma once

#include <memory> //unique_ptr<T>
#include <stdexcept>
#include <initializer_list>
#include <cmath>

template<typename T> 
class Vector
{
public:
	//Constructors & destructors
	Vector();
	Vector(const Vector<T> &other);
	Vector(const std::initializer_list<T> &list);
  Vector(Vector<T>&& other); //Move
	explicit Vector(size_t size);
	Vector(size_t size, T element);
	~Vector();

	//Operators
	T& operator[](size_t index);
	const T operator[](size_t index) const;
	Vector<T>& operator=(const Vector<T> & other);
	Vector<T>& operator=(const std::initializer_list<T> &list);
  Vector<T>& operator=(Vector<T>&& other); //Move

	//Modify vector
	Vector<T> &push_back(const T& element);
	Vector<T> &insert(size_t index, const T& element);
	Vector<T> &erase(size_t index);
	Vector<T> &clear();
	Vector<T> &sort(bool ascending = true);
	Vector<T> &unique_sort(bool ascending = true);

	//Lookup in vector
	bool exists(const T &element) const;
	size_t size() const;
private:
  const int DEFAULT_SIZE = 16;

  size_t count; //Actual number of elements in the vector
  size_t max_size; //Allocated memory for elements. Will be 2^n for some n
  std::unique_ptr<T[]> data; //A pointer to the vector data

  void increase_memory(int num_elements, bool copy = true); //Increases memory to fit at least num_elements number of elements
};

template<typename T>
Vector<T>::Vector() : count(0), max_size(DEFAULT_SIZE), data(new T[max_size]) {

}

template<typename T>
Vector<T>::Vector(const Vector<T> &other) : count(other.count), max_size(other.max_size), data(new T[max_size]) {
  for (size_t i = 0; i < count; ++i)
  {
    data[i] = other.data[i];
  }
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T> &list) : count(list.size()), max_size(1 << static_cast<int>(ceil(log2(count)))), data(new T[max_size]) {
  size_t i;
  typename std::initializer_list<T>::iterator item;
  for (i = 0, item = list.begin(); item != list.end(); ++i, ++item)
  {
    data[i] = *item;
  }
}

template<typename T>
Vector<T>::Vector(size_t size) : count(size), max_size(1 << static_cast<int>(ceil(log2(count)))), data(new T[max_size]) {
  for (size_t i = 0; i < count; ++i)
  {
    data[i] = T();
  }
}

template<typename T>
Vector<T>::Vector(size_t size, T element) : count(size), max_size(1 << static_cast<int>(ceil(log2(count)))), data(new T[max_size]) {
  for (size_t i = 0; i < count; ++i)
  {
    data[i] = element;
  }
}

template<typename T>
Vector<T>::~Vector() {

}

template<typename T>
T& Vector<T>::operator[](size_t index) {
  if (index < 0 || index >= count) {
    throw std::out_of_range("Index out of range");
  }
	return data[index];
}

template<typename T>
const T Vector<T>::operator[](size_t index) const {
  if (index < 0 || index >= count) {
    throw std::out_of_range("Index out of range");
  }

  return data[index];
}

template<typename T>
Vector<T> & Vector<T>::operator=(const Vector<T> & other) {
  if (&other == this) {
    return  *this;
  }

  if (other.count > max_size) {
    increase_memory(other.count, false);
  }

  count = other.size();
  for (size_t i = 0; i < other.count; ++i)
  {
    data[i] = other[i];
  }

	return *this;
}

template<typename T>
Vector<T> & Vector<T>::operator=(const std::initializer_list<T> &list) {
  if (list.size > max_size) {
    increase_memory(list.size, false);
  }

  count = list.size();
  for (size_t i = 0; i < list.count; i++)
  {
    data[i] = list[i];
  }

	return *this;
}

template<typename T>
Vector<T> & Vector<T>::push_back(const T& element) {
	return *this;
}

template<typename T>
Vector<T> & Vector<T>::insert(size_t index, const T& element) {
	return *this;
}

template<typename T>
Vector<T> & Vector<T>::erase(size_t index) {
	return *this;
}

template<typename T>
Vector<T> & Vector<T>::clear() {
	return *this;
}

template<typename T>
Vector<T> & Vector<T>::sort(bool ascending) {
	return *this;
}

template<typename T>
Vector<T> & Vector<T>::unique_sort(bool ascending) {
	return *this;
}

template<typename T>
bool Vector<T>::exists(const T &element) const {
	return false;
}

template<typename T>
size_t Vector<T>::size() const {
	return count;
}

template<typename T>
void Vector<T>::increase_memory(int num_elements, bool copy) {
  size_t new_max_size = (1 << static_cast<int>(ceil(log2(num_elements))));
  if (new_max_size < max_size) {
    throw std::invalid_argument("Vector already large enough");
  }

  std::unique_ptr<T[]> new_data(new T[new_max_size]);

  if (copy) {
    for (size_t i = 0; i < count; i++)
    {
      new_data[i] = data[i];
    }
  }

  data = std::move(new_data);
}