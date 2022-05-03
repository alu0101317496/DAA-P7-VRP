// NOTE(Seriuusly): REINSERTION_INTER CLASS DEF
#include "ReInsertion_Inter.h"

/**
* @desc Constructor and destructor of the Reinsertion Inter Class
*/
ReInsertionInter::ReInsertionInter(Graph* graph, int v) : 
 LocalSearch(graph, v) {}
ReInsertionInter::~ReInsertionInter() {}

void ReInsertionInter::SolveLocal(std::vector<Vehicle>& vehicles, Solution& solution) {
  Solution new_solution;
  for (int i = 0; i < vehicles.size(); ++i) {
    for (int j = 0; j < vehicles.size(); ++j) {
      if (i == j) {
        continue;
      }
      ReInsertionProcedure(vehicles[i], vehicles[j], new_solution);
    }
  }
  int new_cost = 0;
  for (auto& v : vehicles) {
    new_cost += v.acumulated_cost;
  }
  new_solution.set_total_cost(new_cost);
  if(new_solution < solution) {
    new_solution.set_path(vehicles);
    solution = new_solution;
  }
}

void ReInsertionInter::ReInsertionProcedure(Vehicle& v1, Vehicle& v2, Solution& solution) {
  Pair best_cost = {v1.acumulated_cost, v2.acumulated_cost};
  int f_index = -1;
  int s_index = -1;

  bool improvements = false;

  do {
    if (v1.path.size() <= 4) {
      break;
    }
    const int max_size = (graph_->get_number_of_nodes()/n_vehicles_) + graph_->get_number_of_nodes() * 0.1;
    if (v2.path.size() >= (max_size)) {
      break;
    }
    improvements = false;
    for (int i = 1; i < v1.path.size() - 1; ++i) {
      for (int j = 0; j < v2.path.size() - 1; ++j) {
        Pair swap_cost = ReInsertionCost(v1, v2, i, j);
        if ((swap_cost.cost_for_1 + swap_cost.cost_for_2) 
          < (best_cost.cost_for_1 + best_cost.cost_for_2)) {
          best_cost = swap_cost;
          f_index = i;
          s_index = j;
        }
      }
    }
    if (f_index != -1 && s_index != -1) {
      Insert(v1, v2, f_index, s_index);
      v1.RecalculateCarCost(graph_);
      v2.RecalculateCarCost(graph_);
      f_index = -1;
      s_index = -1;
      improvements = true;
    }
  } while (improvements);
}

Pair ReInsertionInter::ReInsertionCost(Vehicle& v1, 
                                       Vehicle& v2, 
                                       int f_index, 
                                       int s_index) {
  int prev_f_val = v1.path[f_index - 1];
  int f_val = v1.path[f_index];
  int pos_f_val = v1.path[f_index + 1];

  int prev_s_val = v2.path[s_index - 1];
  int s_val = v2.path[s_index];
  int pos_s_val = v2.path[s_index + 1];

  int new_f_cost = v1.acumulated_cost
    - graph_->get_node(prev_f_val).cost_per_pos[f_val]
    - graph_->get_node(f_val).cost_per_pos[pos_f_val]
    + graph_->get_node(prev_f_val).cost_per_pos[pos_f_val];

  int new_s_cost = v2.acumulated_cost
    - graph_->get_node(s_val).cost_per_pos[pos_s_val]
    + graph_->get_node(s_val).cost_per_pos[f_val]
    + graph_->get_node(f_val).cost_per_pos[pos_s_val];
  
  return {new_f_cost, new_s_cost};
}

void ReInsertionInter::Insert(Vehicle& v1, 
                              Vehicle& v2, 
                              int f_index, 
                              int s_index) {
  std::vector<int> new_f_route;
  std::vector<int> new_s_route;
  for(int i = 0; i < f_index; ++i) {
    new_f_route.emplace_back(v1.path[i]);
  }
  for(int i = f_index + 1; i < v1.path.size(); ++i) {
    new_f_route.emplace_back(v1.path[i]);
  }

  for (int i = 0; i <= s_index; ++i) {
    new_s_route.emplace_back(v2.path[i]);
  }
  new_s_route.emplace_back(v1.path[f_index]);
  for (int i = s_index + 1; i < v2.path.size(); ++i) {
    new_s_route.emplace_back(v2.path[i]);
  }
  
  v1.path = new_f_route;
  v2.path = new_s_route;
}
