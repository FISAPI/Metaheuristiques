#include "algorithme_glouton.h"
#include <iostream>
#include <set>
#include <limits>
#include <algorithm>

using namespace std;

// Constructeur
GreedySetCover::GreedySetCover(int universeSize, const vector<vector<int>> &subsets, const vector<double> &costs) {
    this->universeSize = universeSize;
    this->subsets = subsets;
    this->costs = costs;
}

// Algorithme glouton pour la couverture d'ensemble
vector<int> GreedySetCover::solve() {
    set<int> covered;  // Éléments couverts
    vector<int> solution;  // Indices des sous-ensembles sélectionnés

    while (covered.size() < universeSize) {
        int bestIndex = -1;
        double bestRatio = numeric_limits<double>::max();

        for (int i = 0; i < subsets.size(); i++) {
            int uncoveredCount = 0;
            for (int elem : subsets[i]) {
                if (covered.find(elem) == covered.end()) {
                    uncoveredCount++;
                }
            }
            if (uncoveredCount > 0) {
                double ratio = costs[i] / uncoveredCount;
                if (ratio < bestRatio) {
                    bestRatio = ratio;
                    bestIndex = i;
                }
            }
        }

        if (bestIndex == -1) break; // Aucun sous-ensemble ne peut améliorer la couverture

        // Ajouter le meilleur sous-ensemble à la solution
        solution.push_back(bestIndex);
        for (int elem : subsets[bestIndex]) {
            covered.insert(elem);
        }
    }
    return solution;
}

// Affichage de la solution
void GreedySetCover::printSolution(const vector<int> &solution) {
    cout << "Solution trouvée : ";
    for (int idx : solution) {
        cout << idx << " ";
    }
    cout << "\nSous-ensembles sélectionnés et leurs éléments :\n";

    for (int idx : solution) {
        cout << "Sous-ensemble " << idx << " : { ";
        for (int elem : subsets[idx]) {
            cout << elem << " ";
        }
        cout << "} (Coût: " << costs[idx] << ")\n";
    }
}
