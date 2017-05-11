#ifndef __PAIR_INCLUDED_
#define __PAIR_INCLUDED_

#include <cstdlib>
#include <string>
#include <stdexcept>

template <class A, class B>
struct Pair {
public:
  A a;
  B b;
};

#endif
