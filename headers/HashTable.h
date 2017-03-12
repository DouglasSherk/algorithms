#include <cstdlib>
#include <string>
#include <stdexcept>

template <class T>
class HashTable {
private:
  T * elems;
  size_t size;

protected:
  // void resolveConflict();
  // void shouldExpandMemory();
  size_t hash(const char*);

public:
  HashTable();
  ~HashTable();

  void set(const char*, const T&);
  T get(const char*);
};

template <class T>
HashTable<T>::HashTable() {
  this->elems = new T[100];
  this->size = 100;
}

template <class T>
HashTable<T>::~HashTable() {
  delete [] this->elems;
}

template <class T>
size_t HashTable<T>::hash(const char* key) {
  size_t hash = 0;
  size_t len = strlen(key);

  for (size_t i = 0; i < len; i++) {
    hash += key[i];
  }

  // TODO: Check if we should expand the memory or put it into a better spot.
  if (hash >= this->size) {
    hash %= this->size;
  }

  return hash;
}

template <class T>
void HashTable<T>::set(const char* key, T const& elem) {
  size_t hash = this->hash(key);
  this->elems[hash] = elem;
}

template <class T>
T HashTable<T>::get(const char* key) {
  size_t hash = this->hash(key);
  return this->elems[hash];
}
