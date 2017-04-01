#ifndef __PRIORITY_QUEUE_INCLUDED_
#define __PRIORITY_QUEUE_INCLUDED_

#include <cstdlib>
#include <string>
#include <stdexcept>

#include "Queue.h"

template <class T>
class PriorityQueue : protected Queue<T> {
public:
  void enqueue(const T&);
  T dequeue();
  int length() const;
  const T& peek() const;
};

template <class T>
int PriorityQueue<T>::length() const {
  return Queue<T>::length();
}

template <class T>
const T& PriorityQueue<T>::peek() const {
  return Queue<T>::peek();
}

template <class T>
void PriorityQueue<T>::enqueue(const T& value) {
  auto index = 0;
  auto node = this->seekTo(0);
  while (node && value > node->value) {
    node = node->nextNode;
    index++;
  }
  this->insertAt(value, index);
}

template <class T>
T PriorityQueue<T>::dequeue() {
  return Queue<T>::dequeue();
}

#endif // __PRIORITY_QUEUE_INCLUDED_
