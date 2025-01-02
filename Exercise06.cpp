#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Graph {
private:
    unordered_map<int, vector<int>> adjList; // Adjacency List Representation

public:
    // Add an edge to the graph
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Since it's an undirected graph
    }

    // Helper function to perform DFS and find connected components
    void dfs(int vertex, unordered_set<int> &visited, vector<int> &component) {
        visited.insert(vertex);
        component.push_back(vertex);

        for (int neighbor : adjList[vertex]) {
            if (visited.find(neighbor) == visited.end()) {
                dfs(neighbor, visited, component);
            }
        }
    }

    // Function to find all connected components
    vector<vector<int>> findConnectedComponents() {
        unordered_set<int> visited;
        vector<vector<int>> connectedComponents;

        for (const auto &pair : adjList) {
            int vertex = pair.first;
            if (visited.find(vertex) == visited.end()) {
                vector<int> component;
                dfs(vertex, visited, component);
                connectedComponents.push_back(component);
            }
        }

        return connectedComponents;
    }
};

int main() {
    Graph graph;

    // Input edges
    int numEdges;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    // Find connected components
    vector<vector<int>> connectedComponents = graph.findConnectedComponents();

    // Print connected components
    cout << "Connected Components:\n";
    for (const auto &component : connectedComponents) {
        for (int vertex : component) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    return 0;
}
