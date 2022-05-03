#include "./solutions.h"
#pragma once

class Solver {
  public:
  Solver(Graph* graph, int v) : graph_(graph), n_vehicles_(v) {}
  ~Solver() {};
  virtual Solution Solve(Graph*, std::vector<Vehicle>&) = 0;
  protected:
  Graph* graph_;
  int n_vehicles_;
};
