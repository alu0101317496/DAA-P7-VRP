#include "../LocalSearch.h"
#pragma once
class OPT2 : public LocalSearch {
  public:
  OPT2(Graph* graph, int);
  ~OPT2();
  
  void SolveLocal(std::vector<Vehicle>&, Solution&);
  
  private:
  void OPT2Swap(Vehicle&, int, int);
  void RecalculateCost(std::vector<Vehicle>&);
};
