#pragma once
#include <vector>
#include <deque>

class TabuSearch {
public:
    TabuSearch(int m,
               const std::vector<std::vector<int>>& A,
               const std::vector<double>& costs,
               int tenure = 7,
               int maxIter = 500);
    std::vector<int> run(const std::vector<int>& initSol);
private:
    int m, tenure, maxIter;
    const std::vector<std::vector<int>>& A;
    const std::vector<double>& costs;
    bool neighborhood(std::vector<int>& sol, std::deque<int>& tabu);
    double solutionCost(const std::vector<int>& sol);
};
