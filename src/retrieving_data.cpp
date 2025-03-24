#include "retrieving_data.h"

// Constructeur par défaut
SCPInstance::SCPInstance() : num_elements(0), num_subsets(0) {}

// Chargement des données depuis un fichier
bool SCPInstance::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << endl;
        return false;
    }

    // Lecture du nombre d'éléments et de sous-ensembles
    file >> num_elements >> num_subsets;

    // Lecture des coûts des sous-ensembles
    costs.resize(num_subsets);
    for (int j = 0; j < num_subsets; ++j) {
        file >> costs[j];
    }

    // Lecture des sous-ensembles
    subsets.resize(num_subsets);
    for (int j = 0; j < num_subsets; ++j) {
        int num_elements_in_subset;
        file >> num_elements_in_subset; // Nombre d'éléments couverts par le sous-ensemble

        subsets[j].resize(num_elements_in_subset);
        for (int k = 0; k < num_elements_in_subset; ++k) {
            file >> subsets[j][k];
            subsets[j][k]--; // Ajustement (index OR-Library commence à 1)
        }
    }

    file.close();
    return true;
}

// Affichage des données chargées
void SCPInstance::print() const {
    cout << "Nombre d'éléments : " << num_elements << endl;
    cout << "Nombre de sous-ensembles : " << num_subsets << endl;

    cout << "\nCoûts des sous-ensembles : ";
    for (int cost : costs) {
        cout << cost << " ";
    }
    cout << endl;

    cout << "\nSous-ensembles (indices des éléments couverts) :\n";
    for (size_t j = 0; j < subsets.size(); ++j) {
        cout << "Sous-ensemble " << j << " : ";
        for (int element : subsets[j]) {
            cout << element << " "; // Affichage indexé à 1
        }
        cout << endl;
    }
}
