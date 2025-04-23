#include <iostream>
#include <Windows.h>
#include <cstdio>
#include <chrono>
#include <numeric>
#include "retrieving_data.h"
#include "greedy_algorithm.h"
#include "dual_fitting_algorithm.h"
#include "metaheuristic.h"
#include "genetic_algorithm.h"
#include "local_search.h"
#include "feasibility_check.h"
#include "tabu_search.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: ./scp_solver <scp_file> --greedy | --dualfitting | --metaheuristic | --genetic | --tabu [--ls]" << endl;
        return 1;
    }

    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    string filename;
    string method;
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
        else if (arg == "--metaheuristic") {
            method = "metaheuristic";
        }
        else if (arg == "--genetic") {
            method = "genetic";
        }
        else if (arg == "--tabu") {
            method = "tabu";
        }
        else if (i == 1) {
            filename = arg;
        }
    }

    if (filename.empty()) {
        cerr << "Error: No file specified. Usage: ./scp_solver <scp_file> [--greedy|--dualfitting|--metaheuristic|--genetic|--tabu] [--ls]" << endl;
        return 1;
    }

    SCPInstance instance;
    if (!instance.loadFromFile(filename)) {
        cerr << "Error loading data from " << filename << endl;
        return 1;
    }
    cout << "Data successfully loaded!\n";

    vector<int> solution;
    auto& A     = instance.getCoverMatrix();
    auto& costs = instance.getCosts();
    int m       = instance.getNumElements();

    // Initial solution
    if (method == "greedy") {
        cout << "Running the greedy algorithm for initial solution...\n";
        GreedySetCover solver(m, instance.getNumSubsets(), A, costs);
        solution = solver.solve();
        solver.printSolution(solution);
    }
    else if (method == "dualfitting") {
        cout << "Running the dual fitting approximation with the loaded data...\n";
        DualFittingSetCover solver(m, A, costs);
        solution = solver.solve();
        solver.printSolution(solution);
    }
    else if (method == "metaheuristic" || method == "tabu") {
        cout << "Running the metaheuristic algorithm with the loaded data...\n";
        Metaheuristic solver(m, instance.getNumSubsets(), A, costs);
        solution = solver.solve();
        solver.printSolution(solution);
    }
    else if (method == "genetic") {
        cout << "Running the genetic algorithm with the loaded data...\n";
        GeneticSetCover solver(m, instance.getNumSubsets(), A, costs);
        solution = solver.solve();
        solver.printSolution(solution);
    }
    else {
        cerr << "Unknown method. Use --greedy, --dualfitting, --metaheuristic, --genetic or --tabu" << endl;
        return 1;
    }

    // Feasibility check
    if (!isFeasible(m, A, solution)) {
        cerr << "Solution initiale non faisable !" << endl;
        return 1;
    }

    // Apply Tabu Search if requested
    if (method == "tabu") {
        cout << "\nRunning Tabu Search...\n";
        TabuSearch ts(m, A, costs);
        auto improved = ts.run(solution);
        cout << "--- Solution after Tabu Search ---\n";
        for (int idx : improved) cout << idx << " ";
        double costTS = accumulate(improved.begin(), improved.end(), 0.0,
            [&](double s, int j){ return s + costs[j]; });
        cout << "\nTotal cost = " << costTS << "\n";
        solution = improved;
    }

    // Optional local search post-processing
    if (useLS && method != "tabu") {
        cout << "\n--- Starting Local Search post-processing ---\n";
        bool improved = true;
        auto t0 = chrono::high_resolution_clock::now();
        while (improved) {
            improved = false;
            if (tryRemove(m, A, costs, solution)) improved = true;
            if (tryAdd   (m, A, costs, solution)) improved = true;
            if (trySwap  (m, A, costs, solution)) improved = true;
        }
        auto t1 = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(t1 - t0).count();
        cout << "Local Search completed (CPU: " << elapsed << "s)\n";
        cout << "Solution indices: ";
        for (int idx : solution) cout << idx << " ";
        double costLS = accumulate(solution.begin(), solution.end(), 0.0,
            [&](double s, int j){ return s + costs[j]; });
        cout << "\nTotal cost = " << costLS << "\n";
    }

    return 0;
}
