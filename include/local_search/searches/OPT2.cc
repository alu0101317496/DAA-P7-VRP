#include "./OPT2.h"

/**
* @desc Constructor and destructor of the OPT2 class
* @param The graph to work with
*/
OPT2::OPT2(Graph* graph, int v) : LocalSearch(graph, v) {}
OPT2::~OPT2() {}


/**
* @desc This function applies the local search with 2-opt procedure
* @param @{vehicles} This param is a reference to a vector of vehicles
* @param @{solution} This param is a reference to de actual found solution
*/
void OPT2::SolveLocal(std::vector<Vehicle>& vehicles, Solution& solution) {
  Solution new_solution;
  int new_cost = 0;
  do {
    for (auto& v : vehicles) {
      for (int i = 1; i < v.path.size() - 1; ++i) {
        for (int j = i+1; j < v.path.size() - 1; ++j) {
          OPT2Swap(v, i, j);
          RecalculateCost(vehicles);
          for (auto& va : vehicles) {
            new_cost += va.acumulated_cost;
          }
          if (new_cost < solution.get_total_cost()) {
            new_solution.set_path(vehicles);
            new_solution.set_total_cost(new_cost);
          }
          new_cost = 0;
        }
      }
    }
  } while(UpdateLocalSolution(solution, new_solution));
}

/**
* @desc This function swaps the elements of the car path
* @param @{vehicle}
* @param @{i}
* @param @{k}
*/
void OPT2::OPT2Swap(Vehicle& vehicle, int i, int k) {
  std::vector<int> new_path;
  for (int a = 0; a < i; ++a) {
    new_path.emplace_back(vehicle.path[a]);
  }
  for (int b = k; b >= i; --b) {
    new_path.emplace_back(vehicle.path[b]);
  }
  for (int c = k+1; c < vehicle.path.size(); ++c) {
    new_path.emplace_back(vehicle.path[c]);
  }
  vehicle.path = new_path;
  new_path.clear();
}

/**
* @desc This function 
* @param @{vehicles} 
*/
void OPT2::RecalculateCost(std::vector<Vehicle>& vehicles) {
  for(auto& v : vehicles) {
    std::vector<int> path = v.path;
    int cost = 0;
    for (int i = 0; i < (int)path.size()-1;++i) {
      cost += graph_->get_node(path[i]).cost_per_pos[path[i+1]];
    }
    v.acumulated_cost = cost;
  }
}
