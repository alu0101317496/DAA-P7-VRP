// NOTE(Seriuusly): EXCHANGE_INTRA CLASS DEF
#include "Exchange_Intra.h"

ExchangeIntra::ExchangeIntra(Graph* graph, int v) : 
  LocalSearch(graph, v) {}
ExchangeIntra::~ExchangeIntra() {}

/**
* 
* @param @{Vehicle} 
* @param @{Solution} 
*/
void ExchangeIntra::SolveLocal(std::vector<Vehicle>& vehicles, Solution& solution) {
  Solution new_solution;
  for (auto& v : vehicles) {
    IntraRouteProcedure(v, solution);
    new_solution.set_path(vehicles);
  }
  int new_cost = 0;
  for (auto& v : vehicles) {
    new_cost += v.acumulated_cost;
  }
  new_solution.set_total_cost(new_cost);
  if(new_solution < solution) {
    solution = new_solution;
  }
}

void ExchangeIntra::IntraRouteProcedure(Vehicle& vehicle, Solution& new_solution) {
  int f_index = -1;
  int s_index = -1;
  int best_cost = vehicle.acumulated_cost;
  bool improvements = false;
  
  do {
    improvements = false;
    for (int i = 1; i < vehicle.path.size() - 1; ++i) {
      for (int j = i + 1; j < vehicle.path.size() - 1; ++j) {
        int swap_cost = CalculateSwapCost(vehicle, i, j);
        if (swap_cost < best_cost) {
          best_cost = swap_cost;
          f_index = i;
          s_index = j;
        }
      }
    }
    if(f_index != -1 && s_index != -1) {
      Swap(vehicle, f_index, s_index);
      vehicle.RecalculateCarCost(graph_);
      f_index = -1;
      s_index = -1;
      improvements = true;
    }
  } while(improvements);
}

int ExchangeIntra::CalculateSwapCost(Vehicle& vehicle, int f_index, int s_index) {
  int actual_cost = vehicle.acumulated_cost;
  int swap_cost = actual_cost;

  //First Index
  int c_f_index = vehicle.path[f_index];
  int pre_c_f_index = vehicle.path[f_index - 1];
  int pos_c_f_index = vehicle.path[f_index + 1];

  //Second Index
  int c_s_index = vehicle.path[s_index];
  int pre_c_s_index = vehicle.path[s_index - 1];
  int pos_c_s_index = vehicle.path[s_index + 1];

  if (ABSINT(s_index - f_index == 1)) {
    swap_cost -= graph_->get_node(c_f_index).cost_per_pos[pos_c_f_index];
    swap_cost -= graph_->get_node(c_s_index).cost_per_pos[pos_c_s_index];
    swap_cost -= graph_->get_node(pre_c_f_index).cost_per_pos[c_f_index];
    swap_cost += graph_->get_node(pre_c_f_index).cost_per_pos[c_s_index];
    swap_cost += graph_->get_node(c_f_index).cost_per_pos[pos_c_s_index];
    swap_cost += graph_->get_node(c_s_index).cost_per_pos[c_f_index];
  } else {
    swap_cost -= graph_->get_node(pre_c_f_index).cost_per_pos[c_f_index];
    swap_cost -= graph_->get_node(pre_c_s_index).cost_per_pos[c_s_index];
    swap_cost += graph_->get_node(pre_c_f_index).cost_per_pos[c_s_index];
    swap_cost += graph_->get_node(pre_c_s_index).cost_per_pos[c_f_index];
    swap_cost -= graph_->get_node(c_f_index).cost_per_pos[pos_c_f_index];
    swap_cost -= graph_->get_node(c_s_index).cost_per_pos[pos_c_s_index];
    swap_cost += graph_->get_node(c_f_index).cost_per_pos[pos_c_s_index];
    swap_cost += graph_->get_node(c_s_index).cost_per_pos[pos_c_f_index];
  }

     return swap_cost;
}

void ExchangeIntra::Swap(Vehicle& vehicle, int f_index, int s_index) {
  std::vector<int> new_path = vehicle.path;
  int old_f_value = new_path[f_index];
  new_path[f_index] = new_path[s_index];
  new_path[s_index] = old_f_value;
  vehicle.path = new_path;
  vehicle.RecalculateCarCost(graph_);
}
