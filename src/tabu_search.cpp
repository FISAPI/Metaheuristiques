#include "tabu_search.h"
#include "local_search.h"
#include "feasibility_check.h"
#include <algorithm>
#include <numeric>
#include <limits>

TabuSearch::TabuSearch(int m,
                       const std::vector<std::vector<int>>& A,
                       const std::vector<double>& costs,
                       int tenure, int maxIter)
    : m(m), A(A), costs(costs), tenure(tenure), maxIter(maxIter) {}

double TabuSearch::solutionCost(const std::vector<int>& sol) {
    return std::accumulate(sol.begin(), sol.end(), 0.0,
        [&](double s,int j){return s + costs[j];});
}

bool TabuSearch::neighborhood(std::vector<int>& sol, std::deque<int>& tabu) {
    for(int in : sol){
        for(int out=0; out<(int)costs.size(); out++){
            if(std::count(sol.begin(),sol.end(),out)) continue;
            if(std::count(tabu.begin(),tabu.end(),out)) continue;
            auto cand=sol;
            std::replace(cand.begin(),cand.end(), in, out);
            if(isFeasible(m,A,cand) &&
               solutionCost(cand) < solutionCost(sol)) {
                sol=cand;
                tabu.push_back(out);
                if((int)tabu.size()>tenure) tabu.pop_front();
                return true;
               }
        }
    }
    return false;
}

std::vector<int> TabuSearch::run(const std::vector<int>& initSol) {
    std::vector<int> best = initSol, curr = initSol;
    double bestCost = solutionCost(best);
    std::deque<int> tabu;

    for(int it=0; it<maxIter; ++it){
        if(!neighborhood(curr, tabu)) break;
        double currCost = solutionCost(curr);
        if(currCost < bestCost){
            best = curr;
            bestCost = currCost;
        }
    }
    return best;
}
