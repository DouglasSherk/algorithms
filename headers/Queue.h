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
  const T& dequeue();
  int length();
};

template <class T>
int Queue<T>::length() {
  return List<T>::length();
}

template <class T>
void Queue<T>::enqueue(const T& value) {
  this->insertFront(value);
}

template <class T>
const T& Queue<T>::dequeue() {
  const T& value = this->back();
  this->removeBack();
  return value;
}

#endif
