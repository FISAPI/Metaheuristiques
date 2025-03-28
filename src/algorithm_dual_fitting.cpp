#include "algorithm_dual_fitting.h"
#include <iostream>
#include <set>
#include <vector>
#include <limits>
#include <algorithm>
#include <numeric>

using namespace std;

// Constructeur
DualFittingSetCover::DualFittingSetCover(int universeSize, const vector<vector<int>> &cover_matrix, const vector<double> &costs) {
    this->universeSize = universeSize;
    this->cover_matrix = cover_matrix;  // Utilisation de cover_matrix directement
    this->costs = costs;
}

// Algorithme d'approximation par Dual Fitting
vector<int> DualFittingSetCover::solve() {
    vector<double> y(universeSize, 0.0); // Poids duals
    set<int> covered;  // Éléments déjà couverts
    vector<int> solution;  // Indices des sous-ensembles sélectionnés

    while (covered.size() < universeSize) {
        int bestIndex = -1;
        double bestRatio = numeric_limits<double>::max();

        // Sélection du sous-ensemble avec le meilleur ratio coût / éléments non couverts
        for (int j = 0; j < cover_matrix[0].size(); j++) {
            int uncoveredCount = 0;

            for (int i = 0; i < universeSize; i++) {
                if (cover_matrix[i][j] == 1 && covered.find(i) == covered.end()) {
                    uncoveredCount++;
                }
            }

            if (uncoveredCount > 0) {
                double ratio = costs[j] / uncoveredCount;
                if (ratio < bestRatio) {
                    bestRatio = ratio;
                    bestIndex = j;
                }
            }
        }

        if (bestIndex == -1) break; // Aucun sous-ensemble utile n'est trouvé

        // Ajouter le meilleur sous-ensemble à la solution
        solution.push_back(bestIndex);

        // Marquer les éléments couverts par ce sous-ensemble
        for (int i = 0; i < universeSize; i++) {
            if (cover_matrix[i][bestIndex] == 1) {
                covered.insert(i);
                y[i] = max(y[i], costs[bestIndex] / universeSize);  // Mise à jour des poids
            }
        }
    }

    return solution;
}

// Affichage de la solution
void DualFittingSetCover::printSolution(const vector<int> &solution) {
    cout << "Solution trouvée avec Dual Fitting : ";
    for (int idx : solution) {
        cout << idx << " ";
    }
    cout << "\nSous-ensembles sélectionnés et leurs éléments :\n";

    double totalCost = 0.0;
    for (int idx : solution) {
        cout << "Sous-ensemble " << idx << " : { ";
        for (int i = 0; i < universeSize; i++) {
            if (cover_matrix[i][idx] == 1) {
                cout << i << " ";
            }
        }
        cout << "} (Coût: " << costs[idx] << ")\n";
        totalCost += costs[idx];  // Calcul du coût total de la solution
    }
    cout << "Coût total de la solution : " << totalCost << endl;
}
