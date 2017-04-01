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
  HashTable<TestTuple, int> hashTableObj;

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
  hashTableObj.set(TestTuple({1, 1}), 1);
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
  hashTableObj.set(TestTuple({1, 1}), 1);
  EXPECT_EQ(hashTableObj.has(TestTuple({1, 1})), true);
}

TEST_F(HashTableTest, HasntObj) {
  hashTableObj.set(TestTuple({1, 1}), 1);
  EXPECT_EQ(hashTableObj.has(TestTuple({2, 2})), false);
}

TEST_F(HashTableTest, GetObj) {
  hashTableObj.set(TestTuple({1, 1}), 1);
  EXPECT_EQ(hashTableObj.get(TestTuple({1, 1})), 1);
}

TEST_F(HashTableTest, Remove) {
  hashTable.set(1, 1);
  hashTable.remove(1);
  EXPECT_EQ(hashTable.size(), 0);
}

TEST_F(HashTableTest, RemoveObj) {
  hashTableObj.set(TestTuple({1, 1}), 1);
  hashTableObj.remove(TestTuple({1, 1}));
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
    hashTableObj.set(TestTuple({i, i}), i);
  }
  EXPECT_EQ(hashTableObj.size(), 1000);
  for (int i = 0; i < 1000; i++) {
    EXPECT_EQ(hashTableObj.get(TestTuple({i, i})), i);
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
    hashTableObj.set(TestTuple({i, i}), i);
  }
  for (int i = 0; i < 1000; i++) {
    hashTableObj.remove(TestTuple({i, i}));
  }
  EXPECT_EQ(hashTableObj.size(), 0);
}

} // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
