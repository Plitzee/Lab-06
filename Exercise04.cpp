#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Graph {
private:
    // Adjacency List Representation
    unordered_map<int, vector<int>> adjList;

public:
    // Add an edge to the graph
    void addEdge(int u, int v, bool isDirected = false) {
        adjList[u].push_back(v);
        if (!isDirected) {
            adjList[v].push_back(u); // For undirected graph
        }
    }

    // Detect cycles in a directed graph using DFS
    bool detectCycleDirectedHelper(int vertex, unordered_map<int, bool> &visited, unordered_map<int, bool> &recStack) {
        visited[vertex] = true;
        recStack[vertex] = true;

        for (int neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                if (detectCycleDirectedHelper(neighbor, visited, recStack)) {
                    return true;
                }
            } else if (recStack[neighbor]) {
                return true; // Back edge detected
            }
        }

        recStack[vertex] = false;
        return false;
    }

    bool detectCycleDirected() {
        unordered_map<int, bool> visited;
        unordered_map<int, bool> recStack;

        for (const auto &pair : adjList) {
            if (!visited[pair.first]) {
                if (detectCycleDirectedHelper(pair.first, visited, recStack)) {
                    return true;
                }
            }
        }

        return false;
    }

    // Detect cycles in an undirected graph using DFS
    bool detectCycleUndirectedHelper(int vertex, int parent, unordered_map<int, bool> &visited) {
        visited[vertex] = true;

        for (int neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                if (detectCycleUndirectedHelper(neighbor, vertex, visited)) {
                    return true;
                }
            } else if (neighbor != parent) {
                return true; // Back edge detected
            }
        }

        return false;
    }

    bool detectCycleUndirected() {
        unordered_map<int, bool> visited;

        for (const auto &pair : adjList) {
            if (!visited[pair.first]) {
                if (detectCycleUndirectedHelper(pair.first, -1, visited)) {
                    return true;
                }
            }
        }

        return false;
    }
};

int main() {
    Graph directedGraph, undirectedGraph;

    // Input edges for directed graph
    cout << "Directed Graph:\n";
    directedGraph.addEdge(0, 1, true);
    directedGraph.addEdge(1, 2, true);
    directedGraph.addEdge(2, 0, true); // Cycle here

    // Input edges for undirected graph
    cout << "Undirected Graph:\n";
    undirectedGraph.addEdge(0, 1);
    undirectedGraph.addEdge(1, 2);
    undirectedGraph.addEdge(2, 0); // Cycle here

    // Detect cycle in directed graph
    if (directedGraph.detectCycleDirected()) {
        cout << "Cycle detected in the directed graph.\n";
    } else {
        cout << "No cycle in the directed graph.\n";
    }

    // Detect cycle in undirected graph
    if (undirectedGraph.detectCycleUndirected()) {
        cout << "Cycle detected in the undirected graph.\n";
    } else {
        cout << "No cycle in the undirected graph.\n";
    }

    return 0;
}
