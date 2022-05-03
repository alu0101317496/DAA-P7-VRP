/* date = May 2nd 2022 0:22 am */

#include "../LocalSearch.h"

#ifndef _RE_INSERTION__INTER_H
#define _RE_INSERTION__INTER_H

class ReInsertionInter : public LocalSearch {
  public:
  ReInsertionInter(Graph*, int);
  ~ReInsertionInter();
  
  void SolveLocal(std::vector<Vehicle>& vehicles, Solution& solution);
  
  private:
  void ReInsertionProcedure(Vehicle&, Vehicle&, Solution&);
  Pair ReInsertionCost(Vehicle&, Vehicle&, int, int);
  void Insert(Vehicle&, Vehicle&, int, int);
};

#endif //_RE_INSERTION__INTER_H
