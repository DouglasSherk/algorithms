#ifndef __HASH_TABLE_INCLUDED_
#define __HASH_TABLE_INCLUDED_

#include <cstdlib>
#include <string>
#include <stdexcept>

#include "Vector.h"

#define __HASH_TABLE_DEFAULT_SIZE 100

template <class K, class V>
class HashTable {
public:
  HashTable();
  ~HashTable();

  void set(const K&, const V&);
  const V& get(const K&) const;
  bool has(const K&) const;
  V remove(const K&);
  size_t size() const;

protected:
  struct HashTuple {
    K key;
    V value;
    // Only needed for `find` operations on the outer Vector.
    bool operator ==(const HashTuple& other) const {
      return this->key == other.key;
    }
    HashTuple& operator =(const HashTuple& other) {
      this->key = other.key;
      this->value = other.value;
      return *this;
    }
  };

  void setValue(const K&, const V&);

  void repartitionForSize(size_t);
  void repartition(size_t);

  size_t hash(const K&) const;

  size_t partitions;
  size_t totalElems;
  Vector<HashTuple>* elems;
};

template <class K, class V>
HashTable<K, V>::HashTable()
  : partitions(0),
    totalElems(0),
    elems(NULL) {
  repartitionForSize(0);
}

template <class K, class V>
HashTable<K, V>::~HashTable() {
  delete [] this->elems;
}

template <class K, class V>
size_t HashTable<K, V>::hash(const K& key) const {
  return size_t(key) % this->partitions;
}

template <class K, class V>
void HashTable<K, V>::set(const K& key, const V& value) {
  repartitionForSize(size() + 1);
  setValue(key, value);
}

template <class K, class V>
void HashTable<K, V>::setValue(const K& key, const V& value) {
  size_t hash = this->hash(key);
  Vector<HashTuple>& hashTupleVector = this->elems[hash];

  HashTuple hashTuple({key, value});
  int index = hashTupleVector.find(hashTuple);
  if (index != -1) {
    hashTupleVector[index] = hashTuple;
  } else {
    hashTupleVector.insertBack(hashTuple);
    this->totalElems++;
  }
}

template <class K, class V>
const V& HashTable<K, V>::get(const K& key) const {
  size_t hash = this->hash(key);
  const Vector<HashTuple>& hashTupleVector = this->elems[hash];
  int index = hashTupleVector.find(HashTuple({key, V()}));
  if (index == -1) {
    throw "No element with key";
  }
  return hashTupleVector[index].value;
}

template <class K, class V>
bool HashTable<K, V>::has(const K& key) const {
  size_t hash = this->hash(key);
  const Vector<HashTuple>& hashTupleVector = this->elems[hash];
  return hashTupleVector.find(HashTuple({key, V()})) != -1;
}

template <class K, class V>
V HashTable<K, V>::remove(const K& key) {
  repartitionForSize(size() - 1);

  size_t hash = this->hash(key);
  Vector<HashTuple>& hashTupleVector = this->elems[hash];
  int index = hashTupleVector.find(HashTuple({key, V()}));
  if (index == -1) {
    throw "No element with key";
  }
  this->totalElems--;
  return hashTupleVector.remove(index).value;
}

template <class K, class V>
void HashTable<K, V>::repartitionForSize(size_t size) {
  if (size == 0) {
    repartition(__HASH_TABLE_DEFAULT_SIZE);
  } else if (size <= this->partitions / 10 ||
             size >= this->partitions) {
    repartition(size * 5);
  }
}

template <class K, class V>
void HashTable<K, V>::repartition(size_t partitions) {
  if (partitions < __HASH_TABLE_DEFAULT_SIZE) {
    partitions = __HASH_TABLE_DEFAULT_SIZE;
  }

  if (partitions == this->partitions) {
    return;
  }

  Vector<HashTuple>* oldElems = this->elems;
  size_t oldPartitions = this->partitions;

  this->partitions = partitions;
  this->elems = new Vector<HashTuple>[partitions];
  this->totalElems = 0;

  for (size_t i = 0; i < oldPartitions; i++) {
    for (int j = 0; j < oldElems[i].length(); j++) {
      const HashTuple& tuple = oldElems[i][j];
      setValue(tuple.key, tuple.value);
    }
  }

  delete [] oldElems;
}

template <class K, class V>
size_t HashTable<K, V>::size() const {
  return this->totalElems;
}

#endif
