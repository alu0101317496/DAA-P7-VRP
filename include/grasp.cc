#include "grasp.h"

GRASP::GRASP(int n_customers, Graph* graph, int v) : Solver(graph, v),
n_customers_(n_customers)
{
  local_exchange_intra_ = new ExchangeIntra(graph_, v);
  local_exchange_inter_ = new ExchangeInter(graph_, v);
  local_reinsertion_inter_ = new ReInsertionInter(graph_, v);
  local_reinsertion_intra_ = new ReInsertionIntra(graph_, v);
  local_2_opt_ = new OPT2(graph_, v);
}
GRASP::~GRASP() {}


/**
* @brief Solve: this is the function called grasp in the paper
* it solves the problem using the GRASP procedures
*/
Solution GRASP::Solve(Graph* graph, std::vector<Vehicle>& vehicles) {
  int criterio = 0;
  int n_iterations = 0;
  Solution best_sol;
  Solution new_solution;
  while (n_iterations < 100000 && criterio < 10000) {
    graph->ResetVisited();
    for(auto& vehicle : vehicles) {
      vehicle.Reset();
    }
    ConstructGreedyRandomizedSolution(graph, vehicles, new_solution);
    SearchLocally(graph, vehicles, new_solution);
    if (UpdateSolution(best_sol, new_solution)) {
      criterio = 0;
    } else {
      criterio++;
    }
    n_iterations++;
  }
  return best_sol;
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

std::string GRASP::information(int& n_iterations, int cost) {
  std::string information = "";
  information = "Found solution at iteration: " + std::to_string(n_iterations) + '\n';
  information += "Best solution yet: " + std::to_string(cost) + '\n';
  return information;
}

bool GRASP::UpdateSolution(Solution& solution, Solution& new_solution) {
  if (new_solution < solution) {
    solution = new_solution;
    return true;
  }
  return false;
}

void GRASP::SearchLocally(Graph* graph, 
                          std::vector<Vehicle>& vehicles, 
                          Solution& solution) {
  local_reinsertion_inter_->SolveLocal(vehicles, solution);
  local_reinsertion_intra_->SolveLocal(vehicles, solution);
  local_exchange_inter_->SolveLocal(vehicles, solution);
  local_exchange_intra_->SolveLocal(vehicles, solution);
  local_2_opt_->SolveLocal(vehicles, solution);
}

