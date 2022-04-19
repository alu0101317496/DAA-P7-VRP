#include "solver.h"

class GRASP : public Solver {
public:
    GRASP();
    ~GRASP();
    void Solve(Graph*, std::vector<Vehicle>&);
};
