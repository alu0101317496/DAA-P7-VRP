/* date = May 2nd 2022 0:53 am */
#include "../LocalSearch.h"

#ifndef _EXCHANGE__INTER_H
#define _EXCHANGE__INTER_H


class ExchangeInter : public LocalSearch {
  public:
  ExchangeInter(Graph*, int);
  ~ExchangeInter();
  
  void SolveLocal(std::vector<Vehicle>&, Solution&);
  private:
  void InterRouteProcedure(Vehicle&, Vehicle&, Solution&);

  Pair SwapCost(Vehicle&, Vehicle&, int, int);
};

#endif //_EXCHANGE__INTER_H
