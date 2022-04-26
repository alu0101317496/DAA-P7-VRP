#include "solver.h"

class GRASP : public Solver {
public:
  GRASP(int n_vehicles);
  ~GRASP();
  void Solve(Graph*, std::vector<Vehicle>&);
  void MakeRCL(int*,Graph*, int);
  int SelectRandomElementFromRCL(int*);
  void ConstructGreedyRandomizedSolution(Graph*, std::vector<Vehicle>&, Solution&);
  bool UpdateSolution(Solution&, Solution&);

private:
  int n_customers_;
  std::string information(int&, int&, int);
};
