#include "MergeSort.h"
#include "data.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    vector<size_t> sizes = { 1000, 5000, 10000, 50000, 100000 };
    vector<DataType> types = { DataType::RANDOM, DataType::SORTED, DataType::REVERSED,
                                   DataType::ALMSORTED, DataType::FEWUN };
    vector<string> typeNames = { "RANDOM", "SORTED", "REVERSED", "ALMOST_SORTED", "FEW_UNIQUE" };

    for (auto n : sizes) {
        cout << "\n Size: " << n << " \n";
  
        cout << left << setw(15) << "Type"
            << setw(15) << "Alg"
            << setw(10) << "Time(s)"
            << setw(12) << "Comparisons"
            << setw(12) << "Copies"
            << setw(10) << "Memory" << "\n";
        cout << string(70, '-') << "\n";

        for (size_t t = 0; t < types.size(); ++t) {
            auto data = generateData(n, types[t]);

            SortStats statsTD, statsBU;
            auto arr1 = data;
            MergeSortTopDown(arr1, statsTD);

            auto arr2 = data;
            MergeSortBottomUp(arr2, statsBU);

            cout << left << setw(15) << typeNames[t]
                << setw(15) << "Top-Down"
                << setw(10) << statsTD.time
                << setw(12) << statsTD.comparisons
                << setw(12) << statsTD.copies
                << setw(10) << statsTD.memory << "\n";

            cout << left << setw(15) << ""
                << setw(15) << "Bottom-Up"
                << setw(10) << statsBU.time
                << setw(12) << statsBU.comparisons
                << setw(12) << statsBU.copies
                << setw(10) << statsBU.memory << "\n";

            cout << string(70, '-') << "\n";
        }
    }

    return 0;
}