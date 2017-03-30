#include "Queue.h"
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace {

class QueueTest : public ::testing::Test {
 protected:
  Queue<int> queue;

  QueueTest() {
  }

  virtual ~QueueTest() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(QueueTest, Enqueue) {
  queue.enqueue(1);
  EXPECT_EQ(queue.length(), 1);
}

TEST_F(QueueTest, Dequeue) {
  queue.enqueue(1);
  EXPECT_EQ(queue.dequeue(), 1);
  EXPECT_EQ(queue.length(), 0);
}

} // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
