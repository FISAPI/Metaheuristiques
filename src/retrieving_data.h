#ifndef RETRIEVING_DATA_H
#define RETRIEVING_DATA_H

#include <vector>
#include <string>

class SCPInstance {
private:
    int num_elements;  // Nombre total d'éléments
    int num_subsets;   // Nombre total de sous-ensembles
    std::vector<std::vector<int>> cover_matrix; // Matrice binaire A (m x n)
    std::vector<double> costs;  // Coûts des sous-ensembles

public:
    SCPInstance();
    bool loadFromFile(const std::string &filename);
    void print() const;

    // Méthodes pour récupérer les données
    int getNumElements() const { return num_elements; }
    int getNumSubsets() const { return num_subsets; }
    const std::vector<std::vector<int>>& getCoverMatrix() const { return cover_matrix; }
    const std::vector<double>& getCosts() const { return costs; }
};

#endif
