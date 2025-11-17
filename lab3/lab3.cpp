#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

struct Graph {
    int n;
    vector<vector<int>> adjMatrix;
    vector<vector<int>> adjList;

    Graph(int vertices) {
        n = vertices;
        adjMatrix.assign(n, vector<int>(n, 0));
        adjList.assign(n, {});
    }

    void generateRandom(double p) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double r = (double)rand() / RAND_MAX;
                if (r < p) {
                    adjMatrix[i][j] = adjMatrix[j][i] = 1;
                    adjList[i].push_back(j);
                    adjList[j].push_back(i);
                }
            }
        }
    }
};

void bfs_list(const Graph& g, int start) {
    vector<bool> visited(g.n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : g.adjList[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
}

void bfs_matrix(const Graph& g, int start) {
    vector<bool> visited(g.n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int i = 0; i < g.n; i++) {
            if (g.adjMatrix[v][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

void dfs_list_r(const Graph& g, int v, vector<bool>& visited) {
    visited[v] = true;
    for (int u : g.adjList[v]) {
        if (!visited[u]) {
            dfs_list_r(g, u, visited);
        }
    }
}

void dfs_list(const Graph& g, int start) {
    vector<bool> visited(g.n, false);
    dfs_list_r(g, start, visited);
}

void dfs_matrix_r(const Graph& g, int v, vector<bool>& visited) {
    visited[v] = true;
    for (int i = 0; i < g.n; i++) {
        if (g.adjMatrix[v][i] && !visited[i]) {
            dfs_matrix_r(g, i, visited);
        }
    }
}

void dfs_matrix(const Graph& g, int start) {
    vector<bool> visited(g.n, false);
    dfs_matrix_r(g, start, visited);
}

void runTest(int n, double p) {
    Graph g(n);
    g.generateRandom(p);

    const int REPEAT = 100;
    double bfslistT, bfsmatrixT, dfslistT, dfsmatrixT;

    auto t1 = high_resolution_clock::now();
    for (int i = 0; i < REPEAT; i++) bfs_list(g, 0);
    auto t2 = high_resolution_clock::now();
    bfslistT = duration_cast<microseconds>(t2 - t1).count() / (double)REPEAT;

    t1 = high_resolution_clock::now();
    for (int i = 0; i < REPEAT; i++) bfs_matrix(g, 0);
    t2 = high_resolution_clock::now();
    bfsmatrixT = duration_cast<microseconds>(t2 - t1).count() / (double)REPEAT;

    t1 = high_resolution_clock::now();
    for (int i = 0; i < REPEAT; i++) dfs_list(g, 0);
    t2 = high_resolution_clock::now();
    dfslistT = duration_cast<microseconds>(t2 - t1).count() / (double)REPEAT;

    t1 = high_resolution_clock::now();
    for (int i = 0; i < REPEAT; i++) dfs_matrix(g, 0);
    t2 = high_resolution_clock::now();
    dfsmatrixT = duration_cast<microseconds>(t2 - t1).count() / (double)REPEAT;

    cout << setw(4) << n
        << " " << setw(8) << fixed << setprecision(4) << p
        << " " << setw(10) << fixed << setprecision(3) << bfslistT
        << " " << setw(12) << fixed << setprecision(3) << bfsmatrixT
        << " " << setw(13) << fixed << setprecision(3) << dfslistT
        << " " << setw(14) << fixed << setprecision(3) << dfsmatrixT
        << endl;
}

int main() {
    srand(time(NULL));

    cout << "n       p      BFS_List       BFS_Matrix       DFS_List      DFS_Matrix" << endl;
    cout << "-----------------------------------------------------------------------" << endl;

    int size[] = { 5, 10, 50, 100 };
    double probs[] = { 0.01, 0.1, 0.2, 0.5, 0.7 };

    for (int n : size) {
        for (double p : probs) {
            runTest(n, p);
        }
    }

    return 0;

}