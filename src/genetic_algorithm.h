#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <vector>

class GeneticSetCover {
private:
    int universeSize;
    int numSubsets;
    std::vector<std::vector<int>> cover_matrix;
    std::vector<double> costs;

    // GA parameters
    int populationSize;
    int generations;
    double crossoverRate;
    double mutationRate;

public:
    GeneticSetCover(int universeSize, int numSubsets,
                    const std::vector<std::vector<int>> &cover_matrix,
                    const std::vector<double> &costs,
                    int populationSize = 100,
                    int generations = 100,
                    double crossoverRate = 0.8,
                    double mutationRate = 0.05);

    std::vector<int> solve();  // run the genetic algorithm
    void printSolution(const std::vector<int> &solution);
};

#endif // GENETIC_ALGORITHM_H
