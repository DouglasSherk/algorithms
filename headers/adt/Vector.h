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
  void insertFront(const T&);
  void insertBack(const T&);
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
  setCapacity(__VECTOR_DEFAULT_SIZE);
}

template <class T>
Vector<T>::Vector(int size)
  : Vector() {
  if (size < 0) {
    throw "Index out of range";
  }
  resize(size);
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
  validateIndexInRange(index);
  return this->elements[index];
}

template <class T>
T& Vector<T>::operator [](int index) {
  validateIndexInRange(index);
  return this->elements[index];
}

template <class T>
bool Vector<T>::operator ==(const Vector<T>& other) const {
  if (length() != other.length()) {
    return false;
  }

  for (int i = 0; i < length(); i++) {
    if (this->elements[i] != other[i]) {
      return false;
    }
  }

  return true;
}

template <class T>
Vector<T>& Vector<T>::operator =(const Vector<T>& other) {
  resize(other.length());
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

  setCapacityForSize(size);
  this->elementsLength = size;
}

template <class T>
void Vector<T>::clear() {
  resize(0);
}

template <class T>
int Vector<T>::find(const T& value) const {
  for (int i = 0; i < length(); i++) {
    if (this->elements[i] == value) {
      return i;
    }
  }
  return -1;
}

template <class T>
void Vector<T>::insert(const T& value, int index) {
  validateIndexPossible(index);
  setCapacityForSize(length() + 1);

  for (int i = length(); i > index; i--) {
    this->elements[i] = this->elements[i - 1];
  }
  this->elements[index] = value;
  this->elementsLength++;
}

template <class T>
void Vector<T>::insertFront(const T& value) {
  insert(value, 0);
}

template <class T>
void Vector<T>::insertBack(const T& value) {
  insert(value, length());
}

template <class T>
T Vector<T>::remove(int index) {
  validateIndexInRange(index);

  T element = this->elements[index];
  for (int i = index; i < length() - 1; i++) {
    this->elements[i] = this->elements[i + 1];
  }
  resize(length() - 1);

  return element;
}

template <class T>
void Vector<T>::validateIndexPossible(int index) const {
  if (index < 0 || index > length()) {
    throw "Index out of range";
  }
}

template <class T>
void Vector<T>::validateIndexInRange(int index) const {
  if (index < 0 || index >= length()) {
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
    setCapacity(__VECTOR_DEFAULT_SIZE);
  } else if (size <= capacity() / 4 ||
             size >= capacity()) {
    setCapacity(size * 2);
  }
}

template <class T>
void Vector<T>::setCapacity(int newCapacity) {
  if (newCapacity < __VECTOR_DEFAULT_SIZE) {
    newCapacity = __VECTOR_DEFAULT_SIZE;
  }
  if (capacity() == newCapacity) { return; }

  T* oldElements = this->elements;
  this->elements = (T*)(new char[sizeof(T) * newCapacity]);
  for (int i = 0; i < newCapacity; i++) {
    // Zero/default-ctor any elements past the previous boundary.
    if (i >= this->elementsLength) {
      new (&this->elements[i]) T();
    // Copy elements that were part of the previous data set.
    } else {
      new (&this->elements[i]) T(oldElements[i]);
    }
  }
  this->capacityLength = newCapacity;
  delete [] oldElements;
}

#endif
