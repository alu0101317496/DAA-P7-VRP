#include "solutions.h"

class GRASP : public Solver {
public:
  GRASP(int n_vehicles);
  ~GRASP();
  void Solve(Graph*, std::vector<Vehicle>&);
  void MakeRCL(int*,Graph*, int);
  int SelectRandomElementFromRCL(int*);
  void ConstructGreedyRandomizedSolution(Graph*, std::vector<Vehicle>&, Solution&);
  void LocalSearch(Graph*, std::vector<Vehicle>&, Solution&);
  bool UpdateSolution(Solution&, Solution&);
  void MakeRCLInsertion(int*,Graph*, int);


private:
  int n_customers_;
  std::string information(int&, int&, int);
  int l_s_option_;
  void opt2_optimization(Graph*, std::vector<Vehicle>&, Solution&);
  void opt2_swap(Vehicle&, int, int);
  void re_insertion(Graph*, std::vector<Vehicle>&, Solution&);
  void update_costs(Graph*, std::vector<Vehicle>&);
  void re_insertion_swap(Vehicle&, Graph*, int, int);
  int SelectRandomElementFromRCLInsertion(int*);
};
