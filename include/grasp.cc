#include "grasp.h"

GRASP::GRASP(int n_customers) :
n_customers_(n_customers)
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
  while (n_iterations < 2000 && criterio < 200) {
    graph->ResetVisited();
    for(auto& vehicle : vehicles) {
      vehicle.Reset();
    }
    ConstructGreedyRandomizedSolution(graph, vehicles, new_solution);
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
  while(!graph->AllNodesVisited()) {
    for (int id_vehicle = 0; id_vehicle < (int)vehicles.size(); id_vehicle++) {
      int s;
      if(!graph->AllNodesVisited()) {
        MakeRCL(RCL, graph, vehicles[id_vehicle].actual_position);
        s = SelectRandomElementFromRCL(RCL);
      }
      graph->get_node(s).visited = true;
      vehicles[id_vehicle].path.emplace_back(s);
      vehicles[id_vehicle].acumulated_cost += graph->get_node(vehicles[id_vehicle].actual_position).cost_per_pos[s];
      vehicles[id_vehicle].actual_position = s;
    }
  }

  int total_cost = 0;
  for (auto& vehicle : vehicles) {
    total_cost += vehicle.acumulated_cost;
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
