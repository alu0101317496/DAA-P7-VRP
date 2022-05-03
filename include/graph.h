#include "structures.h"
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
  inline int get_number_of_nodes() {return nodes_.size();}
  private: 
  int number_of_nodes_;
  std::vector<Node> nodes_;
};

typedef struct internal_vehicle {
  ~internal_vehicle() {}
  int identifier;
  int actual_position = 0;
  std::vector<int> path;
  int acumulated_cost = 0;
  void Reset() {
    actual_position = 0;
    acumulated_cost = 0;
    path.clear();
  }
  
  void RecalculateCarCost(Graph* graph) {
    int cost = 0;
    for (int i = 0; i < (int)path.size() - 1; ++i) {
      cost += graph->get_node(path[i]).cost_per_pos[path[i+1]];
    }
    acumulated_cost = cost;
  }
  
  std::string VisualizePath() {
    std::string aux_printer;
    aux_printer += "Vehicle: " + std::to_string(identifier+1);
    aux_printer += " cost -> " + std::to_string(acumulated_cost) + "\n";
    aux_printer += "Path: ";
    for (int i = 0; i < (int)path.size(); i++) {
      aux_printer += std::to_string(path[i]) + ((i == (int)(path.size()-1)? "\n" : "->" ));
    }
    return aux_printer;
  }
} Vehicle;
