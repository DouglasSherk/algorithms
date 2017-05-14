#include "AVLTree.h"
#include <iostream>
#include <gtest/gtest.h>
#include <cmath>

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
  TestSortable() : TestSortable(10) {

  }
  bool operator > (const TestSortable& other) const {
    return this->series.length() > other.series.length();
  }
  bool operator < (const TestSortable& other) const {
    return this->series.length() < other.series.length();
  }
  bool operator == (const TestSortable& other) const {
    return this->series == other.series;
  }
};

class AVLTreeTest : public ::testing::Test {
protected:
  AVLTree<int> avlTree;
  AVLTree<TestSortable> avlTreeObj;

  AVLTreeTest() {
  }

  virtual ~AVLTreeTest() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(AVLTreeTest, Insert) {
  avlTree.insert(1);
  EXPECT_EQ(avlTree.size(), 1);
}

TEST_F(AVLTreeTest, InsertMany) {
  avlTree.insert(5);
  avlTree.insert(3);
  avlTree.insert(2);
  avlTree.insert(1);
  avlTree.insert(4);
  avlTree.insert(8);
  avlTree.insert(7);
  avlTree.insert(6);
  avlTree.insert(9);
  EXPECT_EQ(avlTree.size(), 9);
}

TEST_F(AVLTreeTest, Remove) {
  avlTree.insert(1);
  avlTree.insert(2);
  avlTree.remove(2);
  EXPECT_EQ(avlTree.size(), 1);
}

TEST_F(AVLTreeTest, RemoveMany) {
  avlTree.insert(5);
  avlTree.insert(3);
  avlTree.insert(2);
  avlTree.insert(1);
  avlTree.insert(4);
  avlTree.insert(8);
  avlTree.insert(7);
  avlTree.insert(6);
  avlTree.insert(9);
  avlTree.remove(3);
  avlTree.remove(1);
  avlTree.remove(8);
  avlTree.remove(6);
  avlTree.remove(5);
  EXPECT_EQ(avlTree.size(), 4);
}

TEST_F(AVLTreeTest, Walk) {
  avlTree.insert(5);
  avlTree.insert(3);
  avlTree.insert(2);
  avlTree.insert(1);
  avlTree.insert(4);
  avlTree.insert(8);
  avlTree.insert(7);
  avlTree.insert(6);
  avlTree.insert(9);
  int i = 0;
  for (auto it : avlTree) {
    if (i >= 10) { break; }
    EXPECT_EQ(it, ++i);
  }
}

TEST_F(AVLTreeTest, Find) {
  avlTree.insert(3);
  avlTree.insert(2);
  avlTree.insert(1);
  EXPECT_EQ(*avlTree.find(2), 2);
}

TEST_F(AVLTreeTest, FindNonExistent) {
  avlTree.insert(3);
  avlTree.insert(2);
  avlTree.insert(1);
  EXPECT_EQ(avlTree.find(4), avlTree.end());
}

TEST_F(AVLTreeTest, HeightChain) {
  avlTree.insert(3);
  avlTree.insert(2);
  avlTree.insert(1);
  EXPECT_LE(avlTree.height(), 3);
}

TEST_F(AVLTreeTest, Height) {
  // Root
  avlTree.insert(5);
  // Left sub-tree
  avlTree.insert(3);
  avlTree.insert(2);
  avlTree.insert(4);
  // Right sub-tree
  avlTree.insert(8);
  avlTree.insert(7);
  avlTree.insert(9);
  EXPECT_LE(avlTree.height(), 3);
  EXPECT_GT(avlTree.height(), 0);
}

TEST_F(AVLTreeTest, HeightLots) {
  int target = 5000;
  for (int i = 0; i < target; i++) {
    avlTree.insert(i);
  }
  EXPECT_GE(avlTree.height(), int(log2(target) + 1));
  EXPECT_LE(avlTree.height(), 2 * int(log2(target) + 1));
}

TEST_F(AVLTreeTest, Destructor) {
  AVLTree<int>* avlTreePtr = new AVLTree<int>();
  int target = 100;
  for (int i = target; i >= (target / 2) + 1; i--) {
    avlTreePtr->insert(target - i);
    avlTreePtr->insert(i);
  }
  delete avlTreePtr;
}

TEST_F(AVLTreeTest, LotsOfInserts) {
  int target = 5000;
  avlTree.insert(target);
  for (int i = target / 2; target - i > 0; i++) {
    avlTree.insert(target + i);
    avlTree.insert(target - i);
  }
  EXPECT_EQ(avlTree.size(), target + 1);
}

TEST_F(AVLTreeTest, FindLots) {
  int target = 1000;
  for (int i = target / 2; target - i >= 0; i++) {
    avlTree.insert(target + i);
    avlTree.insert(target - i);
  }
  EXPECT_EQ(*avlTree.find(target / 2), target / 2);
  EXPECT_EQ(*avlTree.find(target / 3), target / 3);
}

} // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
