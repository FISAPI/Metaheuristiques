#include "genetic_algorithm.h"
#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <algorithm>
#include <numeric>

using namespace std;

// Constructor
GeneticSetCover::GeneticSetCover(int universeSize, int numSubsets,
                                 const vector<vector<int>> &cover_matrix,
                                 const vector<double> &costs,
                                 int populationSize,
                                 int generations,
                                 double crossoverRate,
                                 double mutationRate)
        : universeSize(universeSize), numSubsets(numSubsets),
          cover_matrix(cover_matrix), costs(costs),
          populationSize(populationSize), generations(generations),
          crossoverRate(crossoverRate), mutationRate(mutationRate) {}


// Evaluate fitness of a chromosome (lower cost = better)
double fitness(const vector<int> &chromosome, const vector<vector<int>> &cover_matrix,
               const vector<double> &costs, int universeSize) {
    set<int> covered;
    double totalCost = 0.0;

    for (int i = 0; i < chromosome.size(); ++i) {
        if (chromosome[i]) {
            totalCost += costs[i];
            for (int j = 0; j < universeSize; ++j) {
                if (cover_matrix[j][i] == 1)
                    covered.insert(j);
            }
        }
    }

    if (covered.size() < universeSize)
        return 1e9 + (universeSize - covered.size()) * 1000; // Penalize incomplete coverage

    return totalCost;
}

// Main solve function
vector<int> GeneticSetCover::solve() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> prob(0.0, 1.0);
    uniform_int_distribution<> bin(0, 1);

    vector<vector<int>> population;

    // Initial population
    for (int i = 0; i < populationSize; ++i) {
        vector<int> chromosome(numSubsets);
        for (int j = 0; j < numSubsets; ++j)
            chromosome[j] = bin(gen);
        population.push_back(chromosome);
    }

    vector<int> bestSolution;
    double bestFitness = numeric_limits<double>::max();

    for (int genIndex = 0; genIndex < generations; ++genIndex) {
        vector<pair<double, vector<int>>> scored;

        // Evaluate population
        for (auto &individual : population) {
            double f = fitness(individual, cover_matrix, costs, universeSize);
            scored.emplace_back(f, individual);

            if (f < bestFitness) {
                bestFitness = f;
                bestSolution = individual;
            }
        }

        // Sort by fitness (minimize)
        sort(scored.begin(), scored.end());

        // Selection (top 50%)
        vector<vector<int>> newPopulation;
        for (int i = 0; i < populationSize / 2; ++i)
            newPopulation.push_back(scored[i].second);

        // Crossover
        while (newPopulation.size() < populationSize) {
            int a = rand() % (populationSize / 2);
            int b = rand() % (populationSize / 2);
            vector<int> parent1 = scored[a].second;
            vector<int> parent2 = scored[b].second;
            vector<int> child = parent1;

            if (prob(gen) < crossoverRate) {
                int point = rand() % numSubsets;
                for (int j = point; j < numSubsets; ++j)
                    child[j] = parent2[j];
            }

            // Mutation
            for (int j = 0; j < numSubsets; ++j) {
                if (prob(gen) < mutationRate)
                    child[j] = 1 - child[j];
            }

            newPopulation.push_back(child);
        }

        population = newPopulation;
    }

    return bestSolution;
}

// Display the final solution
void GeneticSetCover::printSolution(const vector<int> &solution) {
    cout << "Solution found using Genetic Algorithm: ";
    for (int i = 0; i < solution.size(); ++i) {
        if (solution[i]) cout << i << " ";
    }
    cout << "\nSelected subsets and their elements:\n";

    double totalCost = 0.0;
    set<int> covered;

    for (int i = 0; i < solution.size(); ++i) {
        if (solution[i]) {
            cout << "Subset " << i << " : { ";
            for (int j = 0; j < universeSize; ++j) {
                if (cover_matrix[j][i] == 1) {
                    cout << j << " ";
                    covered.insert(j);
                }
            }
            cout << "} (Cost: " << costs[i] << ")\n";
            totalCost += costs[i];
        }
    }

    cout << "Total cost of the solution: " << totalCost << endl;
    cout << "Covered elements: " << covered.size() << " / " << universeSize << endl;

    if (covered.size() < universeSize) {
        cout << "⚠️ Warning: The solution does not cover the entire universe!" << endl;
    }
}
