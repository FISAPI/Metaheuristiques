#include "algorithme_glouton.h"
#include <iostream>
#include <set>
#include <limits>
#include <algorithm>
#include <numeric>

using namespace std;

// Constructeur
GreedySetCover::GreedySetCover(int universeSize, int numSubsets, const vector<vector<int>> &cover_matrix, const vector<double> &costs) {
    this->universeSize = universeSize;
    this->numSubsets = numSubsets;
    this->cover_matrix = cover_matrix;
    this->costs = costs;
}

// Algorithme glouton pour la couverture d'ensemble
vector<int> GreedySetCover::solve() {
    set<int> covered;  // Ensemble des éléments déjà couverts
    vector<int> solution;  // Indices des sous-ensembles sélectionnés

    while (covered.size() < universeSize) {
        int bestIndex = -1;
        double bestRatio = numeric_limits<double>::max();

        // Parcourir les sous-ensembles pour trouver le meilleur
        for (int j = 0; j < numSubsets; j++) {
            int uncoveredCount = 0;

            // Vérifier combien d'éléments du sous-ensemble j ne sont pas encore couverts
            for (int i = 0; i < universeSize; i++) {
                if (cover_matrix[i][j] == 1 && covered.find(i) == covered.end()) {
                    uncoveredCount++;
                }
            }

            // Sélectionner le sous-ensemble qui minimise le coût par élément nouvellement couvert
            if (uncoveredCount > 0) {
                double ratio = costs[j] / uncoveredCount;
                if (ratio < bestRatio) {
                    bestRatio = ratio;
                    bestIndex = j;
                }
            }
        }
        if (bestIndex == -1) break; // Aucun sous-ensemble ne peut améliorer la couverture

        // Ajouter le sous-ensemble sélectionné à la solution
        solution.push_back(bestIndex);

        // Marquer ses éléments comme couverts
        for (int i = 0; i < universeSize; i++) {
            if (cover_matrix[i][bestIndex] == 1) {
                covered.insert(i);
            }
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
        for (int i = 0; i < universeSize; i++) {
            if (cover_matrix[i][idx] == 1) {
                cout << i << " ";
            }
        }
        cout << "} (Coût: " << costs[idx] << ")\n";
    }

	cout << "Coût total de la solution : " << accumulate(costs.begin(), costs.end(), 0.0) << endl;
}
