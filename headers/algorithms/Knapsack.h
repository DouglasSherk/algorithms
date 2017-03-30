#ifndef __KNAPSACK_INCLUDED_
#define __KNAPSACK_INCLUDED_

#include <cstdlib>
#include <string>
#include <stdexcept>

#include "Vector.h"

struct KnapsackItem {
public:
  int weight;
  int value;
};

class Knapsack {
public:
  static const Vector<KnapsackItem>& run(const Vector<KnapsackItem>&);
private:
  static const Vector<KnapsackItem>& inner(const Vector<KnapsackItem>&, const Vector<KnapsackItem>&);
};

const Vector<KnapsackItem>& Knapsack::run(const Vector<KnapsackItem>& items) {
  for (int i = 0; i < items.length(); i++) {
    Vector<KnapsackItem> items_prime(items);
    Vector<KnapsackItem> selected;
    // selected.insert(items_prime.remove(i), 0);
    // inner(items_prime, selected);
  }
  return items;
}

const Vector<KnapsackItem>& Knapsack::inner(const Vector<KnapsackItem>& items,
                                            const Vector<KnapsackItem>& selected) {
  return items;
}

#endif
