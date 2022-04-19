#include "solver.h"

class Greedy : public Solver{
  public:
    Greedy(int);
    ~Greedy();
    void Solve(Graph* graph, std::vector<Vehicle>&);
    std::vector<int> FilterGroups(Graph*, int);
    int SelectFromCandidates(std::vector<int>&, Graph*, int);
  private:
    int n_customers_;
};
