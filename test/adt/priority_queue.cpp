#include "PriorityQueue.h"
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

class PriorityQueueTest : public ::testing::Test {
protected:
  PriorityQueue<int> priorityQueue;
  PriorityQueue<TestSortable> priorityQueueObj;

  PriorityQueueTest() {
  }

  virtual ~PriorityQueueTest() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(PriorityQueueTest, Enqueue) {
  priorityQueue.enqueue(1);
  EXPECT_EQ(priorityQueue.length(), 1);
}

TEST_F(PriorityQueueTest, EnqueueObj) {
  priorityQueueObj.enqueue(TestSortable(5));
  EXPECT_EQ(priorityQueueObj.length(), 1);
}

TEST_F(PriorityQueueTest, EnqueueOrder) {
  priorityQueue.enqueue(3);
  priorityQueue.enqueue(2);
  priorityQueue.enqueue(1);
  priorityQueue.enqueue(4);
  EXPECT_EQ(priorityQueue.length(), 4);
  EXPECT_EQ(priorityQueue.peek(), 4);
}

TEST_F(PriorityQueueTest, EnqueueOrderObj) {
  priorityQueueObj.enqueue(TestSortable(3));
  priorityQueueObj.enqueue(TestSortable(2));
  priorityQueueObj.enqueue(TestSortable(1));
  priorityQueueObj.enqueue(TestSortable(4));
  EXPECT_EQ(priorityQueueObj.length(), 4);
  EXPECT_EQ(priorityQueueObj.peek(), TestSortable(4));
}

TEST_F(PriorityQueueTest, Dequeue) {
  priorityQueue.enqueue(1);
  EXPECT_EQ(priorityQueue.dequeue(), 1);
  EXPECT_EQ(priorityQueue.length(), 0);
}

TEST_F(PriorityQueueTest, DequeueOrder) {
  priorityQueue.enqueue(3);
  priorityQueue.enqueue(2);
  priorityQueue.enqueue(2);
  priorityQueue.enqueue(1);
  priorityQueue.enqueue(4);
  EXPECT_EQ(priorityQueue.length(), 5);
  EXPECT_EQ(priorityQueue.dequeue(), 4);
  EXPECT_EQ(priorityQueue.dequeue(), 3);
  EXPECT_EQ(priorityQueue.dequeue(), 2);
  EXPECT_EQ(priorityQueue.dequeue(), 2);
  EXPECT_EQ(priorityQueue.dequeue(), 1);
}

TEST_F(PriorityQueueTest, DequeueOrderObj) {
  priorityQueueObj.enqueue(TestSortable(3));
  priorityQueueObj.enqueue(TestSortable(2));
  priorityQueueObj.enqueue(TestSortable(2));
  priorityQueueObj.enqueue(TestSortable(1));
  priorityQueueObj.enqueue(TestSortable(4));
  EXPECT_EQ(priorityQueueObj.length(), 5);
  EXPECT_EQ(priorityQueueObj.dequeue(), TestSortable(4));
  EXPECT_EQ(priorityQueueObj.dequeue(), TestSortable(3));
  EXPECT_EQ(priorityQueueObj.dequeue(), TestSortable(2));
  EXPECT_EQ(priorityQueueObj.dequeue(), TestSortable(2));
  EXPECT_EQ(priorityQueueObj.dequeue(), TestSortable(1));
}

} // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
