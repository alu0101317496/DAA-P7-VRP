#include "graph.h"

class VRP {
  public:
  VRP(std::string input_file);
  ~VRP();
  void Solve();
  int CandidateSelector(std::vector<int>&);

  private:
  Graph* graph_;
  int num_vehicles_;
  int num_customers_;
};
