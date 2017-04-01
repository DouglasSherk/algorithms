#include "Knapsack.h"
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace {

class KnapsackTest : public ::testing::Test {
 protected:
  Vector<KnapsackItem> items;

  KnapsackTest() {
  }

  virtual ~KnapsackTest() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(KnapsackTest, OneItem) {
  items.insert(KnapsackItem({1, 1}), 0);
  Knapsack knapsack(1, items);
  EXPECT_EQ(knapsack.getItems().length(), 1);
  EXPECT_EQ(knapsack.getWeight(), 1);
  EXPECT_EQ(knapsack.getValue(), 1);
}

TEST_F(KnapsackTest, TwoItems) {
  items.insert(KnapsackItem({1, 1}), 0);
  items.insert(KnapsackItem({2, 2}), 1);
  Knapsack knapsack(3, items);

  EXPECT_EQ(knapsack.getItems().length(), 2);
  EXPECT_EQ(knapsack.getWeight(), 3);
  EXPECT_EQ(knapsack.getValue(), 3);
}

TEST_F(KnapsackTest, ThreeItems) {
  items.insert(KnapsackItem({1, 1}), 0);
  items.insert(KnapsackItem({1, 1}), 0);
  items.insert(KnapsackItem({1, 1}), 0);
  Knapsack knapsack(3, items);
  EXPECT_EQ(knapsack.getItems().length(), 3);
  EXPECT_EQ(knapsack.getWeight(), 3);
  EXPECT_EQ(knapsack.getValue(), 3);
}

TEST_F(KnapsackTest, ThreeItemsTwoSelected) {
  items.insert(KnapsackItem({5, 3}), 0);
  items.insert(KnapsackItem({4, 3}), 0);
  items.insert(KnapsackItem({2, 3}), 0);
  Knapsack knapsack(6, items);
  EXPECT_EQ(knapsack.getItems().length(), 2);
  EXPECT_EQ(knapsack.getWeight(), 6);
  EXPECT_EQ(knapsack.getValue(), 6);
}

TEST_F(KnapsackTest, FourItemsThreeSelected) {
  items.insert(KnapsackItem({5, 3}), 0);
  items.insert(KnapsackItem({4, 3}), 0);
  items.insert(KnapsackItem({2, 3}), 0);
  items.insert(KnapsackItem({1, 3}), 0);
  Knapsack knapsack(7, items);
  EXPECT_EQ(knapsack.getItems().length(), 3);
  EXPECT_EQ(knapsack.getWeight(), 7);
  EXPECT_EQ(knapsack.getValue(), 9);
}

TEST_F(KnapsackTest, FourItemsThreeSelectedExcessCapacity) {
  items.insert(KnapsackItem({5, 3}), 0);
  items.insert(KnapsackItem({4, 3}), 0);
  items.insert(KnapsackItem({2, 3}), 0);
  items.insert(KnapsackItem({1, 3}), 0);
  Knapsack knapsack(8, items);
  EXPECT_EQ(knapsack.getItems().length(), 3);
  EXPECT_EQ(knapsack.getWeight(), 7);
  EXPECT_EQ(knapsack.getValue(), 9);
}

TEST_F(KnapsackTest, ManyItems) {
  int count = 8;
  for (int i = 0; i < count; i++) {
    items.insert(KnapsackItem({1, 1}), 0);
  }
  Knapsack knapsack(count, items);
  EXPECT_EQ(knapsack.getItems().length(), count);
  EXPECT_EQ(knapsack.getWeight(), count);
  EXPECT_EQ(knapsack.getValue(), count);
}

TEST_F(KnapsackTest, ManyItemsHalfSelected) {
  int count = 8;
  for (int i = 0; i < count; i++) {
    items.insert(KnapsackItem({1, 1}), 0);
  }
  Knapsack knapsack(count / 2, items);
  EXPECT_EQ(knapsack.getItems().length(), count / 2);
  EXPECT_EQ(knapsack.getWeight(), count / 2);
  EXPECT_EQ(knapsack.getValue(), count / 2);
}

} // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
