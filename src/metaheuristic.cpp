#include "metaheuristic.h"
#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <cmath>
#include <limits>
#include <ctime>
#include <algorithm>
#include <numeric>

using namespace std;

// Constructor
Metaheuristic::Metaheuristic(int universeSize, int numSubsets,
                                 const vector<vector<int>> &cover_matrix,
                                 const vector<double> &costs)
    : universeSize(universeSize), numSubsets(numSubsets),
      cover_matrix(cover_matrix), costs(costs) {}

// Simulated annealing to solve Set Cover Problem
vector<int> Metaheuristic::solve() {
    set<int> covered;
    vector<int> currentSolution;
    vector<int> bestSolution;
    set<int> bestCovered;

    double bestCost = numeric_limits<double>::max();
    double temperature = 100.0;
    double coolingRate = 0.95;
    int maxIterations = 1000;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> subsetDist(0, numSubsets - 1);
    uniform_real_distribution<> prob(0.0, 1.0);

    for (int iter = 0; iter < maxIterations && covered.size() < universeSize; ++iter) {
        int candidate = subsetDist(gen);

        // Skip if already selected
        if (find(currentSolution.begin(), currentSolution.end(), candidate) != currentSolution.end()) {
            continue;
        }

        // Evaluate coverage gain
        int gain = 0;
        for (int i = 0; i < universeSize; ++i) {
            if (cover_matrix[i][candidate] == 1 && covered.find(i) == covered.end()) {
                gain++;
            }
        }

        double delta = costs[candidate] / (gain + 1);

        // Accept candidate based on improvement or probability
        if (gain > 0 || prob(gen) < exp(-delta / temperature)) {
            currentSolution.push_back(candidate);

            // Update covered elements
            for (int i = 0; i < universeSize; ++i) {
                if (cover_matrix[i][candidate] == 1) {
                    covered.insert(i);
                }
            }

            // Evaluate cost of current solution
            double cost = 0.0;
            for (int idx : currentSolution) cost += costs[idx];

            // Update best solution if it's better
            if (covered.size() == universeSize && cost < bestCost) {
                bestCost = cost;
                bestSolution = currentSolution;
                bestCovered = covered;
            }
        }

        // Cooling
        temperature *= coolingRate;
    }



    // Fallback: if no complete solution was found, return current one
    if (!bestSolution.empty()) {
        return bestSolution;
    }

    return currentSolution;
}

// Displays the selected subsets and their elements
void Metaheuristic::printSolution(const vector<int>& solution) {
    cout << "Solution found using simulated annealing: ";
    for (int idx : solution) {
        cout << idx << " ";
    }
    cout << "\nSelected subsets and their elements:\n";

    double totalCost = 0.0;
    set<int> finalCovered;

    for (int idx : solution) {
        cout << "Subset " << idx << " : { ";
        for (int i = 0; i < universeSize; i++) {
            if (cover_matrix[i][idx] == 1) {
                cout << i << " ";
                finalCovered.insert(i);
            }
        }
        cout << "} (Cost: " << costs[idx] << ")\n";
        totalCost += costs[idx];
    }

    cout << "Total cost of the solution: " << totalCost << endl;
    cout << "Covered elements: " << finalCovered.size() << " / " << universeSize << endl;

    if (finalCovered.size() < universeSize) {
        cout << "⚠️ Warning: The solution does not cover the entire universe!" << endl;
    }
}
