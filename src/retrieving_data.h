#ifndef RETRIEVING_DATA_H
#define RETRIEVING_DATA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class SCPInstance {
private:
    int num_elements;  // Nombre total d'éléments (m)
    int num_subsets;   // Nombre total de sous-ensembles (n)
    vector<int> costs; // Coût de chaque sous-ensemble
    vector<vector<int>> subsets; // Matrice des sous-ensembles et leurs éléments

public:
    // Constructeur
    SCPInstance();

    // Chargement des données depuis un fichier
    bool loadFromFile(const string& filename);

    // Affichage des données
    void print() const;

    // Getters pour récupérer les données (si besoin)
    int getNumElements() const { return num_elements; }
    int getNumSubsets() const { return num_subsets; }
    const vector<int>& getCosts() const { return costs; }
    const vector<vector<int>>& getSubsets() const { return subsets; }
};

#endif // RETRIEVING_DATA_H
