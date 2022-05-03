// NOTE(Seriuusly): REINSERTION_INTRA CLASS DEF
#include "ReInsertion_Intra.h"

/**
* @desc Constructor and destructor of the Reinsertion Inter Class
*/
ReInsertionIntra::ReInsertionIntra(Graph* graph, int v) : 
  LocalSearch(graph, v) {}
ReInsertionIntra::~ReInsertionIntra() {}

/**
*
*
*
*/
void ReInsertionIntra::SolveLocal(std::vector<Vehicle>& vehicles, Solution& best_solution) {
  Solution new_solution;
  for (auto& v : vehicles) {
    ReInsertionProcedure(v, new_solution);
  }
  if (new_solution < best_solution) {
    best_solution = new_solution;
  }
}

void ReInsertionIntra::ReInsertionProcedure(Vehicle& vehicle, Solution& solution) {
  int best_cost = vehicle.acumulated_cost;
  int f_index = -1;
  int s_index = -1;
  bool improvements = false;

  do {
    improvements = false;
    for (int i = 1; i < vehicle.path.size() - 1; ++i) {
      for (int j = 0; j < vehicle.path.size() - 1; ++j) {
        if (i == j) { // not swapping with itself
          continue;
        }
        if (i == (j+1)) { // not swapping with next one
          continue;
        }
        int insertion_cost = ReInsertionCost(vehicle, i, j);
        if (insertion_cost < best_cost) {
          best_cost = insertion_cost;
          f_index = i;
          s_index = j;
        }
      }
    }
    if (f_index != -1 && s_index != -1) {
      Insert(vehicle, f_index, s_index);
      vehicle.RecalculateCarCost(graph_);
      f_index = -1;
      s_index = -1;
      improvements = true;
    }
  } while (improvements);
}

int ReInsertionIntra::ReInsertionCost(Vehicle& v, int f_i, int s_i) {
  int swap_cost = v.acumulated_cost;

  /** Values */
  int f_v     = v.path[f_i];
  int pre_f_v = v.path[f_i - 1];
  int pos_f_v = v.path[f_i + 1];

  int s_v     = v.path[s_i];
  int pre_s_v = v.path[s_i - 1];
  int pos_s_v = v.path[s_i + 1];

  swap_cost = swap_cost
    - graph_->get_node(pre_f_v).cost_per_pos[f_v]
    - graph_->get_node(f_v).cost_per_pos[pos_f_v]
    - graph_->get_node(s_v).cost_per_pos[pos_s_v]
    + graph_->get_node(pre_f_v).cost_per_pos[pos_f_v]
    + graph_->get_node(s_v).cost_per_pos[f_v]
    + graph_->get_node(f_v).cost_per_pos[pos_s_v];
  return swap_cost;
}

void ReInsertionIntra::Insert(Vehicle& v, int f_pos, int s_pos) {
  std::vector<int> new_route;
  int f_val = v.path[f_pos];
  int s_val = v.path[s_pos];

  if (f_pos < s_pos) {
    for (int i = 0; i < f_pos; ++i) {
      new_route.emplace_back(v.path[i]);
    }
    for (int i = f_pos + 1; i <= s_pos; ++i) {
      new_route.emplace_back(v.path[i]);
    }
    new_route.emplace_back(v.path[f_pos]);
    for (int i = s_pos + 1; i < v.path.size(); ++i) {
      new_route.emplace_back(v.path[i]);
    }
  } else {
    for (int i = 0; i <= s_pos; ++i) {
      new_route.emplace_back(v.path[i]);
    }
    new_route.emplace_back(v.path[f_pos]);
    for (int i = s_pos + 1; i < f_pos; ++i) {
      new_route.emplace_back(v.path[i]);
    }
    for(int i = f_pos + 1; i < v.path.size(); ++i) {
      new_route.emplace_back(v.path[i]);
    }
  }

  v.path = new_route;
  new_route.clear();
}
