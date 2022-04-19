#include "solver.h"

class GRASP : public Solver {
public:
  GRASP(int n_vehicles);
  ~GRASP();
  void Solve(Graph*, std::vector<Vehicle>&);
  void MakeRCL(std::vector<int>&,Graph*, int);
  int SelectRandomElementFromRCL(std::vector<int>&);
  void ConstructGreedyRandomizedSolution(Graph*, std::vector<Vehicle>&, std::vector<int>& solution);

private:
  int n_vehicles_;
};
