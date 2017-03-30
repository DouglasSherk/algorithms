#include "List.h"
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace {

class ListTest : public ::testing::Test {
 protected:
  List<int> list;

  ListTest() {
    list.insertBack(1);
    list.insertBack(3);
  }

  virtual ~ListTest() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(ListTest, InsertFront) {
  list.insertFront(2);
  EXPECT_EQ(list.getAt(0), 2);
  EXPECT_EQ(list.getAt(1), 1);
  EXPECT_EQ(list.length(), 3);
}

TEST_F(ListTest, InsertBack) {
  EXPECT_EQ(list.getAt(0), 1);
  EXPECT_EQ(list.getAt(1), 3);
  EXPECT_EQ(list.length(), 2);
}

TEST_F(ListTest, InsertAt) {
  list.insertAt(2, 1);
  EXPECT_EQ(list.getAt(0), 1);
  EXPECT_EQ(list.getAt(1), 2);
  EXPECT_EQ(list.getAt(2), 3);
  EXPECT_EQ(list.length(), 3);
}

TEST_F(ListTest, RemoveAt) {
  list.removeAt(0);
  EXPECT_EQ(list.getAt(0), 3);
  EXPECT_EQ(list.length(), 1);
}

TEST_F(ListTest, Remove) {
  list.remove(3);
  EXPECT_EQ(list.getAt(0), 1);
  EXPECT_EQ(list.length(), 1);
}

TEST_F(ListTest, RemoveFront) {
  list.removeFront();
  EXPECT_EQ(list.getAt(0), 3);
  EXPECT_EQ(list.length(), 1);
}

TEST_F(ListTest, RemoveBack) {
  list.removeBack();
  EXPECT_EQ(list.getAt(0), 1);
  EXPECT_EQ(list.length(), 1);
}

TEST_F(ListTest, GetAt) {
  EXPECT_EQ(list.getAt(0), 1);
}

TEST_F(ListTest, IndexOf) {
  EXPECT_EQ(list.indexOf(3), 1);
}

TEST_F(ListTest, Front) {
  EXPECT_EQ(list.front(), 1);
}

TEST_F(ListTest, Back) {
  EXPECT_EQ(list.back(), 3);
}

TEST_F(ListTest, Length) {
  EXPECT_EQ(list.length(), 2);
}

TEST_F(ListTest, AddRemoveLotsOfElements) {
  list.removeBack();
  list.removeFront();
  list.insertFront(3);
  list.insertBack(2);
  list.insertFront(1);
  list.removeFront();
  list.removeFront();
  EXPECT_EQ(list.getAt(0), 2);
  EXPECT_EQ(list.length(), 1);
}

} // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
