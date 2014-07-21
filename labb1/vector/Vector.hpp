#pragma once

#include <memory> //unique_ptr<T>
#include <stdexcept>

template<typename T> 
class Vector
{
public:
	//Constructors & destructors
	Vector();
	Vector(const Vector<T> &other);
	Vector(const std::initializer_list<T> &list);
	explicit Vector(size_t size);
	Vector(size_t size, T element);
	~Vector();

	//Operators
	T& operator[](size_t index);
	const T operator[](size_t index) const;
	Vector<T> &operator=(const Vector<T> & other);
	Vector<T> &operator=(const std::initializer_list<T> &list);

	//Modify vector
	Vector<T> &push_back(T element);
	Vector<T> &insert(size_t index, T element);
	Vector<T> &erase(size_t index);
	Vector<T> &clear();
	Vector<T> &sort(bool ascending = true);
	Vector<T> &unique_sort(bool ascending = true);

	//Lookup in vector
	bool exists(const T &element) const;
	size_t size() const;
private:
	std::unique_ptr<T*> data; //A pointer to the vector data
	int count; //Actual number of elements in the vector
	int max_size; //Allocated memory for elements. Will be 2^n for some n

	const int DEFAULT_SIZE = 16;
};

template<typename T>
Vector<T>::Vector() {

}

template<typename T>
Vector<T>::Vector(const Vector<T> &other) {

}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T> &list) {

}

template<typename T>
Vector<T>::Vector(size_t size) {

}

template<typename T>
Vector<T>::Vector(size_t size, T element) {

}

template<typename T>
Vector<T>::~Vector() {

}

template<typename T>
T& Vector<T>::operator[](size_t index) {
	T value = T();
	return value;
}

template<typename T>
const T Vector<T>::operator[](size_t index) const {
	T value = T();
	return value;
}

template<typename T>
Vector<T> & Vector<T>::operator=(const Vector<T> & other) {
	return *this;
}

template<typename T>
Vector<T> & Vector<T>::operator=(const std::initializer_list<T> &list) {
	return *this;
}

template<typename T>
Vector<T> & Vector<T>::push_back(T element) {
	return *this;
}

template<typename T>
Vector<T> & Vector<T>::insert(size_t index, T element) {
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
Vector<T> & Vector<T>::sort(bool ascending = true) {
	return *this;
}

template<typename T>
Vector<T> & Vector<T>::unique_sort(bool ascending = true) {
	return *this;
}

template<typename T>
bool Vector<T>::exists(const T &element) const {
	return false;
}

template<typename T>
size_t Vector<T>::size() const {
	return -1;
}