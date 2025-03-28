#include "greedy_algorithm.h"
#include <iostream>
#include <set>
#include <vector>
#include <limits>
#include <algorithm>
#include <numeric>

using namespace std;

// Constructor
GreedySetCover::GreedySetCover(int universeSize, int numSubsets, const vector<vector<int>> &cover_matrix, const vector<double> &costs) {
    this->universeSize = universeSize;
    this->numSubsets = numSubsets;
    this->cover_matrix = cover_matrix;
    this->costs = costs;
}

// Greedy algorithm for the set cover problem
vector<int> GreedySetCover::solve() {
    set<int> covered;  // Set of already covered elements
    vector<int> solution;  // Indices of the selected subsets

    while (covered.size() < universeSize) {
        int bestIndex = -1;
        double bestRatio = -1.0;  // We maximize, so we initialize with a very low value

        // Find the best subset
        for (int j = 0; j < numSubsets; j++) {
            int uncoveredCount = 0;

            // Count how many elements in this subset are not yet covered
            for (int i = 0; i < universeSize; i++) {
                if (cover_matrix[i][j] == 1 && covered.find(i) == covered.end()) {
                    uncoveredCount++;
                }
            }

            // Choose the subset that maximizes |S_j \ Covered| / c_j
            if (uncoveredCount > 0) {
                double ratio = uncoveredCount / costs[j];  // Corrected formula
                if (ratio > bestRatio) {  // Maximization
                    bestRatio = ratio;
                    bestIndex = j;
                }
            }
        }

        if (bestIndex == -1) break; // No subset can improve the coverage

        // Add the selected subset to the solution
        solution.push_back(bestIndex);

        // Mark its elements as covered
        for (int i = 0; i < universeSize; i++) {
            if (cover_matrix[i][bestIndex] == 1) {
                covered.insert(i);
            }
        }
    }
    return solution;
}

// Display the solution
void GreedySetCover::printSolution(const vector<int> &solution) {
    cout << "Solution found using the greedy algorithm: ";
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

    cout << "Total solution cost: " << totalCost << endl;
}
