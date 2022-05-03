#include "./LocalSearch.h"

/**
     * @desc Constructor and Destructor of the LocalSearch class
* @class LocalSearch
  */
LocalSearch::LocalSearch(Graph* graph, int v) : graph_(graph) {}

LocalSearch::~LocalSearch() {}

/**
* @desc This function shows the graph in the LocalSearch
*/
void LocalSearch::VisualizeGraph() {
  graph_->GraphVisualizer();
}

bool LocalSearch::UpdateLocalSolution(Solution& solution, Solution& new_solution) {
  if (new_solution < solution) {
    solution = new_solution;
    return true;
  }
  return false;
}
