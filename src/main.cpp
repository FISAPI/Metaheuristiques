#include <iostream>
#include <Windows.h>
#include <cstdio>
#include "retrieving_data.h"

using namespace std;

int main() {
    // Activer l'UTF-8 pour la console Windows
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    SCPInstance instance;
    string filename = "datas/scp42.txt"; // Chemin du fichier

    if (instance.loadFromFile(filename)) {
        cout << "Données chargées avec succès !\n";
        instance.print();
    } else {
        cout << "Erreur lors du chargement des données.\n";
    }

    return 0;
}
