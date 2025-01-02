#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Graph {
private:
    unordered_map<int, vector<int>> adjList; // Adjacency List Representation
    vector<pair<int, int>> bridges;         // To store all bridges

    // Helper function for DFS
    void dfs(int vertex, int parent, vector<bool> &visited, vector<int> &disc, vector<int> &low, int &time) {
        visited[vertex] = true;
        disc[vertex] = low[vertex] = ++time;

        for (int neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                dfs(neighbor, vertex, visited, disc, low, time);

                // Update low value
                low[vertex] = min(low[vertex], low[neighbor]);

                // Check if the edge is a bridge
                if (low[neighbor] > disc[vertex]) {
                    bridges.push_back({vertex, neighbor});
                }
            } else if (neighbor != parent) {
                // Update low value for back edge
                low[vertex] = min(low[vertex], disc[neighbor]);
            }
        }
    }

public:
    // Add an edge to the graph
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Since it's an undirected graph
    }

    // Function to find all bridges in the graph
    vector<pair<int, int>> findBridges(int numVertices) {
        vector<bool> visited(numVertices, false);
        vector<int> disc(numVertices, -1);  // Discovery times
        vector<int> low(numVertices, -1);   // Low values
        int time = 0;                       // Time tracker

        // Perform DFS for all vertices
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                dfs(i, -1, visited, disc, low, time);
            }
        }

        return bridges;
    }
};

int main() {
    Graph graph;

    int numVertices, numEdges;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    // Find and print bridges
    vector<pair<int, int>> bridges = graph.findBridges(numVertices);
    cout << "Bridges in the graph:\n";
    for (auto &bridge : bridges) {
        cout << bridge.first << " - " << bridge.second << "\n";
    }

    return 0;
}
