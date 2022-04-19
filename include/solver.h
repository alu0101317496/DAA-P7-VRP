#include "graph.h"
#pragma once

class Solver {
public:
  Solver() {}
  ~Solver() {};
  virtual void Solve(Graph*, std::vector<Vehicle>&) = 0;

};
