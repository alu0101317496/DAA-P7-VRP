/* date = May 2nd 2022 0:30 am */

#include "../LocalSearch.h"

#ifndef _RE_INSERTION__INTRA_H
#define _RE_INSERTION__INTRA_H

class ReInsertionIntra : public LocalSearch{
  public:
  ReInsertionIntra(Graph*, int);
  ~ReInsertionIntra();
  
  void SolveLocal(std::vector<Vehicle>&, Solution&);
  private:
  void ReInsertionProcedure(Vehicle&, Solution&);
  int ReInsertionCost(Vehicle&, int, int);
  void Insert(Vehicle&, int, int);
};

#endif //_RE_INSERTION__INTRA_H
