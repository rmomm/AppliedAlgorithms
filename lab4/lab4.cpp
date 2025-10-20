#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include "UnionFind.h"

using namespace std;
using namespace std::chrono;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

int Kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    int mst_weight = 0;

    for (auto& e : edges) {
        if (uf.Find(e.u) != uf.Find(e.v)) {
            mst_weight += e.w;
            uf.Unite(e.u, e.v);
        }
    }
    return mst_weight;
}

vector<Edge> generateGraph(int n, int E) {
    vector<Edge> edges;
    for (int i = 0; i < E; ++i) {
        int u = rand() % n;
        int v = rand() % n;
        while (v == u) v = rand() % n;
        int w = rand() % 100 + 1;
        edges.push_back({ u, v, w });
    }
    return edges;
}

int main() {
    srand(time(0));
    int vertices[] = { 5, 10, 20, 50, 100, 200, 500 };
    int edges_count[] = { 5, 10, 20, 50, 100, 200, 500 };

    int size = sizeof(vertices) / sizeof(vertices[0]);

    cout << "n\tE\tDensity\t\tMST Weight\tTime (microseconds)" << endl;
    cout << "-------------------------------------------------------" << endl;

    for (int i = 0; i < size; ++i) {
        int n = vertices[i];
        int E = edges_count[i];

        auto edges = generateGraph(n, E);

        double density = (double)E / (n * (n - 1) / 2.0);

        auto start = high_resolution_clock::now();
        int mst_weight = Kruskal(n, edges);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        cout << setw(5) << n
            << setw(8) << E
            << setw(12) << fixed << setprecision(3) << density
            << setw(12) << mst_weight
            << setw(18) << duration.count()
            << endl;
    }

    return 0;
}