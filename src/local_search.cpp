#include "local_search.h"
#include "feasibility_check.h"
#include <algorithm>
#include <numeric>

// tryAdd : ajoute le j qui couvre le plus de non-couverts / coût
bool tryAdd(int m, const std::vector<std::vector<int>>& A,
            const std::vector<double>& costs,
            std::vector<int>& sol) {
    std::vector<bool> covered(m,false);
    for(int j:sol)
      for(int i=0;i<m;i++)
        if(A[i][j]) covered[i]=true;

    double bestScore=0;
    int bestJ=-1;
    for(int j=0;j<(int)costs.size();j++){
      if(std::count(sol.begin(),sol.end(),j)) continue;
      int newCov=0;
      for(int i=0;i<m;i++)
        if(A[i][j] && !covered[i]) newCov++;
      if(newCov>0){
        double score = newCov / costs[j];
        if(score>bestScore){
          bestScore=score;
          bestJ=j;
        }
      }
    }
    if(bestJ>=0){
      sol.push_back(bestJ);
      return true;
    }
    return false;
}

// tryRemove : retire un subset si la solution reste faisable
bool tryRemove(int m, const std::vector<std::vector<int>>& A,
               const std::vector<double>& costs,
               std::vector<int>& sol) {
    for(auto it=sol.begin(); it!=sol.end(); ++it){
      int rem = *it;
      auto cand = sol;
      cand.erase(std::find(cand.begin(),cand.end(),rem));
      if(isFeasible(m,A,cand)){
        sol = cand;
        return true;
      }
    }
    return false;
}

// trySwap : échange un in par un out si faisable et coût réduit
bool trySwap(int m, const std::vector<std::vector<int>>& A,
             const std::vector<double>& costs,
             std::vector<int>& sol) {
    auto costOf = [&](const std::vector<int>& s){
      return std::accumulate(s.begin(),s.end(),0.0,
        [&](double acc,int j){return acc + costs[j];});
    };
    for(int in : sol){
      for(int out=0; out<(int)costs.size(); out++){
        if(std::count(sol.begin(),sol.end(),out)) continue;
        auto cand = sol;
        std::replace(cand.begin(),cand.end(), in, out);
        if(isFeasible(m,A,cand) && costOf(cand) < costOf(sol)){
          sol = cand;
          return true;
        }
      }
    }
    return false;
}
