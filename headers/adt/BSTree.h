#ifndef __BS_TREE_INCLUDED_
#define __BS_TREE_INCLUDED_

#include <cstdlib>
#include <stdexcept>

#include "Pair.h"

#include <iostream>
using namespace std;

template <class T>
class BSTree {
public:
  BSTree();

  void insert(const T&);
  size_t size() const;
  void remove(const T&);

protected:
  struct Node {
    T value;
    Node* left;
    Node* right;
    Node* parent;

    size_t size() const;

    bool operator > (const Node& other) const {
      return this->value > other.value;
    }

    Node(const T&);
  };

  Node* root;

  Node** traverseTo(const T&);
};

template <class T>
BSTree<T>::Node::Node(const T& value)
  : value(value),
    left(NULL),
    right(NULL),
    parent(NULL) {

}

template <class T>
size_t BSTree<T>::Node::size() const {
  size_t size = 1;
  size += left ? left->size() : 0;
  size += right ? right->size() : 0;
  return size;
}

template <class T>
BSTree<T>::BSTree()
  : root(NULL) {

}

template <class T>
typename BSTree<T>::Node** BSTree<T>::traverseTo(const T& value) {
  Node* prev = NULL;
  Node* next = root;
  bool wentRight;
  while (next && value != next->value) {
    prev = next;

    if (value > next->value) {
      wentRight = true;
      next = next->right;
    } else {
      wentRight = false;
      next = next->left;
    }
  }

  if (next == root) {
    return &root;
  }
  return &(wentRight ? prev->right : prev->left);
}

template <class T>
void BSTree<T>::insert(const T& value) {
  Node** position = traverseTo(value);
  *position = new Node(value);
}

template <class T>
void BSTree<T>::remove(const T& value) {
  Node** position = traverseTo(value);
  if (!*position) {
    return;
  }

  Node** replacementPosition = &(*position)->left;
  Node* replacement = *replacementPosition;
  // Seek to the right-most node in the left sub-tree.
  while (replacement && replacement->right) {
    replacementPosition = &replacement->right;
    replacement = *replacementPosition;
  }

  if (replacement) {
    // There's a tree beneath this node -- move the next closest element up.
    delete *replacementPosition;
    *replacementPosition = NULL;
    (*position)->value = replacement->value;
  } else {
    // This is a leaf node -- just delete it.
    delete *position;
    *position = NULL;
  }
}

template <class T>
size_t BSTree<T>::size() const {
  return root ? root->size() : 0;
}

#endif
