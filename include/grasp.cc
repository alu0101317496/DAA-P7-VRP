#include "grasp.h"

GRASP::GRASP(int n_customers) :
n_customers_(n_customers),
l_s_option_(3)
{}
GRASP::~GRASP() {}


/**
* @brief Solve: this is the function called grasp in the paper
* it solves the problem using the GRASP procedures
*/
void GRASP::Solve(Graph* graph, std::vector<Vehicle>& vehicles) {
  int criterio = 0;
  int n_iterations = 0;
  Solution best_sol;
  Solution new_solution;
  while (n_iterations < 10000 && criterio < 1000) {
    graph->ResetVisited();
    for(auto& vehicle : vehicles) {
      vehicle.Reset();
    }
    ConstructGreedyRandomizedSolution(graph, vehicles, new_solution);
    LocalSearch(graph, vehicles, new_solution);
    if (UpdateSolution(best_sol, new_solution)) {
      criterio = 0;
    } else {
      criterio++;
    }




    std::string print_info = information(n_iterations, 
                                          criterio, 
                                          best_sol.get_total_cost());
    n_iterations++;
    system("cls");
    std::cout << print_info;
  }
}

/**
 * @brief ConstructGreedyRandomizedSolution: this function constructs a 
 * solution using the greedy randomized algorithm
 * @param graph: the graph 
 * @param vehicles: the vehicles 
 * @param solution: the solution
 */
void GRASP::ConstructGreedyRandomizedSolution(Graph* graph, 
                                              std::vector<Vehicle>& vehicles, 
                                              Solution& solution) {
  int* RCL = new int[10];
  graph->get_node(0).visited = true;
  for(auto& v : vehicles) {
    v.path.emplace_back(0);
  }
  while(!graph->AllNodesVisited()) {
    for (int id_vehicle = 0; id_vehicle < (int)vehicles.size(); id_vehicle++) {
      int s;
      if(!graph->AllNodesVisited()) {
        MakeRCL(RCL, graph, vehicles[id_vehicle].actual_position);
        s = SelectRandomElementFromRCL(RCL);
      }
      graph->get_node(s).visited = true;
      vehicles[id_vehicle].acumulated_cost += graph->get_node(vehicles[id_vehicle].actual_position).cost_per_pos[s];
      vehicles[id_vehicle].path.emplace_back(s);
      vehicles[id_vehicle].actual_position = s;
    }
  }
  for(auto& v : vehicles) {
    v.path.emplace_back(0);
    v.acumulated_cost += graph->get_node(v.actual_position).cost_per_pos[0];
  }

  int total_cost = 0;
  for (auto& v : vehicles) {
    total_cost += v.acumulated_cost;
  }

  if(total_cost < solution.get_total_cost()) {
    solution.set_total_cost(total_cost);
    solution.set_path(vehicles);
  }
}

/**
 * @brief MakeRCL: this function makes the RCL
 * @param RCL: the RCL 
 * @param graph: the graph 
 * @param actual_position: the actual position of the vehicle
 */
void GRASP::MakeRCL(int* RCL, 
                    Graph* graph,
                    int actual_position) {
  for(int p = 0; p < 10; p++) {
    RCL[p] = -1;
  }
  int min = 999999;
  int min_index = -1;
  int candidate_min_cost_node = -1;
  for (int j = 0; j < 10; ++j) {
    for (int i = 0; 
         i < (int)graph->get_node(actual_position).cost_per_pos.size(); 
         ++i) {
      if (graph->get_node(actual_position).cost_per_pos[i] < min &&
          !graph->get_node(i).visited) {
        candidate_min_cost_node = i;
        if(i != actual_position && [RCL, &i](){for(int a = 0; a < 10; ++a) if (RCL[a] == i) return false; return true;}()) {
          min = graph->get_node(actual_position).cost_per_pos[i];
          min_index = i;
        } else {
          candidate_min_cost_node = 999999;
        }
      }
    }
    RCL[j] = min_index;
    candidate_min_cost_node = -1;
    min = 999999;
    min_index = -1;
  }
}


/**
 * @brief SelectRandomElementFromRCL: this function selects
 * a random element from the RCL
 * @param RCL: the RCL
 */
int GRASP::SelectRandomElementFromRCL(int* RCL) {
  srand(time(NULL));
  int random_index = -1;
  do {
    random_index = rand() % 10;
  } while(RCL[random_index] == -1);
  return RCL[random_index];
}

std::string GRASP::information(int& n_iterations, int& criterio, int cost) {
  std::string information = "";
  information = "Iteration: " + std::to_string(n_iterations) + '\n';
  information += "Iterations without improvement: " + std::to_string(criterio) + '\n';
  information += "Best solution: " + std::to_string(cost) + '\n';
  return information;
}

bool GRASP::UpdateSolution(Solution& solution, Solution& new_solution) {
  if (new_solution < solution) {
    solution = new_solution;
    return true;
  }
  return false;
}

void GRASP::LocalSearch(Graph* graph, 
                        std::vector<Vehicle>& vehicles, 
                        Solution& solution) {
  switch(l_s_option_) {
    case 0:
      re_insertion(graph, vehicles, solution);
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      opt2_optimization(graph, vehicles, solution);
     break;
  }

}

void GRASP::opt2_optimization(Graph* graph, 
                              std::vector<Vehicle>& vehicles, 
                              Solution& solution) {
  Solution new_solution;
  int new_cost = 0;
  do {
    for(auto v: vehicles) {
      for (int i = 1; i < v.path.size()-1; ++i) {
        for(int j = i+1; j < v.path.size()-1; ++j) {
          opt2_swap(v, i, j);
          update_costs(graph, vehicles);
          for(auto& va : vehicles) {
            new_cost += va.acumulated_cost;
          }
          if(new_cost < solution.get_total_cost()) {
            new_solution.set_path(vehicles);
            new_solution.set_total_cost(new_cost);
          }
          new_cost = 0;
        }
      }
    }
  } while(UpdateSolution(solution, new_solution));
}

void GRASP::opt2_swap(Vehicle& vehicles, int i, int k) {
  std::vector<int> new_path;
    for (int a = 0; a < i; ++a) {
      new_path.emplace_back(vehicles.path[a]);
    }
    for (int b = k; b >= i; --b) {
      new_path.emplace_back(vehicles.path[b]);
    }
    for (int c = k+1; c < vehicles.path.size(); ++c) {
      new_path.emplace_back(vehicles.path[c]);
    }
    vehicles.path = new_path;
    new_path.clear();
}

void GRASP::update_costs(Graph* graph, std::vector<Vehicle>& vehicles) {
  for (int v = 0; v < (int)vehicles.size(); ++v) {
    std::vector<int> path = vehicles[v].path;
    int cost = 0;
    for (int i = 0; i < (int)path.size()-1; ++i) {
      cost += graph->get_node(path[i]).cost_per_pos[path[i+1]];
    }
  }
}

void GRASP::re_insertion(Graph* graph, std::vector<Vehicle>& vehicles, Solution& solution) {
  Solution new_solution;
  int new_cost = 0;
  do {
    for(auto v: vehicles) {
      for (int i = 1; i < v.path.size()-1; ++i) {
          re_insertion_swap(v, graph,i, solution.get_total_cost());
          update_costs(graph, vehicles);
          for(auto& va : vehicles) {
            new_cost += va.acumulated_cost;
          }
          if(new_cost < solution.get_total_cost()) {
            new_solution.set_path(vehicles);
            new_solution.set_total_cost(new_cost);
          }
          new_cost = 0;
        }
      }
    } while(UpdateSolution(solution, new_solution));
}

void GRASP::re_insertion_swap(Vehicle& ve, Graph* graph, int i, int old_cost) {
  int* RCL = new int[5];
  MakeRCLInsertion(RCL,graph,ve.path[i]);
  int candidate_node = SelectRandomElementFromRCLInsertion(RCL);
  int to_swap_index = std::find(ve.path.begin(), ve.path.end(), candidate_node) - ve.path.begin();
  int old_value = ve.path[i];
  ve.path[i] = candidate_node;
  ve.path[to_swap_index] = old_value;
  delete[] RCL;
}

void GRASP::MakeRCLInsertion(int* RCL, Graph* graph, int actual_position) {
    for(int p = 0; p < 5; p++) {
    RCL[p] = -1;
  }
  int min = 999999;
  int min_index = -1;
  int candidate_min_cost_node = -1;
  for (int j = 0; j < 5; ++j) {
    for (int i = 0; 
         i < (int)graph->get_node(actual_position).cost_per_pos.size(); 
         ++i) {
      if (graph->get_node(actual_position).cost_per_pos[i] < min) {
        candidate_min_cost_node = i;
        if(i != actual_position && [RCL, &i](){for(int a = 0; a < 5; ++a) if (RCL[a] == i) return false; return true;}()) {
          min = graph->get_node(actual_position).cost_per_pos[i];
          min_index = i;
        } else {
          candidate_min_cost_node = 999999;
        }
      }
    }
    RCL[j] = min_index;
    candidate_min_cost_node = -1;
    min = 999999;
    min_index = -1;
  }

}

int GRASP::SelectRandomElementFromRCLInsertion(int* RCL) {
  srand(time(NULL));
  int random_index = -1;
  do {
    random_index = rand() % 5;
  } while(RCL[random_index] == -1);
  return RCL[random_index];
}
