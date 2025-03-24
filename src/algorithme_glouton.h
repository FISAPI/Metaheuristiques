#ifndef ALGORITHME_GLOUTON_H
#define ALGORITHME_GLOUTON_H

#include <vector>

class GreedySetCover {
private:
    int universeSize;
    std::vector<std::vector<int>> subsets;
    std::vector<double> costs;

public:
    // Constructeur
    GreedySetCover(int universeSize, const std::vector<std::vector<int>> &subsets, const std::vector<double> &costs);

    // Fonction pour exécuter l'algorithme
    std::vector<int> solve();

    // Afficher la solution
    void printSolution(const std::vector<int> &solution);
};

#endif // ALGORITHME_GLOUTON_H

