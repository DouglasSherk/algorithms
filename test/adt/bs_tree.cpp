#include "BSTree.h"
#include <iostream>
#include <gtest/gtest.h>

#include "Vector.h"

using namespace std;

namespace {

struct TestSortable {
  Vector<int> series;
  TestSortable(int size) {
    for (int i = 0; i < size; i++) {
      series.insertBack(i);
    }
  }
  bool operator > (const TestSortable& other) const {
    return this->series.length() > other.series.length();
  }
  bool operator == (const TestSortable& other) const {
    return this->series == other.series;
  }
};

class BSTreeTest : public ::testing::Test {
protected:
  BSTree<int> bsTree;
  BSTree<TestSortable> bsTreeObj;

  BSTreeTest() {
  }

  virtual ~BSTreeTest() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(BSTreeTest, Insert) {
  bsTree.insert(1);
  EXPECT_EQ(bsTree.size(), 1);
}

TEST_F(BSTreeTest, InsertMany) {
  bsTree.insert(5);
  bsTree.insert(3);
  bsTree.insert(2);
  bsTree.insert(1);
  bsTree.insert(4);
  bsTree.insert(8);
  bsTree.insert(7);
  bsTree.insert(6);
  bsTree.insert(9);
  EXPECT_EQ(bsTree.size(), 9);
}

TEST_F(BSTreeTest, Remove) {
  bsTree.insert(1);
  bsTree.insert(2);
  bsTree.remove(2);
  EXPECT_EQ(bsTree.size(), 1);
}

TEST_F(BSTreeTest, RemoveMany) {
  bsTree.insert(5);
  bsTree.insert(3);
  bsTree.insert(2);
  bsTree.insert(1);
  bsTree.insert(4);
  bsTree.insert(8);
  bsTree.insert(7);
  bsTree.insert(6);
  bsTree.insert(9);
  bsTree.remove(3);
  bsTree.remove(1);
  bsTree.remove(8);
  bsTree.remove(6);
  bsTree.remove(5);
  EXPECT_EQ(bsTree.size(), 4);
}

TEST_F(BSTreeTest, Walk) {
  bsTree.insert(5);
  bsTree.insert(3);
  bsTree.insert(2);
  bsTree.insert(1);
  bsTree.insert(4);
  bsTree.insert(8);
  bsTree.insert(7);
  bsTree.insert(6);
  bsTree.insert(9);
  int i = 0;
  for (auto it : bsTree) {
    EXPECT_EQ(it, ++i);
  }
}

TEST_F(BSTreeTest, Find) {
  bsTree.insert(3);
  bsTree.insert(2);
  bsTree.insert(1);
  EXPECT_EQ(*bsTree.find(2), 2);
}

TEST_F(BSTreeTest, FindNonExistent) {
  bsTree.insert(3);
  bsTree.insert(2);
  bsTree.insert(1);
  EXPECT_EQ(bsTree.find(4), bsTree.end());
}

TEST_F(BSTreeTest, Destructor) {
  BSTree<int>* bsTreePtr = new BSTree<int>();
  int target = 100;
  for (int i = target; i >= (target / 2) + 1; i--) {
    bsTreePtr->insert(target - i);
    bsTreePtr->insert(i);
  }
  delete bsTreePtr;
}

TEST_F(BSTreeTest, LotsOfInserts) {
  int target = 5000;
  bsTree.insert(target);
  for (int i = target / 2; target - i > 0; i++) {
    bsTree.insert(target + i);
    bsTree.insert(target - i);
  }
  EXPECT_EQ(bsTree.size(), target + 1);
}

TEST_F(BSTreeTest, FindLots) {
  int target = 1000;
  for (int i = target / 2; target - i >= 0; i++) {
    bsTree.insert(target + i);
    bsTree.insert(target - i);
  }
  EXPECT_EQ(*bsTree.find(target / 2), target / 2);
  EXPECT_EQ(*bsTree.find(target / 3), target / 3);
}

} // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
