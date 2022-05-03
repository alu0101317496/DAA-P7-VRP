/* date = May 2nd 2022 0:50 am */

#include "../LocalSearch.h"

#ifndef _EXCHANGE__INTRA_H
#define _EXCHANGE__INTRA_H

class ExchangeIntra : public LocalSearch {
  public:
  ExchangeIntra(Graph*, int);
  ~ExchangeIntra();
  
  void SolveLocal(std::vector<Vehicle>&, Solution&);
  private:
  void IntraRouteProcedure(Vehicle&, Solution&);
  int CalculateSwapCost(Vehicle&, int, int);
  void Swap(Vehicle& ,int, int);
  
};

#endif //_EXCHANGE__INTRA_H
