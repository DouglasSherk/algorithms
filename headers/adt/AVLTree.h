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
  void insert(const T&);
  void remove(const T&);

protected:
  typedef BSTree<T> super;

  void rebalance();
};

template <class T>
void AVLTree<T>::insert(const T& val) {
  super::insert(val);
  rebalance();
}

template <class T>
void AVLTree<T>::remove(const T& val) {
  super::remove(val);
  rebalance();
}

template <class T>
void AVLTree<T>::rebalance() {
  
}

#endif
