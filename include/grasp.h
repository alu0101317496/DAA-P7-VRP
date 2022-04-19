#include "solver.h"

class GRASP : public Solver {
public:
  GRASP();
  ~GRASP();
  void Solve(Graph*, std::vector<Vehicle>&);
  std::vector<int> MakeRCL(Graph*, int);
  int SelectRandomElementFromRCL(std::vector<int>&);
};
