#include "vrp.h"

VRP::VRP(std::string input_file) {
  std::ifstream input(input_file);
  std::string line;
  getline(input, line);
  std::stringstream ss(line);
  std::string trash;
  ss >> trash >> num_customers_;
  getline(input, line);
  ss.clear();
  ss.str(line);
  ss >> trash >> num_vehicles_;
  std::cout << "num_customers: " << num_customers_ << std::endl;
  std::cout << "num_vehicles: " << num_vehicles_ << std::endl;
  getline(input, line);
  ss.clear();
  ss.str(line);
  ss.clear();

  int identifier = 0;
  int cost = 0;
  graph_ = new Graph();
  while(getline(input, line)) {
    std::stringstream ss(line);
    Node newnode;
    newnode.identifier = identifier;
    for (int i = 0; i <= num_customers_; ++i) {
      ss >> cost;
      newnode.cost_per_pos.emplace_back(cost);
    }
    graph_->AddNode(newnode);
    ++identifier;
  }

  graph_->GraphVisualizer();
}

VRP::~VRP() {

}

void VRP::Solve() {

}

int VRP::CandidateSelector(std::vector<int>& to_visit) {
  int min_cost = 9999999;
  int min_cost_index = -1;
  for (int i = 0; i < to_visit.size(); ++i) {
    if (graph_->GetNode(to_visit[i]).cost_per_pos[0] < min_cost) {
      min_cost = graph_->GetNode(to_visit[i]).cost_per_pos[0];
      min_cost_index = i;
    }
  }
  return min_cost_index;
}
