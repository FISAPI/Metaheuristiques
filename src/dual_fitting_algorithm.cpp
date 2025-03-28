#include "dual_fitting_algorithm.h"
#include <iostream>
#include <set>
#include <vector>
#include <limits>
#include <algorithm>
#include <numeric>

using namespace std;

// Constructor
DualFittingSetCover::DualFittingSetCover(int universeSize, const vector<vector<int>> &cover_matrix, const vector<double> &costs) {
    this->universeSize = universeSize;
    this->cover_matrix = cover_matrix;  // Directly using cover_matrix
    this->costs = costs;
}

// Approximation algorithm using Dual Fitting
vector<int> DualFittingSetCover::solve() {
    vector<double> y(universeSize, 0.0); // Dual weights
    set<int> covered;  // Elements that are already covered
    vector<int> solution;  // Indices of selected subsets

    while (covered.size() < universeSize) {
        int bestIndex = -1;
        double bestRatio = numeric_limits<double>::max();

        // Select the subset with the best cost-to-uncovered-elements ratio
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

        if (bestIndex == -1) break; // No useful subset found

        // Add the best subset to the solution
        solution.push_back(bestIndex);

        // Mark the elements covered by this subset
        for (int i = 0; i < universeSize; i++) {
            if (cover_matrix[i][bestIndex] == 1) {
                covered.insert(i);
                y[i] = max(y[i], costs[bestIndex] / universeSize);  // Update dual weights
            }
        }
    }

    return solution;
}

// Display the solution
void DualFittingSetCover::printSolution(const vector<int> &solution) {
    cout << "Solution found using Dual Fitting: ";
    for (int idx : solution) {
        cout << idx << " ";
    }
    cout << "\nSelected subsets and their elements:\n";

    double totalCost = 0.0;
    for (int idx : solution) {
        cout << "Subset " << idx << " : { ";
        for (int i = 0; i < universeSize; i++) {
            if (cover_matrix[i][idx] == 1) {
                cout << i << " ";
            }
        }
        cout << "} (Cost: " << costs[idx] << ")\n";
        totalCost += costs[idx];  // Compute the total cost of the solution
    }
    cout << "Total cost of the solution: " << totalCost << endl;
}
