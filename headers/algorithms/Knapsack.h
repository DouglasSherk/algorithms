#ifndef __KNAPSACK_INCLUDED_
#define __KNAPSACK_INCLUDED_

#include <cstdlib>
#include <string>
#include <stdexcept>

#include "Vector.h"
#include "HashTable.h"

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
  struct KnapsackTuple {
    Vector<KnapsackItem> items;
    Vector<KnapsackItem> selected;
    bool operator ==(const KnapsackTuple& other) const {
      return this->items == other.items && this->selected == other.selected;
    }
    operator size_t() const {
      return this->items.length() * 100000 + this->selected.length();
    }
  };

  Vector<KnapsackItem> run(const Vector<KnapsackItem>&, const Vector<KnapsackItem>& = Vector<KnapsackItem>());
  Vector<KnapsackItem> getCache(const Vector<KnapsackItem>&, const Vector<KnapsackItem>&);
  int totalWeight(const Vector<KnapsackItem>&) const;
  int totalValue(const Vector<KnapsackItem>&) const;

  int capacity;
  Vector<KnapsackItem> items;
  Vector<KnapsackItem> selected;
  HashTable<KnapsackTuple, Vector<KnapsackItem>> cache;
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

// The cache gives very significant performance improvements. Without it, even
// selecting from 10 items takes several seconds.
Vector<KnapsackItem> Knapsack::getCache(const Vector<KnapsackItem>& items,
                                        const Vector<KnapsackItem>& selected) {
  const KnapsackTuple knapsackTuple({items, selected});
  if (this->cache.has(knapsackTuple)) {
    return this->cache.get(knapsackTuple);
  }
  Vector<KnapsackItem> selectedPrime = run(items, selected);
  this->cache.set(knapsackTuple, selectedPrime);
  return selectedPrime;
}

Vector<KnapsackItem> Knapsack::run(const Vector<KnapsackItem>& items,
                                   const Vector<KnapsackItem>& selected) {
  Vector<KnapsackItem> bestSelected(selected);
  for (int i = 0; i < items.length(); i++) {
    Vector<KnapsackItem> itemsPrime(items);
    Vector<KnapsackItem> selectedPrime(selected);
    selectedPrime.insert(itemsPrime.remove(i), 0);
    if (totalWeight(selectedPrime) > capacity) {
      continue;
    }
    Vector<KnapsackItem> selectedPrimePrime = getCache(itemsPrime, selectedPrime);
    if (totalValue(selectedPrimePrime) > totalValue(bestSelected)) {
      bestSelected = selectedPrimePrime;
    }
  }
  return bestSelected;
}

#endif
