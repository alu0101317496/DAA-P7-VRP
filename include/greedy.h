#include "solver.h"

class Greedy : public Solver{
  public:
    Greedy(int);
    ~Greedy();
    void Solve(Graph* graph, std::vector<Vehicle>&);
    int CandidateSelector(Graph*, int); 
    int SelectFromCandidates(std::vector<int>&);
  private:
    int n_customers_;


};
