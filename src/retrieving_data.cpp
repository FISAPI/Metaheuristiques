#include "retrieving_data.h"
#include <iostream>
#include <fstream>

using namespace std;

// Default constructor
SCPInstance::SCPInstance() : num_elements(0), num_subsets(0) {}

// Load data from a file
bool SCPInstance::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file " << filename << endl;
        return false;
    }

    cout << "File " << filename << " opened successfully.\n";

    // Read the number of elements and subsets
    file >> num_elements >> num_subsets;

    if (file.fail()) {
        cerr << "Error: Unable to read values for num_elements and num_subsets.\n";
        return false;
    }

    cout << "Number of rows: " << num_elements << endl;
    cout << "Number of columns: " << num_subsets << endl;

    // Read subset costs
    costs.resize(num_subsets);
    for (int j = 0; j < num_subsets; ++j) {
        file >> costs[j];
    }

    // Initialize the binary coverage matrix (m x n)
    cover_matrix.assign(num_elements + 1, vector<int>(num_subsets, 0));

    // Read subsets and populate the matrix
    for (int j = 0; j < num_elements; ++j) {
        int num_elements_in_line;
        file >> num_elements_in_line; // Number of elements covered by this subset

        for (int k = 0; k < num_elements_in_line; ++k) {
            int elem;
            file >> elem;
            cover_matrix[j][elem] = 1; // Mark that element `elem` belongs to subset `j`
        }
    }

    file.close();
    return true;
}

// Display loaded data
void SCPInstance::print() const {
    cout << "Number of elements: " << num_elements << endl;
    cout << "Number of subsets: " << num_subsets << endl;

    cout << "\nSubset costs: ";
    for (double cost : costs) {
        cout << cost << " ";
    }
    cout << endl;

    // Display the coverage matrix
    for (size_t i = 0; i < cover_matrix.size(); ++i) {
        for (size_t j = 0; j < cover_matrix[i].size(); ++j) {
            cout << cover_matrix[i][j] << " ";
        }
        cout << endl;
    }
}
