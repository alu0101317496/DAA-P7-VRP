#include "libraries.h"

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

typedef struct internal_vehicle {
  int identifier;
  int actual_position = 0;
  std::vector<int> path;
  int acumulated_cost = 0;
  void Reset() {
    actual_position = 0;
    acumulated_cost = 0;
    path.clear();
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
