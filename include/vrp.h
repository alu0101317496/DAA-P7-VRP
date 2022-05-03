#include "greedy.h"
#include "grasp.h"

struct SolutionPair {
  Solution solution;
  double time;
};

class VRP {
  public:
  VRP(std::string input_file, int option);
  ~VRP();
  void Solve();
  int CandidateSelector(std::vector<int>&);

  private:
  Graph* graph_;
  Solver* solver_;
  int num_vehicles_;
  int num_customers_;
  std::vector<Vehicle> vehicles_;
  void VisualizeSolutions(std::vector<SolutionPair>);
};
