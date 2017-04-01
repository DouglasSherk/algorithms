#ifndef __QUEUE_INCLUDED_
#define __QUEUE_INCLUDED_

#include <cstdlib>
#include <string>
#include <stdexcept>

#include "List.h"

template <class T>
class Queue : protected List<T> {
public:
  void enqueue(const T&);
  T dequeue();
  int length() const;
  const T& peek() const;
};

template <class T>
int Queue<T>::length() const {
  return List<T>::length();
}

template <class T>
const T& Queue<T>::peek() const {
  return this->back();
}

template <class T>
void Queue<T>::enqueue(const T& value) {
  this->insertFront(value);
}

template <class T>
T Queue<T>::dequeue() {
  T value = this->back();
  this->removeBack();
  return value;
}

#endif
