#include "MergeSortOptimized.h"
#include <algorithm>
#include <chrono>

using namespace std;

static void insertionSortRange(vector<int>& a, int l, int r, SortStats& stats) {
    for (int i = l + 1; i <= r; ++i) {
        int key = a[i];
        stats.copies++;
        int j = i - 1;
        while (j >= l) {
            stats.comparisons++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                stats.copies++;
                j--;
            }
            else break;
        }
        a[j + 1] = key;
        stats.copies++;
    }
}


void MergePass(const vector<int>& src, vector<int>& dst,
    int left, int mid, int right, SortStats& stats)
{
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        stats.comparisons++;
        if (src[i] <= src[j]) dst[k++] = src[i++];
        else dst[k++] = src[j++];
        stats.copies++;
    }
    while (i <= mid) dst[k++] = src[i++], stats.copies++;
    while (j <= right) dst[k++] = src[j++], stats.copies++;
}

void MergeSortBottomUpOptimized(vector<int>& arr, SortStats& stats, size_t cutoff)
{
    auto start = chrono::high_resolution_clock::now();

    int n = arr.size();


    for (int i = 0; i < n; i += cutoff)
        insertionSortRange(arr, i, min(i + (int)cutoff - 1, n - 1), stats);

    vector<int> aux(arr);
    stats.memory += sizeof(int) * n;

    for (int width = cutoff; width < n; width *= 2) {
        for (int left = 0; left < n - width; left += width * 2) {
            int mid = left + width - 1;
            int right = min(left + width * 2 - 1, n - 1);

            MergePass(arr, aux, left, mid, right, stats);
        }
        swap(arr, aux);
    }

    auto end = chrono::high_resolution_clock::now();
    stats.time = chrono::duration<double>(end - start).count();
}
