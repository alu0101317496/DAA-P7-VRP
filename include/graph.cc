#include "graph.h"

Graph::Graph() {}
Graph::~Graph() {}
void Graph::AddNode(const Node new_node) {
  nodes_.emplace_back(new_node);
}

// Visualize all the nodes in the graph
void Graph::GraphVisualizer() {
  for (auto& node : nodes_) {
    node.Visualizer();
  }
}

// Getters
Node& Graph::get_node(int index) {
  return nodes_[index];
}


bool Graph::AllNodesVisited() {
  for (auto& node : nodes_) {
    if (!node.visited) {
      return false;
    }
  }
  return true;
}

void Graph::VisitedVisualizer() {
  std::string aux = "";
  for (auto& node : nodes_) {
    aux += "Node: " + std::to_string(node.identifier) + " -> ";
    if (node.visited) {
      aux += "TRUE\n";
    } else {
      aux += "false\n";
    }
  }
  std::cout << aux;
}

void Graph::ResetVisited() {
  for (auto& node : nodes_) {
    node.visited = false;
  }
}
