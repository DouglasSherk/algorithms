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

} // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
