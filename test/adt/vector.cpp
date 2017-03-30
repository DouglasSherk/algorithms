#include "Vector.h"
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace {

class VectorTest : public ::testing::Test {
 protected:
  Vector<int> vector;

  VectorTest() {
  }

  virtual ~VectorTest() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(VectorTest, Insert) {
  vector.insert(1, 0);
  EXPECT_EQ(vector.length(), 1);
}

TEST_F(VectorTest, Remove) {
  vector.insert(1, 0);
  vector.remove(0);
  EXPECT_EQ(vector.length(), 0);
}

TEST_F(VectorTest, Resize) {
  vector.resize(8);
  EXPECT_EQ(vector.length(), 8);
}

TEST_F(VectorTest, Capacity) {
  int length = 8;
  vector.resize(length);
  EXPECT_GT(vector.capacity(), length);
  EXPECT_LE(vector.capacity(), length * 2);
}

TEST_F(VectorTest, Clear) {
  vector.resize(8);
  vector.clear();
  EXPECT_EQ(vector.length(), 0);
  EXPECT_GT(vector.capacity(), 0);
}

TEST_F(VectorTest, Find) {
  vector.insert(1, 0);
  vector.insert(2, 1);
  vector.insert(3, 2);
  EXPECT_EQ(vector.find(2), 1);
}

TEST_F(VectorTest, FindNone) {
  vector.insert(1, 0);
  vector.insert(2, 1);
  vector.insert(3, 2);
  EXPECT_EQ(vector.find(4), -1);
}

TEST_F(VectorTest, AutoResizingCapacity) {
  int length = 9999;
  for (int i = 0; i < length; i++) {
    vector.insert(i, i);
  }
  EXPECT_EQ(vector.length(), length);
  EXPECT_GT(vector.capacity(), length);
  EXPECT_LE(vector.capacity(), length * 2);
}

TEST_F(VectorTest, AutoResizeDown) {
  int length = 9999;
  for (int i = 0; i < length; i++) {
    vector.insert(i, i);
  }
  while (vector.length()) {
    vector.remove(0);
  }
  EXPECT_EQ(vector.length(), 0);
  EXPECT_GT(vector.capacity(), 0);
}

TEST_F(VectorTest, AutoResizeAtZero) {
  vector.resize(0);
  for (int i = 0; i < 99; i++) {
    vector.insert(1, 0);
    vector.remove(0);
  }
  EXPECT_EQ(vector.length(), 0);
  EXPECT_GT(vector.capacity(), 0);
}

TEST_F(VectorTest, ResizeZeroes) {
  vector.resize(8);
  for (int i = 0; i < vector.length(); i++) {
    EXPECT_EQ(vector[i], 0);
  }
}

} // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
