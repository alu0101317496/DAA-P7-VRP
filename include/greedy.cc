#include "greedy.h"

Greedy::Greedy(int customers, Graph* graph, int v) : Solver(graph, v) {}
Greedy::~Greedy() {}

/**
 * @brief Solves the problem 
 */
Solution Greedy::Solve(Graph* graph, std::vector<Vehicle>& vehicles) {
  graph->get_node(0).visited = true;
  
  for(int i = 0; i < (int)vehicles.size(); ++i) {
    vehicles[i].path.emplace_back(0);
  }
  while (!graph->AllNodesVisited()) {
    for (int i = 0; i < (int)vehicles.size(); ++i) {
      int* CRL = FilterGroups(graph, vehicles[i].actual_position);
      int next_node = SelectFromCandidates(CRL, graph, vehicles[i].actual_position);
      vehicles[i].path.emplace_back(next_node);
      graph->get_node(next_node).visited = true;
      vehicles[i].acumulated_cost += graph->get_node(vehicles[i].actual_position).cost_per_pos[next_node];
      vehicles[i].actual_position = next_node;
    }
  }
  
  for(int i = 0; i < (int)vehicles.size(); ++i) {
    vehicles[i].path.emplace_back(0);
    vehicles[i].acumulated_cost += graph->get_node(vehicles[i].actual_position).cost_per_pos[0];
  }

  
  int final_cost = 0;
  for(int i = 0; i < (int)vehicles.size(); ++i) {
    vehicles[i].VisualizePath();
    final_cost += vehicles[i].acumulated_cost;
  }

  std::cout << "Final acumulated cost: " << final_cost << '\n';
  Solution new_sol;
  new_sol.set_total_cost(final_cost);
  new_sol.set_path(vehicles);
  return new_sol;
}

/**
 * @brief FilterGroups filters the groups of the 3 nodes with the 
 * lowest cost
 * @param graph gives access to the graph nodes.
 * @param actual_position gives the actual position of the vehicle.
 * @return
 */
int* Greedy::FilterGroups(Graph* graph, int position) {
  int min_cost = 99999999;
  int min_cost_node = -1;
  int candidate_min_cost_node = -1;
  int* candidate_nodes = new int[3];
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; 
        j < (int)graph->get_node(position).cost_per_pos.size(); 
        ++j) {
      if (graph->get_node(position).cost_per_pos[j] < min_cost &&
        !graph->get_node(j).visited) {
        candidate_min_cost_node = j;
        if(j != position && [candidate_nodes, &j](){for(int a=0; a < 3; ++a) if(candidate_nodes[a] == j) return false; return true;}()) {
          min_cost = graph->get_node(position).cost_per_pos[j];
          min_cost_node = j;
        } else {
            candidate_min_cost_node = 99999;
        }
      }
    }
    candidate_nodes[i] = min_cost_node;
    min_cost = 99999999;
    candidate_min_cost_node= -1;
  }
  return candidate_nodes;
}

/**
 * @brief Selects the next node to visit from the candidates
 * @param candidates The candidates to choose from
 * @param graph The graph to use
 * @param position The actual position of the vehicle
 * @return The next node to visit
 */
int Greedy::SelectFromCandidates(int* CRL, Graph* graph, int a_pos) {
  int min_cost = 99999999;
  int min_cost_node = -1;
  for (int i = 0; i < 3; ++i) {
    if (graph->get_node(a_pos).cost_per_pos[CRL[i]] < min_cost) {
      min_cost = graph->get_node(a_pos).cost_per_pos[CRL[i]];
      min_cost_node = CRL[i];
    }
  }
  return min_cost_node;
}
