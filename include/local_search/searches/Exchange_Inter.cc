// NOTE(Seriuusly): EXCHANGE_INTER CLASS DEF

#include "Exchange_Inter.h"

/**
* @desc Constructor and destructor of the ExchangeInter class
*/

ExchangeInter::ExchangeInter(Graph* graph, int v) : 
  LocalSearch(graph, v) {}
ExchangeInter::~ExchangeInter() {}

void ExchangeInter::SolveLocal(std::vector<Vehicle>& vehicles, Solution& solution) {
  Solution new_solution;
  for (int i = 0; i < vehicles.size(); ++i) {
    for (int j = i + 1; j < vehicles.size(); ++j) {
      InterRouteProcedure(vehicles[i], vehicles[j], new_solution);
      new_solution.set_path(vehicles);
    }
  }
  int new_cost = 0;
  for (auto& v : vehicles) {
    new_cost += v.acumulated_cost;
  }
  new_solution.set_path(vehicles);
  new_solution.set_total_cost(new_cost);
  if(new_solution < solution) {
    solution = new_solution;
  }
}

void ExchangeInter::InterRouteProcedure(Vehicle& v1, Vehicle& v2, Solution& best_sol) {
  Pair best_cost = {v1.acumulated_cost, v2.acumulated_cost};
  int f_index = -1;
  int s_index = -1;
  bool improvements = false;
  do {
    improvements = false;
    for (int i = 1; i < v1.path.size() - 1; ++i) {
      for (int j = 1; j < v2.path.size() - 1; ++j) {
        Pair swap_cost = SwapCost(v1, v2, i, j);
        if((swap_cost.cost_for_1 + swap_cost.cost_for_2) <
           best_cost.cost_for_1 + best_cost.cost_for_2) {
          best_cost = swap_cost;
          f_index = i;
          s_index = j;
        }
      }
    }
    if (f_index != -1 && s_index != -1) {
      int temp = v1.path[f_index];
      v1.path[f_index] = v2.path[s_index];
      v2.path[s_index] = temp;
      v1.RecalculateCarCost(graph_);
      v2.RecalculateCarCost(graph_);
      f_index = -1;
      s_index = -1;
      improvements = true;
    }
  } while (improvements);
}

Pair ExchangeInter::SwapCost(Vehicle& v1, Vehicle& v2, int f_i, int s_i) {
  int new_f_cost;
  int new_s_cost;
  int f_index = v1.path[f_i];
  int s_index = v2.path[s_i];
  int pre_f = v1.path[f_i - 1];
  int pos_f = v1.path[f_i + 1];
  int pre_s = v2.path[s_i - 1];
  int pos_s = v2.path[s_i + 1];

  new_f_cost = v1.acumulated_cost
    - graph_->get_node(pre_f).cost_per_pos[f_index]
    - graph_->get_node(f_index).cost_per_pos[pos_f]
    + graph_->get_node(pre_f).cost_per_pos[s_index]
    + graph_->get_node(s_index).cost_per_pos[pos_f];

  new_s_cost = v2.acumulated_cost
    - graph_->get_node(pre_s).cost_per_pos[s_index]
    - graph_->get_node(s_index).cost_per_pos[pos_s]
    + graph_->get_node(pre_s).cost_per_pos[f_index]
    + graph_->get_node(f_index).cost_per_pos[pos_s];

  return {new_f_cost, new_s_cost};
}
