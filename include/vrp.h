#include "graph.h"

class VRP {
  public:
  VRP(std::string input_file);
  ~VRP();
  void solve();

  private:
  Graph* graph_;
  int num_vehicles_;
  int num_customers_;
};
