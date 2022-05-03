#include "vrp.h"

VRP::VRP(std::string input_file, int option) {
  std::ifstream input(input_file);
  std::string line;
  getline(input, line);
  std::stringstream ss(line);
  std::string trash;
  ss >> trash >> num_customers_;
  getline(input, line);
  ss.clear();
  ss.str(line);
  ss >> trash >> num_vehicles_;
  std::cout << "num_customers: " << num_customers_ << std::endl;
  std::cout << "num_vehicles: " << num_vehicles_ << std::endl;
  getline(input, line);
  ss.clear();
  ss.str(line);
  ss.clear();

  int identifier = 0;
  int cost = 0;
  graph_ = new Graph();
  while(getline(input, line)) {
    std::stringstream ss(line);
    Node newnode;
    newnode.identifier = identifier;
    for (int i = 0; i <= num_customers_; ++i) {
      ss >> cost;
      newnode.cost_per_pos.emplace_back(cost);
    }
    graph_->AddNode(newnode);
    ++identifier;
  }

  if (option == 1) {
    std::cout << "Using greedy\n";
    solver_ = new Greedy(num_customers_, graph_, num_vehicles_);
  } else {
    std::cout << "Using GRASP\n";
    solver_ = new GRASP(num_customers_, graph_, num_vehicles_);
  }

  for (int i = 0; i < num_vehicles_; ++i) {
    Vehicle new_vehicle;
    new_vehicle.identifier = i;
    vehicles_.emplace_back(new_vehicle);
  }
}

VRP::~VRP() {

}

void VRP::Solve() {
  std::vector<SolutionPair> solutions;
  Solution new_solution;
  for(int i = 0; i < 5; ++i) {
    clock_t begin = clock();
    new_solution = solver_->Solve(graph_, vehicles_);
    clock_t end = clock();
    double time = Clocker(begin, end);
    std::cout << "Found solution: " << new_solution.get_total_cost() << '\n' << "Time spent: " << time << '\n';
    solutions.push_back({new_solution, time});
  }
  VisualizeSolutions(solutions);

  std::cout << "Applying shake....\n";
}

void VRP::VisualizeSolutions(std::vector<SolutionPair> solutions) {
  system("cls");
  std::cout << std::setfill('-') << std::setw(5*20) << "|\n";
  std::cout << std::setfill(' ') << std::fixed;
  std::cout << std::setw(20) << "N vehículos" << std::setw(20) << "n" << std::setw(20) << "Ejecución" << std::setw(20) << "Distancia total" << std::setw(20) << "CPU TIME\n";
  std::cout << std::setfill('-') << std::setw(5*20) << "|\n";
  std::cout << std::setfill(' ') << std::fixed;
  for (int i = 0; i < solutions.size(); ++i) {
    std::cout << std::setw(19) << num_vehicles_ << std::setw(20) << num_customers_ << std::setw(20) << i << std::setw(20) << solutions[i].solution.get_total_cost() << std::setw(20) << solutions[i].time << '\n';
  }
}

