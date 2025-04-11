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
    set<int> covered;               // Set of already covered elements
    vector<int> solution;           // Indices of selected subsets
    vector<bool> subsetVisited(numSubsets, false); // Track if each subset was examined

    while (covered.size() < universeSize) {
        int bestIndex = -1;
        double bestRatio = -1.0;  // Maximize uncoveredCount / cost

        for (int j = 0; j < numSubsets; j++) {
            subsetVisited[j] = true;

            int uncoveredCount = 0;

            for (int i = 0; i < universeSize; i++) {
                if (cover_matrix[i][j] == 1 && covered.find(i) == covered.end()) {
                    uncoveredCount++;
                }
            }

            if (uncoveredCount > 0) {
                double ratio = uncoveredCount / costs[j];
                if (ratio > bestRatio) {
                    bestRatio = ratio;
                    bestIndex = j;
                }
            }
        }

        if (bestIndex == -1) {
            cout << "⚠️ Warning: No useful subset found to improve coverage." << endl;
            break;
        }

        solution.push_back(bestIndex);

        for (int i = 0; i < universeSize; i++) {
            if (cover_matrix[i][bestIndex] == 1) {
                covered.insert(i);
            }
        }
    }

    // Final checks and diagnostics
    int visitedCount = count(subsetVisited.begin(), subsetVisited.end(), true);
    cout << "\nℹ️ Subsets evaluated during solving: " << visitedCount << " / " << numSubsets << endl;

    cout << "✅ Elements covered: " << covered.size() << " / " << universeSize << endl;

    if (covered.size() < universeSize) {
        cout << "❌ Warning: Not all elements were covered!" << endl;
        cout << "Missing elements: ";
        for (int i = 0; i < universeSize; ++i) {
            if (covered.find(i) == covered.end()) {
                cout << i << " ";
            }
        }
        cout << endl;
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
