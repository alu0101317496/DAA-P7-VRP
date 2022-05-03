/* date = April 30th 2022 1:38 pm */
#include "../solver.h"

#ifndef _LOCAL_SEARCH_H
#define _LOCAL_SEARCH_H

struct Pair {
  int cost_for_1;
  int cost_for_2;
};

class LocalSearch {
  public:  
  LocalSearch(Graph*, int);
  ~LocalSearch();
  virtual void SolveLocal(std::vector<Vehicle>&, Solution&) = 0;
  void VisualizeGraph();
  bool UpdateLocalSolution(Solution&, Solution&);
  
  protected:
  Graph* graph_;
  int n_vehicles_;
};

#endif //_LOCAL_SEARCH_H
