#ifndef __LIST_INCLUDED_
#define __LIST_INCLUDED_

#include <cstdlib>
#include <string>
#include <stdexcept>

template <class T>
class List {
public:
  void insertAt(const T&, int);
  void insertFront(const T&);
  void insertBack(const T&);
  void removeAt(int);
  void remove(const T&);
  void removeFront();
  void removeBack();

  const T& getAt(int) const;
  int indexOf(const T&) const;
  const T& front() const;
  const T& back() const;
  int length() const;

  List<T>();
  ~List<T>();

protected:
  struct ListNode {
    ListNode* nextNode;
    ListNode* prevNode;
    T value;
    ListNode(const T&);
  };

  void validateIndex(int) const;

  ListNode* seekTo(int) const;
  ListNode* find(const T&) const;

  ListNode* frontNode;
  ListNode* backNode;
  int nodesLength;
};

template <class T>
List<T>::ListNode::ListNode(const T& val)
  : value(val),
    nextNode(NULL),
    prevNode(NULL) {

}

template <class T>
List<T>::List()
  : frontNode(NULL),
    backNode(NULL),
    nodesLength(0) {

}

template <class T>
void List<T>::validateIndex(int index) const {
  if (index < 0 || index > this->length()) {
    throw "Index out of range";
  }
}

template <class T>
List<T>::~List() {
  ListNode* node = this->frontNode;
  while (node) {
    ListNode* current = node;
    node = node->nextNode;
    delete current;
  }
}

template <class T>
typename List<T>::ListNode* List<T>::find(const T& val) const {
  ListNode* node = this->frontNode;
  while (node) {
    if (node->value == val) {
      return node;
    }
    node = node->nextNode;
  }
  return NULL;
}

template <class T>
typename List<T>::ListNode* List<T>::seekTo(int seekTo) const {
  int index = 0;
  ListNode* node = this->frontNode;
  while (node && index < seekTo) {
    node = node->nextNode;
    index++;
  }
  return index == seekTo ? node : NULL;
}

template <class T>
int List<T>::indexOf(const T& val) const {
  int index = 0;
  ListNode* node = this->frontNode;
  while (node) {
    if (node->value == val) {
      return index;
    }
    node = node->nextNode;
    index++;
  }
  return -1;
}

template <class T>
void List<T>::insertAt(const T& val, int index) {
  this->validateIndex(index);

  ListNode* newNode = new ListNode(val);
  ListNode* prevNode = this->seekTo(index - 1);
  ListNode* nextNode = this->seekTo(index);
  if (prevNode) {
    prevNode->nextNode = newNode;
    newNode->prevNode = prevNode;
  }
  if (nextNode) {
    nextNode->prevNode = newNode;
    newNode->nextNode = nextNode;
  }

  if (!this->frontNode || index == 0) {
    this->frontNode = newNode;
  }
  if (!this->backNode || index == this->length()) {
    this->backNode = newNode;
  }

  nodesLength++;
}

template <class T>
void List<T>::insertBack(const T& val) {
  ListNode* node = new ListNode(val);
  this->insertAt(val, this->length());
}

template <class T>
void List<T>::insertFront(const T& val) {
  ListNode* node = new ListNode(val);
  this->insertAt(val, 0);
}

template <class T>
void List<T>::removeAt(int index) {
  this->validateIndex(index);
  ListNode* node = this->seekTo(index);
  if (node == this->frontNode) {
    this->frontNode = node->nextNode;
  }
  if (node == this->backNode) {
    this->backNode = node->prevNode;
  }
  if (node->prevNode) {
    node->prevNode->nextNode = node->nextNode;
  }
  if (node->nextNode) {
    node->nextNode->prevNode = node->prevNode;
  }
  nodesLength--;
  delete node;
}

template <class T>
void List<T>::remove(const T& val) {
  int index = this->indexOf(val);
  this->removeAt(index);
}

template <class T>
void List<T>::removeFront() {
  this->removeAt(0);
}

template <class T>
void List<T>::removeBack() {
  this->removeAt(this->length() - 1);
}

template <class T>
int List<T>::length() const {
  return this->nodesLength;
}

template <class T>
const T& List<T>::getAt(int index) const {
  ListNode* node = this->seekTo(index);
  return node->value;
}

template <class T>
const T& List<T>::front() const {
  return this->getAt(0);
}

template <class T>
const T& List<T>::back() const {
  return this->getAt(this->length() - 1);
}

#endif
