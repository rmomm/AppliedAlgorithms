#pragma once

#include <vector>
#include <chrono>

using namespace std;

struct SortStats {
    size_t comparisons = 0;   
    size_t copies = 0;      
    size_t memory = 0;       
    double time = 0.0;    
};

void MergeSortTopDown(vector<int>& arr, SortStats& stats);

void MergeSortBottomUp(vector<int>& arr, SortStats& stats);
