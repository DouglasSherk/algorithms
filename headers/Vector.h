#ifndef __VECTOR_INCLUDED_
#define __VECTOR_INCLUDED_

#include <cstdlib>
#include <string>
#include <stdexcept>

#define __VECTOR_DEFAULT_SIZE 16

template <class T>
class Vector {
public:
  const T& operator [](int) const;
  T& operator [](int);
  void resize(int);
  void insert(const T&, int);
  const T& remove(int);
  int find(const T&) const;
  void clear();
  int length() const;
  int capacity() const;

  Vector();
  Vector(int);
  ~Vector();

protected:
  void validateIndexInRange(int) const;
  void validateIndexPossible(int) const;
  void maybeResizeArray();
  void resizeArray(int);

  T* elements;
  int capacityLength;
  int elementsLength;
};

template <class T>
Vector<T>::Vector()
  : elementsLength(0),
    elements(NULL) {
  this->resizeArray(__VECTOR_DEFAULT_SIZE);
}

template <class T>
Vector<T>::Vector(int size)
  : Vector() {
  this->resizeArray(size);
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
void Vector<T>::resize(int size) {
  if (size < 0) {
    throw "Index out of range";
  }

  this->resizeArray(size * 2);
  this->elementsLength = size;
}

template <class T>
void Vector<T>::clear() {
  this->resizeArray(__VECTOR_DEFAULT_SIZE);
  this->elementsLength = 0;
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

  for (int i = this->length() - 1; i > index; i--) {
    this->elements[i] = this->elements[i - 1];
  }
  this->elements[index] = value;
  this->elementsLength++;

  this->maybeResizeArray();
}

template <class T>
const T& Vector<T>::remove(int index) {
  this->validateIndexInRange(index);

  T& element = this->elements[index];
  for (int i = index; i < this->length() - 1; i++) {
    this->elements[i] = this->elements[i + 1];
  }
  this->elementsLength--;

  this->maybeResizeArray();

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
void Vector<T>::maybeResizeArray() {
  if (this->length() == 0) {
    this->resizeArray(__VECTOR_DEFAULT_SIZE);
  } else if (this->length() < this->capacity() / 4) {
    this->resizeArray(this->capacity() / 2);
  } else if (this->length() == this->capacity()) {
    this->resizeArray(this->capacity() * 2);
  }
}

template <class T>
void Vector<T>::resizeArray(int size) {
  T* oldElements = this->elements;
  this->elements = (T*)(new char[sizeof(T) * size]);
  for (int i = 0; i < size; i++) {
    // Zero/default-ctor any elements past the previous boundary.
    if (i >= this->elementsLength) {
      new (&this->elements[i]) T();
    // Copy elements that were part of the previous data set.
    } else {
      new (&this->elements[i]) T(oldElements[i]);
    }
  }
  this->capacityLength = size;
  delete [] oldElements;
}

#endif
