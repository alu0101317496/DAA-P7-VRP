#include "solutions.h"

  
Solution::Solution() {
  paths_ = "";
  total_cost_ = 99999999;
}

Solution::~Solution() {}
 
void Solution::UpdateSolution(Solution new_solution) {
  if (new_solution.get_total_cost() < total_cost_) {
    paths_ = new_solution.get_path();
    total_cost_ = new_solution.get_total_cost();
  }
}

std::string Solution::get_path() {
  return paths_;
}

int Solution::get_total_cost() {
  return total_cost_;
}

void Solution::set_path(std::vector<Vehicle> vehicles) {
  paths_ = "";
  for(auto vehicle : vehicles) {
    paths_ += vehicle.VisualizePath();
  }
}

void Solution::set_total_cost(int total_cost) {
  total_cost_ = total_cost;
}

Solution& Solution::operator=(Solution other_solution) {
  paths_ = other_solution.get_path();
  total_cost_ = other_solution.get_total_cost();
  
  return *this;
}

bool Solution::operator <(Solution& other_solution) {
  return total_cost_ < other_solution.get_total_cost();
}

bool Solution::operator >(Solution& other_solution) {
  return total_cost_ > other_solution.get_total_cost();
}

bool Solution::operator ==(Solution& other_solution) {
  return total_cost_ == other_solution.get_total_cost();
}
