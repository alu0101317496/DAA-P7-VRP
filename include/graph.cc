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
