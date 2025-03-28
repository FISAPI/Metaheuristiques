#include "retrieving_data.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructeur par défaut
SCPInstance::SCPInstance() : num_elements(0), num_subsets(0) {}

// Chargement des données depuis un fichier
bool SCPInstance::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << endl;
        return false;
    }

	cout << "Fichier " << filename << " ouvert avec succès.\n";

    // Lecture du nombre d'éléments et de sous-ensembles
    file >> num_elements >> num_subsets;

	if (file.fail()) {
        cerr << "Erreur: Impossible de lire les valeurs de num_elements et num_subsets.\n";
        return false;
    }

    cout << "Nombre de ligne : " << num_elements << endl;
    cout << "Nombre de colonnes : " << num_subsets << endl;

    // Lecture des coûts des sous-ensembles
    costs.resize(num_subsets);
    for (int j = 0; j < num_subsets; ++j) {
        file >> costs[j];
    }

    // Initialisation de la matrice binaire de couverture (m x n)
    cover_matrix.assign(num_elements+1, vector<int>(num_subsets, 0));

    // Lecture des sous-ensembles et remplissage de la matrice
    //for (int j = 0; j < num_subsets; ++j) {
    //    int num_elements_in_subset;
    //    file >> num_elements_in_subset; // Nombre d'éléments couverts par le sous-ensemble

    //    for (int k = 0; k < num_elements_in_subset; ++k) {
    //        int elem;
    //        file >> elem;
    //        cover_matrix[elem][j] = 1; // Marquer que l'élément `elem` appartient au sous-ensemble `j`
    //    }
    //}

	// Lecture des sous-ensembles et remplissage de la matrice
    for (int j = 0; j < num_elements; ++j) {
        int num_elements_in_line;
        file >> num_elements_in_line; // Nombre d'éléments couverts par le sous-ensemble

        for (int k = 0; k < num_elements_in_line; ++k) {
            int elem;
            file >> elem;
            cover_matrix[j][elem] = 1; // Marquer que l'élément `elem` appartient au sous-ensemble `j`
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
    for (double cost : costs) {
        cout << cost << " ";
    }
    cout << endl;

    for (size_t i = 0; i < cover_matrix.size(); ++i) {
        for (size_t j = 0; j < cover_matrix[i].size(); ++j) {
            cout << cover_matrix[i][j] << " ";
        }
        cout << endl;
    }
}
