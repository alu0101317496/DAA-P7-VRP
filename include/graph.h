#include "solutions.h"
#pragma once

class Graph {
  public:
  Graph();
  ~Graph();
  void AddNode(Node);
  void GraphVisualizer();
  Node& get_node(int);
  bool AllNodesVisited();
  void VisitedVisualizer();
  void ResetVisited();
  private: 
  int number_of_nodes_;
  std::vector<Node> nodes_;
  
};
