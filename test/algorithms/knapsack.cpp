#include "Knapsack.h"
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace {

class KnapsackTest : public ::testing::Test {
 protected:
  Vector<KnapsackItem> items;

  KnapsackTest() {
    KnapsackItem item = {1, 2};
    items.insert(item, 0);
  }

  virtual ~KnapsackTest() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(KnapsackTest, Works) {
  Knapsack::run(items);
}

} // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
