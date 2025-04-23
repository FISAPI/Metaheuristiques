#include <iostream>
#include <Windows.h>
#include <cstdio>
#include "retrieving_data.h"
#include "greedy_algorithm.h"
#include "dual_fitting_algorithm.h"
#include <chrono>
#include "local_search.h"
#include "feasibility_check.h"
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    // Ensure correct usage
    if (argc < 3) {
        cerr << "Usage: ./scp_solver <scp_file> --greedy | --dualfitting" << endl;
        return 1;
    }


    // Enable UTF-8 output for Windows console
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    string filename = "";
    string method = "";

    bool useLS = false;
	for (int i = 1; i < argc; i++) {
    	string arg = argv[i];
    	if (arg == "--localsearch" || arg == "--ls") {
        	useLS = true;
    	}
    	else if (arg == "--greedy") {
        	method = "greedy";
    	}
    	else if (arg == "--dualfitting") {
        	method = "dualfitting";
    	}
    	else if (i == 1) {
        	filename = arg;
    	}
	}

    // Validate filename
    if (filename.empty()) {
        cerr << "Error: No file specified. Usage: ./scp_solver --file_name [--greedy]" << endl;
        return 1;
    }

    SCPInstance instance;

    // Load data from the specified file
    if (!instance.loadFromFile(filename)) {
        cout << "Error loading data.\n";
        return 1;
    }

    cout << "Data successfully loaded!\n";

    if (!instance.loadFromFile(filename)) {
        cerr << "Error reading the file: " << filename << endl;
        return 1;
    }

    vector<int> solution;

    // Execute the selected algorithm
    if (method == "greedy") {
        cout << "Running the greedy algorithm with the loaded data...\n";

        // Retrieve data from `instance`
        int universeSize = instance.getNumElements();  // Total number of elements

        // Instantiate and execute the greedy algorithm
        GreedySetCover solver(instance.getNumElements(), instance.getNumSubsets(), instance.getCoverMatrix(), instance.getCosts());
        solution = solver.solve();
        solver.printSolution(solution);
    }
    else if (method == "dualfitting") {
        cout << "Running the dual fitting approximation with the loaded data...\n";

        // Retrieve data from `instance`
        int universeSize = instance.getNumElements();  // Total number of elements

        // Instantiate and execute the dual fitting algorithm
        DualFittingSetCover solver(instance.getNumElements(), instance.getCoverMatrix(), instance.getCosts());
        solution = solver.solve();
        solver.printSolution(solution);
    }
    else {
        cerr << "Unknown method. Use --greedy or --dualfitting" << endl;
        return 1;
    }

    if (!isFeasible(instance.getNumElements(),
        instance.getCoverMatrix(),
        solution)) {
    cerr << "Solution initiale non faisable !\n";
    return 1;
    }

    if (useLS) {
        auto& A     = instance.getCoverMatrix();
        auto& costs = instance.getCosts();
        int m       = instance.getNumElements();

        bool improved = true;
        auto t0 = chrono::high_resolution_clock::now();

        while (improved) {
            improved = false;
            // tu peux ordonner tes moves en fonction de ta stratégie
            if (tryRemove(m, A, costs, solution))  improved = true;
            if (tryAdd   (m, A, costs, solution))  improved = true;
            if (trySwap  (m, A, costs, solution))  improved = true;
        }

        auto t1 = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(t1 - t0).count();

        cout << "\n--- Après recherche locale (CPU: "
            << elapsed << "s) ---\n";
        // Réutilise l’affichage de ta classe Greedy ou Dual
        for (int idx : solution) cout << idx << " ";
        cout << "\nCoût total = "
             << accumulate(solution.begin(), solution.end(), 0.0,
                      [&](double s,int j){ return s + costs[j]; })
             << "\n";
    }

    return 0;
}
