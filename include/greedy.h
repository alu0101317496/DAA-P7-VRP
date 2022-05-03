#include "local_search/searches/OPT2.h"

class Greedy : public Solver{
  public:
  Greedy(int, Graph*, int);
  ~Greedy();
  Solution Solve(Graph* graph, std::vector<Vehicle>&);
  int* FilterGroups(Graph*, int);
  int SelectFromCandidates(int*, Graph*, int);
  private:
  int n_customers_;
};
