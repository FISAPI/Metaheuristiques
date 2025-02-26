#include "SetCover.h"
#include <iostream>
#include <fstream>

std::vector<Subset> subsets;
std::vector<int> universe;

void readData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier !" << std::endl;
        return;
    }
    int m, n;
    file >> m >> n;
    universe.resize(m);
    subsets.resize(n);
    
    for (int i = 0; i < n; i++) {
        subsets[i].elements.clear();
        for (int j = 0; j < m; j++) {
            int value;
            file >> value;
            if (value > 0) {
                subsets[i].elements.push_back(j);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        file >> subsets[i].variableCost;
    }
    
    for (int i = 0; i < n; i++) {
        file >> subsets[i].fixedCost;
    }
    file.close();
}