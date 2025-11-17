#include "MergeSort.h"
#include <algorithm> 

using namespace std;

void Merge(vector<int>& arr, int left, int mid, int right, SortStats& stats) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    stats.memory += (n1 + n2) * sizeof(int);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
        stats.copies++;
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
        stats.copies++;
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        stats.comparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
        stats.copies++;
    }

    while (i < n1) {
        arr[k++] = L[i++];
        stats.copies++;
    }
    while (j < n2) {
        arr[k++] = R[j++];
        stats.copies++;
    }
}


void MergeSortTopDownRec(vector<int>& arr, int left, int right, SortStats& stats) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    MergeSortTopDownRec(arr, left, mid, stats);
    MergeSortTopDownRec(arr, mid + 1, right, stats);
    Merge(arr, left, mid, right, stats);
}

void MergeSortTopDown(vector<int>& arr, SortStats& stats) {
    auto start = chrono::high_resolution_clock::now();
    MergeSortTopDownRec(arr, 0, arr.size() - 1, stats);
    auto end = chrono::high_resolution_clock::now();
    stats.time = chrono::duration<double>(end - start).count();
}

void MergeSortBottomUp(vector<int>& arr, SortStats& stats) {
    auto start = chrono::high_resolution_clock::now();
    int n = arr.size();
    vector<int> aux(n);
    stats.memory += n * sizeof(int);

    for (int sz = 1; sz < n; sz *= 2) {
        for (int left = 0; left < n - sz; left += 2 * sz) {
            int mid = left + sz - 1;
            int right = min(left + 2 * sz - 1, n - 1);

            int i = left, j = mid + 1, k = left;
            for (int t = left; t <= right; ++t) {
                aux[t] = arr[t];
                stats.copies++;
            }

            while (i <= mid && j <= right) {
                stats.comparisons++;
                if (aux[i] <= aux[j]) {
                    arr[k++] = aux[i++];
                }
                else {
                    arr[k++] = aux[j++];
                }
                stats.copies++;
            }
            while (i <= mid) arr[k++] = aux[i++], stats.copies++;
            while (j <= right) arr[k++] = aux[j++], stats.copies++;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    stats.time = chrono::duration<double>(end - start).count();
}


