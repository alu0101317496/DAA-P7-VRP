#include "solver.h"

class Greedy : public Solver{
  public:
    Greedy(int);
    ~Greedy();
    void Solve(Graph* graph, std::vector<Vehicle>&);
    int* FilterGroups(Graph*, int);
    int SelectFromCandidates(int*, Graph*, int);
  private:
    int n_customers_;
};
