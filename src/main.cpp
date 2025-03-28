#include <iostream>
#include <Windows.h>
#include <cstdio>
#include "retrieving_data.h"
#include "algorithme_glouton.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Activer l'UTF-8 pour la console Windows
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    SCPInstance instance;
    string filename = "datas/scp42.txt"; // Chemin du fichier

    if (!instance.loadFromFile(filename)) {
        cout << "Erreur lors du chargement des données.\n";
        return 1;
    }

    cout << "Données chargées avec succès !\n";
    // instance.print();

    // Vérifier si le mode glouton est activé
    bool modeGlouton = (argc > 1 && string(argv[1]) == "--glouton");

    if (modeGlouton) {
        cout << "Exécution de l'algorithme glouton avec les données chargées...\n";

        // Récupération des données depuis `instance`
        int universeSize = instance.getNumElements();  // Nombre total d'éléments
        // vector<vector<int>> subsets = instance.getSubsets(); // Liste des sous-ensembles
        vector<double> costs(instance.getCosts().begin(), instance.getCosts().end()); // Conversion en `double`

        // cout << "Nombre total de sous-ensembles chargés : " << instance.getNumSubsets() << endl;

        // // Instanciation et exécution de l'algorithme glouton
        // GreedySetCover solver(universeSize, subsets, costs);
        // vector<int> solution = solver.solve();
        // solver.printSolution(solution);

        // Instanciation et exécution de l'algorithme glouton
        GreedySetCover solver(instance.getNumElements(), instance.getNumSubsets(), instance.getCoverMatrix(), instance.getCosts());
        vector<int> solution = solver.solve();
        solver.printSolution(solution);
    }

    return 0;
}