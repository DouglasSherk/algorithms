#ifndef __BS_TREE_INCLUDED_
#define __BS_TREE_INCLUDED_

#include <cstdlib>
#include <stdexcept>

#include "Pair.h"

template <class T>
class BSTree_iterator;

template <class T>
class BSTree {
public:
  BSTree();
  ~BSTree();

  typedef BSTree_iterator<T> iterator;

  virtual void insert(const T&);
  size_t size() const;
  virtual void remove(const T&);
  iterator find(const T&);
  void clear();
  size_t height() const;

  iterator begin();
  iterator end();

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

    Node(Node*, const T&);

    void swap(Node*);
    void unlink();
    void setRight(Node*);
    void setLeft(Node*);

  protected:
    friend class BSTree_iterator<T>;
  };

  friend class BSTree_iterator<T>;

  // Parent-position pair for traversal.
  typedef Pair<Node*, Node**> Traversal;

  Node* root;

  void deleteSubTree(Node*);
  size_t height(Node*) const;

  Traversal traverseTo(const T&);
  Traversal traverse(Node** (*)(Node*, const T&), Node** = NULL, const T& = T());
  Traversal traverseToReplacement(const Traversal&);
};

template <class T>
class BSTree_iterator
{
public:
  bool operator ==(const BSTree_iterator&) const;
  bool operator !=(const BSTree_iterator&) const;

  T& operator *() const;

  BSTree_iterator& operator ++();

private:
  friend class BSTree<T>;
  // friend class BSTree_const_iterator<T>;

  typename BSTree<T>::Node* node;
  BSTree<T>* bsTree;

  BSTree_iterator(typename BSTree<T>::Node* node, BSTree<T>* bsTree)
    : node(node),
      bsTree(bsTree) {

  }
};

template <class T>
BSTree<T>::Node::Node(Node* parent, const T& value)
  : value(value),
    left(NULL),
    right(NULL),
    parent(parent) {

}

template <class T>
size_t BSTree<T>::Node::size() const {
  size_t size = 1;
  size += left ? left->size() : 0;
  size += right ? right->size() : 0;
  return size;
}

template <class T>
void BSTree<T>::Node::swap(Node* other) {
  Node* curLeft = left, curRight = right;

  if (other->parent) {
    if (other->parent->left == other) {
      other->parent->left = this;
    } else {
      other->parent->right = this;
    }
  }

  if (parent) {
    if (parent->left == this) {
      parent->left = other;
    } else {
      parent->right = other;
    }
  }

  left = other->left;
  right = other->right;

  other->left = curLeft;
  other->right = curRight;
}

template <class T>
void BSTree<T>::Node::unlink() {
  if (!parent) { return; }
  if (parent->left == this) {
    parent->left = NULL;
  } else if (parent->right == this) {
    parent->right = NULL;
  }
}

template <class T>
void BSTree<T>::Node::setRight(Node* other) {
  other->parent = this;
  this->right = other;
}

template <class T>
void BSTree<T>::Node::setLeft(Node* other) {
  other->parent = this;
  this->right = other;
}

template <class T>
BSTree<T>::BSTree()
  : root(NULL) {

}

template <class T>
BSTree<T>::~BSTree() {
  clear();
}

template <class T>
typename BSTree<T>::iterator BSTree<T>::begin() {
  Node* node = root;
  while (node && node->left) {
    node = node->left;
  }
  return iterator(node, this);
}

template <class T>
typename BSTree<T>::iterator BSTree<T>::end() {
  return iterator(NULL, this);
}

template <class T>
typename BSTree<T>::Traversal BSTree<T>::traverseTo(const T& val) {
  return traverse([](Node* node, const T& val) {
    if (node->value == val) { return (Node**)NULL; }
    return &(node->value < val ? node->right : node->left);
  }, NULL, val);
}

template <class T>
typename BSTree<T>::Traversal BSTree<T>::traverse(Node** (*compar)(Node*, const T&), Node** start, const T& val) {
  Node* parent = NULL;
  Node** position = start;
  if (!position) {
    position = &root;
  }

  while (*position) {
    Node** next(compar(*position, val));
    if (!next) { break; }
    parent = *position;
    position = next;
  }

  return Traversal(parent, position);
}

template <class T>
void BSTree<T>::insert(const T& value) {
  Traversal traversal(traverseTo(value));
  *traversal.value = new Node(traversal.key, value);
}

template <class T>
typename BSTree<T>::Traversal BSTree<T>::traverseToReplacement(const Traversal& removeTraversal) {
  Traversal* replacementTraversal;
  if ((*removeTraversal.value)->left) {
    replacementTraversal = new Traversal(traverse([](Node* node, const T& val) {
      if (!node->right) { return (Node**)NULL; }
      return &node->right;
    }, &(*removeTraversal.value)->left));
  } else {
    replacementTraversal = new Traversal(traverse([](Node* node, const T& val) {
      if (!node->left) { return (Node**)NULL; }
      return &node->left;
    }, &(*removeTraversal.value)->right));
  }
  Traversal retVal(*replacementTraversal);
  delete replacementTraversal;
  return retVal;
}

template <class T>
void BSTree<T>::remove(const T& value) {
  Traversal removeTraversal(traverseTo(value));
  if (!*removeTraversal.value) {
    return;
  }

  if ((*removeTraversal.value)->left || (*removeTraversal.value)->right) {
    Traversal replacementTraversal(traverseToReplacement(removeTraversal));

    // (*removeTraversal.value)->parent = (*replacementTraversal.value)->parent;
    (*removeTraversal.value)->value = (*replacementTraversal.value)->value;
    delete *replacementTraversal.value;
    *replacementTraversal.value = NULL;
  } else {
    delete *removeTraversal.value;
    *removeTraversal.value = NULL;
  }
}

template <class T>
typename BSTree<T>::iterator BSTree<T>::find(const T& val) {
  Traversal traversal(traverseTo(val));
  return iterator(*traversal.value, this);
}

template <class T>
void BSTree<T>::deleteSubTree(Node* node) {
  if (node == NULL) { return; }

  deleteSubTree(node->left);
  deleteSubTree(node->right);
  delete node;
}

template <class T>
size_t BSTree<T>::height() const {
  return root ? height(root) : 0;
}

template <class T>
size_t BSTree<T>::height(Node* node) const {
  if (!node) { return 0; }

  size_t leftHeight = height(node->left),
         rightHeight = height(node->right);

  return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

template <class T>
void BSTree<T>::clear() {
  deleteSubTree(root);
  root = NULL;
}

template <class T>
size_t BSTree<T>::size() const {
  return root ? root->size() : 0;
}

template <class T>
bool BSTree_iterator<T>::operator ==(const BSTree_iterator& rhs) const {
  return node == rhs.node;
}

template <class T>
bool BSTree_iterator<T>::operator !=(const BSTree_iterator& rhs) const {
  return !(*this == rhs);
}

template <class T>
T& BSTree_iterator<T>::operator *() const {
  return node->value;
}

template <class T>
BSTree_iterator<T>& BSTree_iterator<T>::operator ++() {
  if (node->right) {
    node = node->right;
    while (node->left) {
      node = node->left;
    }
  } else if (node->parent) {
    auto parent = node->parent;
    while (parent && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    node = parent;
  } else {
    node = NULL;
  }
  return *this;
}

#endif
