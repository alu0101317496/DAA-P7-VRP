#include "local_search/searches/OPT2.h"
#include "local_search/searches/Exchange_Inter.h"
#include "local_search/searches/Exchange_Intra.h"
#include "local_search/searches/ReInsertion_Intra.h"
#include "local_search/searches/ReInsertion_Inter.h"

class GVNS : public Solver {
  GVNS(int, Graph*, int);
  ~GVNS();
  Solution Solve(Graph*, std::vector<Vehicle>&);


}
