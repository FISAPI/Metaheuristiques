#include <iostream>
#include <Windows.h>
#include <cstdio>
#include "retrieving_data.h"
#include "greedy_algorithm.h"
#include "dual_fitting_algorithm.h"

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

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg.rfind("--", 0) == 0) { // Check if the argument starts with "--"
            if (i == 1) {
                filename = arg.substr(2); // Remove "--" to get the filename
            } else {
                method = arg.substr(2); // Remove "--" to get the method
            }
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
        vector<int> solution = solver.solve();
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

    return 0;
}
