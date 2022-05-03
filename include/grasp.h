#include "local_search/searches/OPT2.h"
#include "local_search/searches/Exchange_Inter.h"
#include "local_search/searches/Exchange_Intra.h"
#include "local_search/searches/ReInsertion_Intra.h"
#include "local_search/searches/ReInsertion_Inter.h"

class GRASP : public Solver {
  public:
  GRASP(int, Graph*, int);
  ~GRASP();
  Solution Solve(Graph*, std::vector<Vehicle>&);
  void MakeRCL(int*,Graph*, int);
  int SelectRandomElementFromRCL(int*);
  void ConstructGreedyRandomizedSolution(Graph*, std::vector<Vehicle>&, Solution&);
  void SearchLocally(Graph*, std::vector<Vehicle>&, Solution&);
  bool UpdateSolution(Solution&, Solution&);
  void MakeRCLInsertion(int*,Graph*, int);
  
  
  private:
  int n_customers_;
  std::string information(int&, int);
  LocalSearch* local_exchange_intra_;
  LocalSearch* local_exchange_inter_;
  LocalSearch* local_reinsertion_inter_;
  LocalSearch* local_reinsertion_intra_;
  LocalSearch* local_2_opt_;
  int SelectRandomElementFromRCLInsertion(int*);
};
