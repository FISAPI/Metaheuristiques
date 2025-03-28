#include <iostream>
#include <Windows.h>
#include <cstdio>
#include "retrieving_data.h"
#include "algorithme_glouton.h"
#include "algorithm_dual_fitting.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: ./scp_solver <fichier_scp> --glouton | --dualfitting" << endl;
        return 1;
    }
    // Activer l'UTF-8 pour la console Windows
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    string filename = "";
    string method = "";

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg.rfind("--", 0) == 0) { // Vérifie si l'argument commence par "--"
            if (i == 1) {
                filename = arg.substr(2); // Retire "--" pour récupérer le nom du fichier
            } else {
                method = arg.substr(2); // Retire "--" pour récupérer le nom du fichier
            }
        }
    }

    // Vérification de la validité du fichier
    if (filename.empty()) {
        cerr << "Erreur: Aucun fichier spécifié. Utilisation : ./scp_solver --nom_du_fichier [--glouton]" << endl;
        return 1;
    }

    SCPInstance instance;

    if (!instance.loadFromFile(filename)) {
        cout << "Erreur lors du chargement des données.\n";
        return 1;
    }

    cout << "Données chargées avec succès !\n";

    if (!instance.loadFromFile(filename)) {
        cerr << "Erreur lors de la lecture du fichier : " << filename << endl;
        return 1;
    }

    vector<int> solution;

    if (method == "glouton") {
        cout << "Exécution de l'algorithme glouton avec les données chargées...\n";

        // Récupération des données depuis `instance`
        int universeSize = instance.getNumElements();  // Nombre total d'éléments
        // vector<double> costs(instance.getCosts().begin(), instance.getCosts().end()); // Conversion en `double`

        // Instanciation et exécution de l'algorithme glouton
        GreedySetCover solver(instance.getNumElements(), instance.getNumSubsets(), instance.getCoverMatrix(), instance.getCosts());
        vector<int> solution = solver.solve();
        solver.printSolution(solution);
    }
    else if (method == "dualfitting") {
        cout << "Exécution de l'approximation dual_fitting avec les données chargées...\n";

        // Récupération des données depuis `instance`
        int universeSize = instance.getNumElements();  // Nombre total d'éléments
        // vector<double> costs(instance.getCosts().begin(), instance.getCosts().end()); // Conversion en `double`
        DualFittingSetCover solver(instance.getNumElements(), instance.getCoverMatrix(), instance.getCosts());
        solution = solver.solve();
        solver.printSolution(solution);
    }
    else {
        cerr << "Méthode inconnue. Utilisez --glouton ou --dualfitting" << endl;
        return 1;
    }




    return 0;
}