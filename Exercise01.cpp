#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Graph {
private:
    // Adjacency List Representation
    unordered_map<int, vector<int>> adjList;

    // Adjacency Matrix Representation
    vector<vector<int>> adjMatrix;
    int numVertices;

public:
    // Constructor to initialize graph with a fixed number of vertices
    Graph(int vertices) {
        numVertices = vertices;
        adjMatrix.resize(vertices, vector<int>(vertices, 0));
    }

    // Add an edge to the graph
    void addEdge(int u, int v) {
        // Adding edge to the adjacency list
        adjList[u].push_back(v);
        adjList[v].push_back(u); // For undirected graph

        // Adding edge to the adjacency matrix
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // For undirected graph
    }

    // Print adjacency list
    void printAdjList() {
        cout << "Adjacency List:\n";
        for (const auto &pair : adjList) {
            cout << pair.first << ": ";
            for (int neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Print adjacency matrix
    void printAdjMatrix() {
        cout << "Adjacency Matrix:\n";
        for (const auto &row : adjMatrix) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Create a graph with 5 vertices
    Graph graph(5);

    // Add edges
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 0);

    // Print graph representations
    graph.printAdjList();
    graph.printAdjMatrix();

    return 0;
}
