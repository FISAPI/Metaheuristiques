#include "SetCover.h"
#include <algorithm>

std::vector<bool> constructInitialSolution() {
    std::vector<bool> solution(subsets.size(), false);
    std::vector<bool> covered(universe.size(), false);

    for (size_t i = 0; i < subsets.size(); i++) {
        for (int elem : subsets[i].elements) {
            if (!covered[elem]) {
                solution[i] = true;
                for (int e : subsets[i].elements) {
                    covered[e] = true;
                }
                break;
            }
        }
    }
    return solution;
}

bool isFeasible(const std::vector<bool>& solution) {
    std::vector<bool> covered(universe.size(), false);
    for (size_t i = 0; i < solution.size(); i++) {
        if (solution[i]) {
            for (int elem : subsets[i].elements) {
                covered[elem] = true;
            }
        }
    }
    return std::all_of(covered.begin(), covered.end(), [](bool c) { return c; });
}

int solutionCost(const std::vector<bool>& solution) {
    int totalCost = 0;
    for (size_t i = 0; i < solution.size(); i++) {
        if (solution[i]) totalCost += (subsets[i].variableCost + subsets[i].fixedCost);
    }
    return totalCost;
}