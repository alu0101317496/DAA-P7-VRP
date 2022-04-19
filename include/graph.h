#include "libraries.h" 
#pragma once

typedef struct internal_node {
  int identifier; 
  std::vector<int> cost_per_pos;
  bool visited;

  void Visualizer() {
    std::string aux_printer;
    aux_printer += "Node: " + std::to_string(identifier) + "\n";
    aux_printer += "Cost per position: \n";
    for (int i = 0; i < (int)cost_per_pos.size(); i++) {
      aux_printer += std::to_string(cost_per_pos[i]) + " ";
    }
    std::cout << aux_printer << '\n';
  }
} Node;

class Graph {
  public:
  Graph();
  ~Graph();
  void AddNode(Node);
  void GraphVisualizer();
  Node& get_node(int);
  private: 
  int number_of_nodes_;
  std::vector<Node> nodes_;
  
};
