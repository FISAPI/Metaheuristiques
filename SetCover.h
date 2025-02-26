#ifndef SET_COVER_H
#define SET_COVER_H

#include <vector>
#include <string>

struct Subset {
    std::vector<int> elements;
    int variableCost;
    int fixedCost;
};

extern std::vector<Subset> subsets;
extern std::vector<int> universe;

void readData(const std::string& filename);
std::vector<bool> constructInitialSolution();
bool isFeasible(const std::vector<bool>& solution);
int solutionCost(const std::vector<bool>& solution);

#endif
