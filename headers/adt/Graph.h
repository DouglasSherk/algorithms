#ifndef __GRAPH_INCLUDED_
#define __GRAPH_INCLUDED_

#include <cstdlib>
#include <string>
#include <stdexcept>

class GraphNode {
public:
protected:
  virtual int distance(const GraphNode& other) = 0;
};

template <class T>
class Graph {
public:
  Graph();
  ~Graph();
};

#endif
