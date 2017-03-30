#include "HashTable.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  HashTable<int> hashTable;
  hashTable.set("asdf", 3);
  cout << hashTable.get("asdf") << endl;
  // TODO: Add error handling for unset key-value pairs.
  cout << hashTable.get("dane") << endl;

  return 0;
}