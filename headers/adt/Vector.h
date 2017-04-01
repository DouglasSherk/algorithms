#ifndef __VECTOR_INCLUDED_
#define __VECTOR_INCLUDED_

#include <cstdlib>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

#define __VECTOR_DEFAULT_SIZE 16

template <class T>
class Vector {
public:
  void resize(int);
  void insert(const T&, int);
  T remove(int);
  int find(const T&) const;
  void clear();
  int length() const;
  int capacity() const;

  Vector();
  Vector(int);
  Vector(const Vector<T>&);
  ~Vector();

  const T& operator [](int) const;
  T& operator [](int);
  bool operator ==(const Vector<T>&) const;
  Vector<T>& operator =(const Vector<T>&);

protected:
  void validateIndexInRange(int) const;
  void validateIndexPossible(int) const;
  void maybeResizeArray();
  void setCapacity(int);
  void setCapacityForSize(int);

  T* elements;
  int capacityLength;
  int elementsLength;
};

template <class T>
Vector<T>::Vector()
  : elementsLength(0),
    capacityLength(0),
    elements(NULL) {
  this->setCapacity(__VECTOR_DEFAULT_SIZE);
}

template <class T>
Vector<T>::Vector(int size)
  : Vector() {
  if (size < 0) {
    throw "Index out of range";
  }
  this->resize(size);
}

template <class T>
Vector<T>::Vector(const Vector<T>& other)
  : Vector() {
  *this = other;
}

template <class T>
Vector<T>::~Vector() {
  delete [] this->elements;
}

template <class T>
const T& Vector<T>::operator [](int index) const {
  this->validateIndexInRange(index);
  return this->elements[index];
}

template <class T>
T& Vector<T>::operator [](int index) {
  this->validateIndexInRange(index);
  return this->elements[index];
}

template <class T>
bool Vector<T>::operator ==(const Vector<T>& other) const {
  if (this->length() != other.length()) {
    return false;
  }

  for (int i = 0; i < this->length(); i++) {
    if (this->elements[i] != other[i]) {
      return false;
    }
  }

  return true;
}

template <class T>
Vector<T>& Vector<T>::operator =(const Vector<T>& other) {
  this->resize(other.length());
  for (int i = 0; i < other.length(); i++) {
    this->elements[i] = other[i];
  }
  return *this;
}

template <class T>
void Vector<T>::resize(int size) {
  if (size < 0) {
    throw "Size out of range";
  }

  this->setCapacityForSize(size);
  this->elementsLength = size;
}

template <class T>
void Vector<T>::clear() {
  this->resize(0);
}

template <class T>
int Vector<T>::find(const T& value) const {
  for (int i = 0; i < this->length(); i++) {
    if (this->elements[i] == value) {
      return i;
    }
  }
  return -1;
}

template <class T>
void Vector<T>::insert(const T& value, int index) {
  this->validateIndexPossible(index);
  this->setCapacityForSize(this->length() + 1);

  for (int i = this->length(); i > index; i--) {
    this->elements[i] = this->elements[i - 1];
  }
  this->elements[index] = value;
  this->elementsLength++;
}

template <class T>
T Vector<T>::remove(int index) {
  this->validateIndexInRange(index);

  T element = this->elements[index];
  for (int i = index; i < this->length() - 1; i++) {
    this->elements[i] = this->elements[i + 1];
  }
  this->resize(this->length() - 1);

  return element;
}

template <class T>
void Vector<T>::validateIndexPossible(int index) const {
  if (index < 0 || index > this->length()) {
    throw "Index out of range";
  }
}

template <class T>
void Vector<T>::validateIndexInRange(int index) const {
  if (index < 0 || index >= this->length()) {
    throw "Index out of range";
  }
}

template <class T>
int Vector<T>::length() const {
  return this->elementsLength;
}

template <class T>
int Vector<T>::capacity() const {
  return this->capacityLength;
}

template <class T>
void Vector<T>::setCapacityForSize(int size) {
  if (size == 0) {
    this->setCapacity(__VECTOR_DEFAULT_SIZE);
  } else if (size <= this->capacity() / 4 ||
             size >= this->capacity()) {
    this->setCapacity(size * 2);
  }
}

template <class T>
void Vector<T>::setCapacity(int capacity) {
  if (capacity < __VECTOR_DEFAULT_SIZE) {
    capacity = __VECTOR_DEFAULT_SIZE;
  }
  if (this->capacity() == capacity) { return; }

  T* oldElements = this->elements;
  this->elements = (T*)(new char[sizeof(T) * capacity]);
  for (int i = 0; i < capacity; i++) {
    // Zero/default-ctor any elements past the previous boundary.
    if (i >= this->elementsLength) {
      new (&this->elements[i]) T();
    // Copy elements that were part of the previous data set.
    } else {
      new (&this->elements[i]) T(oldElements[i]);
    }
  }
  this->capacityLength = capacity;
  delete [] oldElements;
}

#endif
