#include "grasp.h"

GRASP::GRASP(int n_vehicles) :
n_vehicles_(n_vehicles)
{}
GRASP::~GRASP() {}


// TODO: Finalize the implementation of GRASP
/**
* @brief Solve: this is the function called grasp in the paper
* it solves the problem using the GRASP procedures
*/
void GRASP::Solve(Graph* graph, std::vector<Vehicle>& vehicles) {
  int criterio = 100;
  std::vector<int> solution;
  while (criterio > 0) {
    ConstructGreedyRandomizedSolution(graph, vehicles, solution);
    criterio--;
  }
}

// TODO: CONSTRUCTIVE METHOD

/**
 * @brief ConstructGreedyRandomizedSolution: this function constructs a 
 * solution using the greedy randomized algorithm
 * @param graph: the graph 
 * @param vehicles: the vehicles 
 * @param solution: the solution
 */
void GRASP::ConstructGreedyRandomizedSolution(Graph* graph, 
                                              std::vector<Vehicle>& vehicles, 
                                              std::vector<int>& solution) {
  solution.clear();
  std::vector<int> RCL;
  while(!graph->AllNodesVisited()) {
    //TEMPORAL 0
    if(RCL.size() < 3) {
      MakeRCL(RCL, graph, vehicles[0].actual_position);
    }
    int s = SelectRandomElementFromRCL(RCL);
    solution.push_back(s);
  }
}

/**
 * @brief MakeRCL: this function makes the RCL
 * @param RCL: the RCL 
 * @param graph: the graph 
 * @param actual_position: the actual position of the vehicle
 */
void GRASP::MakeRCL(std::vector<int>& RCL, 
                         Graph* graph,
                         int actual_position) {
  RCL.clear();
  int min = 999999;
  int min_index = 0;
  for (int j = 0; j < 3; ++j) {
    for (int i = 0; 
        i < (int)graph->get_node(actual_position).cost_per_pos.size(); 
        ++i) {
      if (graph->get_node(actual_position).cost_per_pos[i] < min &&
          !graph->get_node(actual_position).visited &&
          std::find(RCL.begin(), RCL.end(), i) == RCL.end()) {
        min = graph->get_node(actual_position).cost_per_pos[i];
        min_index = i;
      }
    }
    RCL.push_back(min_index);
  }
  
}

/**
 * @brief SelectRandomElementFromRCL: this function selects
 * a random element from the RCL
 * @param RCL: the RCL
 */
int GRASP::SelectRandomElementFromRCL(std::vector<int>& RCL) {
  srand(time(NULL));
  int random_index = rand() % RCL.size();
  RCL.erase(RCL.begin() + random_index);
  return RCL[random_index];
}
