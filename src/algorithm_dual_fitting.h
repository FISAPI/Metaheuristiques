#ifndef ALGORITHME_DUAL_FITTING_H
#define ALGORITHME_DUAL_FITTING_H

#include <vector>

class DualFittingSetCover {
private:
    int universeSize;                   // Nombre total d'éléments à couvrir
    std::vector<std::vector<int>> cover_matrix;  // Liste des sous-ensembles
    std::vector<double> costs;          // Coût de chaque sous-ensemble

public:
    // Constructeur
    DualFittingSetCover(int universeSize, const std::vector<std::vector<int>> &subsets, const std::vector<double> &costs);

    // Algorithme Dual Fitting
    std::vector<int> solve();

    // Affichage de la solution
    void printSolution(const std::vector<int> &solution);
};

#endif // ALGORITHME_DUAL_FITTING_H
