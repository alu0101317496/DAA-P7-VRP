#include "structures.h"

class Solution {
public:
  Solution();
  ~Solution();

  void UpdateSolution(Solution);
  void set_path(std::vector<Vehicle>);
  std::string get_path();
  void set_total_cost(int);
  int get_total_cost();
  Solution& operator=(Solution&);
  bool operator <(Solution&);
  bool operator >(Solution&);
  bool operator ==(Solution&);

private:
  std::string paths_;
  int total_cost_;
};



