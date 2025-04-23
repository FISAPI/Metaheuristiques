#include "feasibility_check.h"
#include <vector>

bool isFeasible(int m,
                const std::vector<std::vector<int>>& cover_matrix,
                const std::vector<int>& solution) {
    std::vector<bool> covered(m, false);
    // Marquer tous les éléments couverts par les sous-ensembles de la solution
    for (int j : solution) {
        for (int i = 0; i < m; ++i) {
            if (cover_matrix[i][j]) {
                covered[i] = true;
            }
        }
    }
    // Vérifier que chaque élément est couvert au moins une fois
    for (bool c : covered) {
        if (!c) return false;
    }
    return true;
}
