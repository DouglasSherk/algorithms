#ifndef __KNAPSACK_INCLUDED_
#define __KNAPSACK_INCLUDED_

#include <cstdlib>
#include <string>
#include <stdexcept>

#include "Vector.h"

using namespace std;

struct KnapsackItem {
public:
  int weight;
  int value;
  bool operator ==(const KnapsackItem& other) const {
    return this->weight == other.weight && this->value == other.value;
  }
};

class Knapsack {
public:
  Knapsack(int, const Vector<KnapsackItem>&);
  const Vector<KnapsackItem>& getItems() const;
  int getValue() const;
  int getWeight() const;

private:
  Vector<KnapsackItem> run(const Vector<KnapsackItem>&, const Vector<KnapsackItem>& = Vector<KnapsackItem>(), int = 0);
  int totalWeight(const Vector<KnapsackItem>&) const;
  int totalValue(const Vector<KnapsackItem>&) const;

  int capacity;
  Vector<KnapsackItem> items;
  Vector<KnapsackItem> selected;
};

Knapsack::Knapsack(int capacity,
                   const Vector<KnapsackItem>& items)
  : capacity(capacity),
    items(items) {
  this->selected = run(items);
}

const Vector<KnapsackItem>& Knapsack::getItems() const {
  return selected;
}

int Knapsack::getValue() const {
  return totalValue(this->selected);
}

int Knapsack::getWeight() const {
  return totalWeight(this->selected);
}

int Knapsack::totalWeight(const Vector<KnapsackItem>& items) const {
  int totalWeight = 0;
  for (int i = 0; i < items.length(); i++) {
    totalWeight += items[i].weight;
  }
  return totalWeight;
}

int Knapsack::totalValue(const Vector<KnapsackItem>& items) const {
  int totalValue = 0;
  for (int i = 0; i < items.length(); i++) {
    totalValue += items[i].value;
  }
  return totalValue;
}

Vector<KnapsackItem> Knapsack::run(const Vector<KnapsackItem>& items,
                                   const Vector<KnapsackItem>& selected,
                                   int depth) {
  Vector<KnapsackItem> bestSelected(selected);
  for (int i = 0; i < items.length(); i++) {
    Vector<KnapsackItem> itemsPrime(items);
    Vector<KnapsackItem> selectedPrime(selected);
    selectedPrime.insert(itemsPrime.remove(i), 0);
    if (totalWeight(selectedPrime) > capacity) {
      continue;
    }
    Vector<KnapsackItem> selectedPrimePrime = run(itemsPrime, selectedPrime, depth + 1);
    if (totalValue(selectedPrimePrime) > totalValue(bestSelected)) {
      bestSelected = selectedPrimePrime;
    }
  }
  return bestSelected;
}

#endif
