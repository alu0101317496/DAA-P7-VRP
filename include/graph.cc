#include "graph.h"

Graph::Graph() {}
Graph::~Graph() {}
void Graph::AddNode(const Node new_node) {
  nodes_.emplace_back(new_node);
}

void Graph::GraphVisualizer() {
  for (auto& node : nodes_) {
    node.Visualizer();
  }
}
