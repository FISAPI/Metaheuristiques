#ifndef ALGORITHME_GLOUTON_H
#define ALGORITHME_GLOUTON_H

#include <vector>

class GreedySetCover {
private:
    int universeSize; // Nombre total d'éléments
    int numSubsets;   // Nombre de sous-ensembles
    std::vector<std::vector<int>> cover_matrix; // Matrice binaire de couverture
    std::vector<double> costs; // Coûts des sous-ensembles

public:
    GreedySetCover(int universeSize, int numSubsets, const std::vector<std::vector<int>> &cover_matrix, const std::vector<double> &costs);
    std::vector<int> solve();
    void printSolution(const std::vector<int> &solution);
};

#endif
