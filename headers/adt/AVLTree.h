#ifndef __AVL_TREE_INCLUDED_
#define __AVL_TREE_INCLUDED_

#include <cstdlib>
#include <stdexcept>

#include "BSTree.h"

template <class T>
using AVLTree_iterator = BSTree_iterator<T>;

template <class T>
class AVLTree : public BSTree<T> {
public:
  virtual void insert(const T&);
  virtual void remove(const T&);

protected:
  typedef BSTree<T> super;

  typedef typename BSTree<T>::Node Node;
  typedef typename BSTree<T>::Traversal Traversal;

  size_t rebalance(Node*, const T&);

  void leftRotate(Node*);
  void rightRotate(Node*);
};

template <class T>
void AVLTree<T>::insert(const T& val) {
  super::insert(val);
  rebalance(this->root, val);
}

template <class T>
void AVLTree<T>::remove(const T& val) {
  super::remove(val);
  rebalance(this->root, val);
}

#include <iostream>
using namespace std;

template <class T>
size_t AVLTree<T>::rebalance(Node* currentNode, const T& value) {
  if (!currentNode) { return 0; }

  int leftHeight = rebalance(currentNode->left, value),
      rightHeight = rebalance(currentNode->right, value);
  int balanceFactor = rightHeight - leftHeight;

  if (balanceFactor > 1) {
    if (value < currentNode->right->value) {
      rightRotate(currentNode->right);
      leftRotate(currentNode);
    } else {
      leftRotate(currentNode);
    }
    leftHeight++;
    rightHeight--;
  } else if (balanceFactor < -1) {
    if (value > currentNode->left->value) {
      leftRotate(currentNode->left);
      rightRotate(currentNode);
    } else {
      rightRotate(currentNode);
    }
    leftHeight--;
    rightHeight++;
  }

  return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

template <class T>
void AVLTree<T>::leftRotate(typename AVLTree<T>::Node* node) {
  Node* right = node->right;
  node->right = right->left;
  if (node->right) {
    node->right->parent = node;
  }
  right->left = node;
  right->parent = node->parent;
  if (!node->parent) {
    this->root = right;
  } else if (node->parent->left == node) {
    node->parent->left = right;
  } else if (node->parent->right == node) {
    node->parent->right = right;
  }
  node->parent = right;
}

template <class T>
void AVLTree<T>::rightRotate(typename AVLTree<T>::Node* node) {
  Node* left = node->left;
  node->left = left->right;
  if (node->left) {
    node->left->parent = node;
  }
  left->right = node;
  left->parent = node->parent;
  if (!left->parent) {
    this->root = left;
  } else if (node->parent->left == node) {
    node->parent->left = left;
  } else if (node->parent->right == node) {
    node->parent->right = left;
  }
  node->parent = left;
}

#endif
