#include "HashTable.h"
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace {

struct TestTuple {
  int a;
  int b;
  operator size_t() const {
    return a * 100000 + b;
  }
  bool operator ==(const TestTuple& other) const {
    return this->a == other.a && this->b == other.b;
  }
};

class HashTableTest : public ::testing::Test {
 protected:
  HashTable<int, int> hashTable;
  HashTable<TestTuple, TestTuple> hashTableObj;

  HashTableTest() {
  }

  virtual ~HashTableTest() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(HashTableTest, Set) {
  hashTable.set(1, 1);
  EXPECT_EQ(hashTable.size(), 1);
}

TEST_F(HashTableTest, SetObj) {
  TestTuple testTuple({1, 1});
  hashTableObj.set(testTuple, testTuple);
  EXPECT_EQ(hashTableObj.size(), 1);
}

TEST_F(HashTableTest, Get) {
  hashTable.set(1, 1);
  EXPECT_EQ(hashTable.get(1), 1);
}

TEST_F(HashTableTest, Has) {
  hashTable.set(1, 1);
  EXPECT_EQ(hashTable.has(1), true);
}

TEST_F(HashTableTest, Hasnt) {
  hashTable.set(1, 1);
  EXPECT_EQ(hashTable.has(2), false);
}

TEST_F(HashTableTest, HasObj) {
  TestTuple testTuple({1, 1});
  hashTableObj.set(testTuple, testTuple);
  EXPECT_EQ(hashTableObj.has(testTuple), true);
}

TEST_F(HashTableTest, HasntObj) {
  TestTuple testTuple({1, 1});
  hashTableObj.set(testTuple, testTuple);
  EXPECT_EQ(hashTableObj.has(TestTuple({2, 2})), false);
}

TEST_F(HashTableTest, GetObj) {
  TestTuple testTuple({1, 1});
  hashTableObj.set(testTuple, testTuple);
  EXPECT_EQ(hashTableObj.get(testTuple), testTuple);
}

TEST_F(HashTableTest, Remove) {
  hashTable.set(1, 1);
  hashTable.remove(1);
  EXPECT_EQ(hashTable.size(), 0);
}

TEST_F(HashTableTest, RemoveObj) {
  TestTuple testTuple({1, 1});
  hashTableObj.set(testTuple, testTuple);
  hashTableObj.remove(testTuple);
  EXPECT_EQ(hashTableObj.size(), 0);
}

TEST_F(HashTableTest, SetMany) {
  for (int i = 0; i < 1000; i++) {
    hashTable.set(i, i);
  }
  EXPECT_EQ(hashTable.size(), 1000);
  for (int i = 0; i < 1000; i++) {
    EXPECT_EQ(hashTable.get(i), i);
  }
}

TEST_F(HashTableTest, SetManyObj) {
  for (int i = 0; i < 1000; i++) {
    TestTuple testTuple({i, i});
    hashTableObj.set(testTuple, testTuple);
  }
  EXPECT_EQ(hashTableObj.size(), 1000);
  for (int i = 0; i < 1000; i++) {
    TestTuple testTuple({i, i});
    EXPECT_EQ(hashTableObj.get(testTuple), testTuple);
  }
}

TEST_F(HashTableTest, RemoveMany) {
  for (int i = 0; i < 1000; i++) {
    hashTable.set(i, i);
  }
  for (int i = 0; i < 1000; i++) {
    hashTable.remove(i);
  }
  EXPECT_EQ(hashTable.size(), 0);
}

TEST_F(HashTableTest, RemoveManyObj) {
  for (int i = 0; i < 1000; i++) {
    TestTuple testTuple({i, i});
    hashTableObj.set(testTuple, testTuple);
  }
  for (int i = 0; i < 1000; i++) {
    TestTuple testTuple({i, i});
    hashTableObj.remove(testTuple);
  }
  EXPECT_EQ(hashTableObj.size(), 0);
}

TEST_F(HashTableTest, Tuple) {
  HashTable<size_t, Vector<size_t>> hashTableObjObj;
  Vector<size_t> values;
  values.insertBack(1);
  values.insertBack(2);
  hashTableObjObj.set(1, values);
  EXPECT_EQ(hashTableObjObj.size(), 1);
  EXPECT_EQ(hashTableObjObj.get(1), values);
}

TEST_F(HashTableTest, TupleTuple) {
  struct TestTupleTuple {
    Vector<TestTuple> keys;
    Vector<TestTuple> values;
    operator size_t() const {
      return keys.length() * 10000 + values.length();
    }
    bool operator ==(const TestTupleTuple& other) const {
      return this->keys == other.keys && this->values == other.values;
    }
  };

  HashTable<TestTupleTuple, Vector<TestTuple>> hashTableObjObj;
  Vector<TestTuple> keys, values;
  keys.insertBack({1, 1});
  keys.insertBack({2, 2});
  values.insertBack({1, 1});
  values.insertBack({2, 2});
  TestTupleTuple testTupleTuple({keys, values});
  hashTableObjObj.set(testTupleTuple, values);
  EXPECT_EQ(hashTableObjObj.size(), 1);
  EXPECT_EQ(hashTableObjObj.get(testTupleTuple), values);
}

} // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
