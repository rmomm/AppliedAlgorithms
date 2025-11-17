#include "MergeSort10.h"
#include <queue>
#include <chrono>
using namespace std;

struct Node {
    int value;
    int arrayIndex;
    int position;
    bool operator>(const Node& other) const {
        return value > other.value;
    }
};

void MergeSort10(vector<int>& arr, SortStats& stats)
{
    auto start = chrono::high_resolution_clock::now();

    int n = arr.size();
    int K = 10;
    int block = (n + K - 1) / K;

    vector<vector<int>> parts(K);
    vector<int> limits;

    for (int i = 0; i < K; i++) {
        int l = i * block;
        int r = min(n, (i + 1) * block);

        if (l >= r) break;

        parts[i] = vector<int>(arr.begin() + l, arr.begin() + r);
        limits.push_back(r - l);

        sort(parts[i].begin(), parts[i].end());
        stats.copies += (r - l);
    }

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    for (int i = 0; i < parts.size(); i++) {
        if (!parts[i].empty())
            pq.push({ parts[i][0], i, 0 });
    }

    int idx = 0;

    while (!pq.empty()) {
        Node x = pq.top();
        pq.pop();
        arr[idx++] = x.value;
        stats.copies++;

        if (x.position + 1 < limits[x.arrayIndex]) {
            pq.push({ parts[x.arrayIndex][x.position + 1], x.arrayIndex, x.position + 1 });
            stats.comparisons++;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    stats.time = chrono::duration<double>(end - start).count();
}
