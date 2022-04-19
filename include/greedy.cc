#include "greedy.h"

Greedy::Greedy(int customers) {}
Greedy::~Greedy() {}

void Greedy::Solve(Graph* graph, std::vector<Vehicle>& vehicles) {
  graph->get_node(0).visited = true;
  for(int i = 0; i < (int)vehicles.size(); ++i) {
    vehicles[i].path.emplace_back(0);
  }
  while (!graph->AllNodesVisited()) {
    for (int i = 0; i < (int)vehicles.size(); ++i) {
      int next_node = CandidateSelector(graph, vehicles[i].actual_position);
      vehicles[i].path.emplace_back(next_node);
      graph->get_node(next_node).visited = true;
      vehicles[i].acumulated_cost += graph->get_node(vehicles[i].actual_position).cost_per_pos[next_node];
    }
  }

  for(int i = 0; i < (int)vehicles.size(); ++i) {
    vehicles[i].path.emplace_back(0);
    vehicles[i].acumulated_cost += graph->get_node(vehicles[i].actual_position).cost_per_pos[0];
  }

  for(int i = 0; i < (int)vehicles.size(); ++i) {
    vehicles[i].VisualizePath();
  }

}

int Greedy::CandidateSelector(Graph* graph, int position) {
  int min_cost = 99999999;
  int min_cost_node = -1;
  for (int i = 0; i < (int)graph->get_node(position).cost_per_pos.size(); ++i) {
    if (graph->get_node(position).cost_per_pos[i] < min_cost &&
      !graph->get_node(i).visited) {
      min_cost = graph->get_node(position).cost_per_pos[i];
      min_cost_node = i;
    }
  }
  return min_cost_node;
}
