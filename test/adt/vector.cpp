#include "Vector.h"
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

#define __VECTOR_TEST_OBJ
#define __VECTOR_TEST_PRIMITIVE

namespace {

struct TestStub {
  int a;
  int b;
  bool operator ==(const TestStub& other) const {
    return this->a == other.a && this->b == other.b;
  }
};

class VectorTest : public ::testing::Test {
 protected:
  Vector<int> vector;
  Vector<TestStub> vectorObj;

  VectorTest() {
  }

  virtual ~VectorTest() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

#ifdef __VECTOR_TEST_PRIMITIVE
TEST_F(VectorTest, CopyCtor) {
  vector.insert(1, 0);
  Vector<int> other(vector);
  EXPECT_EQ(other[0], 1);
  EXPECT_EQ(other.length(), 1);
}
#endif

#ifdef __VECTOR_TEST_OBJ
TEST_F(VectorTest, CopyCtorObj) {
  vectorObj.insert({1, 1}, 0);
  Vector<TestStub> other(vectorObj);
  EXPECT_EQ(other[0], TestStub({1, 1}));
  EXPECT_EQ(other.length(), 1);
}
#endif

#ifdef __VECTOR_TEST_PRIMITIVE
TEST_F(VectorTest, CopyCtorMany) {
  for (int i = 0; i < 99; i++) {
    vector.insert(i, i);
  }
  Vector<int> other(vector);
  EXPECT_EQ(other.length(), 99);
  for (int i = 0; i < 99; i++) {
    EXPECT_EQ(other[i], i);
  }
}
#endif

#ifdef __VECTOR_TEST_OBJ
TEST_F(VectorTest, CopyCtorManyObj) {
  for (int i = 0; i < 99; i++) {
    vectorObj.insert({i, i}, i);
  }
  Vector<TestStub> other(vectorObj);
  EXPECT_EQ(other.length(), 99);
  for (int i = 0; i < 99; i++) {
    EXPECT_EQ(other[i], TestStub({i, i}));
  }
}
#endif

#ifdef __VECTOR_TEST_PRIMITIVE
TEST_F(VectorTest, EqualityOper) {
  vector.insert(1, 0);
  Vector<int> other;
  other.insert(1, 0);
  EXPECT_EQ(vector, other);
}

TEST_F(VectorTest, AssignOperLarger) {
  vector.insert(1, 0);
  vector.insert(2, 1);
  Vector<int> other;
  other = vector;
  EXPECT_EQ(vector, other);
  EXPECT_EQ(other.length(), 2);
}
#endif

#ifdef __VECTOR_TEST_OBJ
TEST_F(VectorTest, AssignOperLargerObj) {
  vectorObj.insert({1, 1}, 0);
  vectorObj.insert({2, 2}, 1);
  Vector<TestStub> other;
  other = vectorObj;
  EXPECT_EQ(other[0], TestStub({1, 1}));
  EXPECT_EQ(other[1], TestStub({2, 2}));
  EXPECT_EQ(other.length(), 2);
}
#endif

#ifdef __VECTOR_TEST_PRIMITIVE
TEST_F(VectorTest, AssignOperSmaller) {
  vector.insert(1, 0);
  vector.insert(2, 1);
  Vector<int> other;
  vector = other;
  EXPECT_EQ(vector, other);
  EXPECT_EQ(vector.length(), 0);
}
#endif

#ifdef __VECTOR_TEST_OBJ
TEST_F(VectorTest, AssignOperSmallerObj) {
  vectorObj.insert({1, 1}, 0);
  vectorObj.insert({2, 2}, 1);
  Vector<TestStub> other;
  vectorObj = other;
  EXPECT_EQ(vectorObj.length(), 0);
}
#endif

#ifdef __VECTOR_TEST_PRIMITIVE
TEST_F(VectorTest, ImmutableBracketOper) {
  vector.insert(1, 0);
  EXPECT_EQ(vector[0], 1);
}

TEST_F(VectorTest, MutableBracketOper) {
  vector.insert(1, 0);
  vector[0] = 2;
  EXPECT_EQ(vector[0], 2);
}

TEST_F(VectorTest, Insert) {
  vector.insert(1, 0);
  EXPECT_EQ(vector.length(), 1);
}

TEST_F(VectorTest, InsertIntoFrontMany) {
  for (int i = 0; i < 99; i++) {
    vector.insert(i, 0);
  }
  EXPECT_EQ(vector.length(), 99);
  for (int i = 0; i < 99; i++) {
    EXPECT_EQ(vector[i], 99 - i - 1);
  }
}

TEST_F(VectorTest, InsertIntoBackMany) {
  for (int i = 0; i < 99; i++) {
    vector.insert(i, i);
  }
  EXPECT_EQ(vector.length(), 99);
  for (int i = 0; i < 99; i++) {
    EXPECT_EQ(vector[i], i);
  }
}

TEST_F(VectorTest, InsertFrontMany) {
  for (int i = 0; i < 99; i++) {
    vector.insertFront(i);
  }
  EXPECT_EQ(vector.length(), 99);
  for (int i = 0; i < 99; i++) {
    EXPECT_EQ(vector[i], 99 - i - 1);
  }
}

TEST_F(VectorTest, InsertBackMany) {
  for (int i = 0; i < 99; i++) {
    vector.insertBack(i);
  }
  EXPECT_EQ(vector.length(), 99);
  for (int i = 0; i < 99; i++) {
    EXPECT_EQ(vector[i], i);
  }
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

TEST_F(VectorTest, PreservesData) {
  for (int i = 0; i < 99; i++) {
    vector.insert(i, i);
  }
  for (int i = 0; i < 94; i++) {
    vector.remove(0);
  }

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(vector[i], 94 + i);
  }
}

TEST_F(VectorTest, CopyElement) {
  vector.insert(1, 0);
  vector.insert(2, 1);
  Vector<int> other;
  other.insert(vector.remove(0), 0);
  EXPECT_EQ(vector.length(), 1);
  EXPECT_EQ(other.length(), 1);
  EXPECT_EQ(vector[0], 2);
  EXPECT_EQ(other[0], 1);
}

TEST_F(VectorTest, CopyElementMany) {
  for (int i = 0; i < 99; i++) {
    vector.insert(i, i);
  }
  Vector<int> other;
  for (int i = 0; i < 94; i++) {
    other.insert(vector.remove(0), i);
  }

  for (int i = 0; i < 94; i++) {
    EXPECT_EQ(other[i], i);
  }
}
#endif // __VECTOR_TEST_PRIMITIVE

} // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
