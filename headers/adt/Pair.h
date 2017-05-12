#ifndef __PAIR_INCLUDED_
#define __PAIR_INCLUDED_

#include <cstdlib>
#include <string>
#include <stdexcept>

template <class K, class V>
class Pair {
public:
  K key;
  V value;
  bool operator ==(const Pair& other) const {
    return this->key == other.key;
  }
  Pair& operator =(const Pair& other) {
    this->key = other.key;
    this->value = other.value;
    return *this;
  }
  Pair(K k, V v)
    : key(k),
      value(v) {

  }
};

#endif
