#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Graph {
protected:
	vector<vector<double>> adjMatrix;

public:
	Graph(int n = 0) : adjMatrix(n, vector<double>(n, 0)) {}
	virtual ~Graph() = default;

	int VertexCount() const { return adjMatrix.size(); }

	void addVertex() {
		int n = VertexCount();
		for (auto& row : adjMatrix)
			row.push_back(0);
		adjMatrix.push_back(vector<double>(n + 1, 0));
	}

	bool removeVertex(int v) {
		if (v < 1 || v > VertexCount())
			return false;
		int i = v - 1;
		adjMatrix.erase(adjMatrix.begin() + i);
		for (auto& row : adjMatrix)
			row.erase(row.begin() + i);
		return true;
	}

	virtual bool addEdge(int u, int v, double w = 1.0) = 0;
	virtual bool removeEdge(int u, int v) = 0;

	void printMatrix() const {
		int n = VertexCount();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << adjMatrix[i][j] << " ";
			}
			cout << "\n";
		}
	}
};


class UndirectedGraph : public Graph {
public:
	UndirectedGraph(int n = 0) : Graph(n) {}

	bool addEdge(int u, int v, double w = 1.0) override {
		if (u < 1 || v < 1 || u > VertexCount() || v > VertexCount() || u == v)
			return false;
		adjMatrix[u][v] = 1;
		adjMatrix[v][u] = 1;
		return true;
	}

	bool removeEdge(int u, int v) override {
		if (u < 1 || v < 1 || u > VertexCount() || v > VertexCount())
			return false;
		adjMatrix[u][v] = 0;
		adjMatrix[v][u] = 0;
		return true;
	}
};


class DirectedGraph : public Graph {
public:
	DirectedGraph (int n = 0) : Graph(n) {}

	bool addEdge(int u, int v, double w = 1.0) override {
		if (u < 1 || v < 1 || u > VertexCount() || v > VertexCount() || u == v)
			return false;
		adjMatrix[u][v] = 1;
		return true;
	}

	bool removeEdge(int u, int v) override {
		if (u < 1 || v < 1 || u > VertexCount() || v > VertexCount())
			return false;
		adjMatrix[u][v] = 0;
		return true;
	}

};

class WeightedDirectedGraph : public Graph {
public:
	WeightedDirectedGraph ( int n = 0) : Graph (n){}

	bool addEdge(int u, int v, double w = 1.0) override {
		if (u < 1 || v < 1 || u > VertexCount() || v > VertexCount() || u == v || w <= 0)
			return false;
		adjMatrix[u][v] = w;
		return true;
	}

	bool removeEdge(int u, int v) override {
		if (u < 1 || v < 1 || u > VertexCount() || v > VertexCount())
			return false;
		adjMatrix[u][v] = 0.0;
		return true;
	}

	vector<vector<pair<int, double>>> convToAdjList() const {
		vector<vector<pair<int, double>>> adjList(VertexCount());
		for (int i = 0; i < VertexCount(); ++i) {
			for (int j = 0; j < VertexCount(); ++j) {
				if (adjMatrix[i][j] != 0)
					adjList[i].push_back({ j, adjMatrix[i][j] });
			}
		}
		return adjList;
	}

	void printAdjList() const {
		for (int i = 0; i < VertexCount(); ++i) {
			for (int j = 0; j < VertexCount(); ++j) {
				if (adjMatrix[i][j] != 0) {
					cout << i << " -> " << j << " (weight: " << adjMatrix[i][j] << ")\n";
				}
			}
		}
	}


};

class ErdosRenyiModel : public Graph {
public:
	ErdosRenyiModel(int n = 0) : Graph(n) {}

	static DirectedGraph generateDir(int n, double p) {
		DirectedGraph g(n);
		srand(time(nullptr));
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (i != j && (double)rand() / RAND_MAX < p)
					g.addEdge(i, j);
		return g;
	}

	static UndirectedGraph generateUndir(int n, double p) {
		UndirectedGraph g(n);
		srand(time(nullptr));
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
				if ((double)rand() / RAND_MAX < p)
					g.addEdge(i, j);
		return g;
	}

	static WeightedDirectedGraph generateWG(int n, double p, int minW, int maxW) {
		WeightedDirectedGraph g(n);
		srand(time(nullptr));
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (i != j && (double)rand() / RAND_MAX < p) {
					int w = minW + rand() % (maxW - minW + 1);
					g.addEdge(i, j, w);
				}
		return g;
	}

	bool addEdge(int u, int v, double w = 1.0) override { return false; }
	bool removeEdge(int u, int v) override { return false; }
};


int main() {
	srand(time(nullptr));

	cout << "Directed graph:" << endl;
	DirectedGraph dg(5);
	dg.addEdge(0, 1);
	dg.addEdge(2, 2);
	dg.addEdge(2, 4);
	dg.addEdge(3, 1);
	dg.addVertex();
	dg.removeEdge(1, 2);
	dg.printMatrix();

	cout << "Undirected graph:" << endl;
	UndirectedGraph ug(6);
	ug.addEdge(0, 1);
	ug.addEdge(1, 1);
	ug.addEdge(2, 3);
	ug.addEdge(4, 5);
	ug.addVertex();
	ug.removeVertex(5);
	ug.printMatrix();

	cout << "Weighted directed graph:" << endl;
	WeightedDirectedGraph wg(7);
	wg.addEdge(0, 1, 4);
	wg.addEdge(0, 3, 5);
	wg.addEdge(1, 5, 3);
	wg.addEdge(4, 3, 6);
	wg.addEdge(4, 0, 2);

	wg.printMatrix();

	cout << "Adjacency list (WeightedDirectedGraph):" << endl;
	wg.printAdjList();

	cout << "Random graphs based on the Erdos–Renyi Model" << endl;
	auto randdir = ErdosRenyiModel::generateDir(3, 0.6);
	cout << "Random directed graph:" << endl;
	randdir.printMatrix();

	auto randundir = ErdosRenyiModel::generateUndir(6, 0.5);
	cout << "Random undirected graph:" << endl;
	randundir.printMatrix();

	auto randwg = ErdosRenyiModel::generateWG(6, 0.3, 1, 7);
	cout << "Random weighted graph:" << endl;
	randwg.printMatrix();
	cout << "Adjacency list:" << endl;
	randwg.printAdjList();

	return 0;
}
