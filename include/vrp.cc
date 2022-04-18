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

void VRP::solve() {

}
