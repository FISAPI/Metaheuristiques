#include "SetCover.h"
#include <iostream>

int main() {
    readData("CCNFP10g1a.txt");
    std::vector<bool> solution = constructInitialSolution();

    if (isFeasible(solution)) {
        std::cout << "Solution valide avec coût : " << solutionCost(solution) << std::endl;
    } else {
        std::cout << "Solution non valide." << std::endl;
    }
    return 0;
}