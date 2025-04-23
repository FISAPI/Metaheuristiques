#include <iostream>
#include <cassert>
#include "../src/feasibility_check.h"
#include "../src/local_search.h"
#include <numeric>

// petit exemple : 4 éléments, 3 sous-ensembles
// A = [
//   S0={0,1}, S1={1,2}, S2={2,3}
// ]
// coûts = [3, 2, 4]
// Univers U={0,1,2,3}

int main() {
    int m = 4;
    std::vector<std::vector<int>> A = {
        {1,0,0},  // élément 0 couvert par S0
        {1,1,0},  // élément 1 couvert par S0,S1
        {0,1,1},  // élément 2 couvert par S1,S2
        {0,0,1}   // élément 3 couvert par S2
    };
    std::vector<double> costs = {3.0, 2.0, 4.0};

    // 1) solution initiale : glouton basique (juste pour l'exemple)
    std::vector<int> sol = {0, 1, 2};
    assert(isFeasible(m, A, sol)); // couvre 0,1 et 2,3

    double costBefore = std::accumulate(sol.begin(), sol.end(), 0.0,
    [&](double sum, int j){ return sum + costs[j]; });
    std::cout << "Cout initial = " << costBefore << "\n";

    // 2) tryRemove : on devrait pouvoir retirer S2 (coût 4)
    bool removed = tryRemove(m, A, costs, sol);
    assert(removed);
    assert(isFeasible(m, A, sol));
    std::cout << "Apres tryRemove, sol =";
    for(int j:sol) std::cout << " " << j;
    double costRem = std::accumulate(sol.begin(), sol.end(), 0.0,
    [&](double sum, int j){ return sum + costs[j]; });
    std::cout << " (cout = " << costRem << ")\n";
    assert(costRem < costBefore);

    // 3) tryAdd : on devrait ré-ajouter S2 ou S1 si ça améliore ratio
    bool added = tryAdd(m, A, costs, sol);
    assert(!added);

    std::vector<int> sol_partial = {0};
    assert(!isFeasible(m, A, sol_partial));

    // Répète tryAdd tant qu’il y a des améliorations
    while (tryAdd(m, A, costs, sol_partial));

    // À la fin, toute la couverture doit être assurée
    assert(isFeasible(m, A, sol_partial));

    std::cout << "Apres add iteratif, sol =";
    for (int j : sol_partial) std::cout << " " << j;
    double finalCost = std::accumulate(sol_partial.begin(), sol_partial.end(), 0.0,
        [&](double s, int j){ return s + costs[j]; });
    std::cout << " (cout = " << finalCost << ")\n";

    // 4) trySwap : test qu'on peut échanger un sous-ensemble par un autre
    bool swapped = trySwap(m, A, costs, sol);
    std::cout << "trySwap returned " << swapped << "\n";
    if (swapped) {
        assert(isFeasible(m, A, sol));
        std::cout << "Apres trySwap, sol =";
        for(int j:sol) std::cout << " " << j;
        std::cout << "\n";
    }

    std::cout << "Tests OK\n";
    return 0;
}
