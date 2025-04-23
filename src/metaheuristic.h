#ifndef METAHEURISTIC_H
#define METAHEURISTIC_H

#include <vector>

class Metaheuristic {
private:
    int universeSize;
    int numSubsets;
    std::vector<std::vector<int>> cover_matrix;
    std::vector<double> costs;

public:
    Metaheuristic(int universeSize, int numSubsets,
                    const std::vector<std::vector<int>> &cover_matrix,
                    const std::vector<double> &costs);

    std::vector<int> solve(); // Solves using simulated annealing
    void printSolution(const std::vector<int>& solution); // Displays the result
};

#endif // METAHEURISTIC_H
