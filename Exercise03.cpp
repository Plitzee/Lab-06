#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Graph {
private:
    // Adjacency List Representation
    unordered_map<int, vector<int>> adjList;

public:
    // Add an edge to the graph
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // For undirected graph
    }

    // Function to input edges from the user
    void inputEdges(int numEdges) {
        cout << "Enter " << numEdges << " edges (format: u v):\n";
        for (int i = 0; i < numEdges; i++) {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
        }
    }

    // Breadth-First Search (BFS)
    vector<int> bfs(int startVertex) {
        unordered_map<int, bool> visited;
        queue<int> q;
        vector<int> traversalOrder;

        // Start BFS from the startVertex
        q.push(startVertex);
        visited[startVertex] = true;

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            traversalOrder.push_back(currentVertex);

            // Visit all unvisited neighbors
            for (int neighbor : adjList[currentVertex]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }

        return traversalOrder;
    }
};

int main() {
    Graph graph;

    int numEdges, startVertex;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    // Input edges
    graph.inputEdges(numEdges);

    // Start vertex for BFS
    cout << "Enter the starting vertex for BFS: ";
    cin >> startVertex;

    // Perform BFS
    vector<int> traversalOrder = graph.bfs(startVertex);

    // Print BFS traversal order
    cout << "BFS Traversal Order: ";
    for (int vertex : traversalOrder) {
        cout << vertex << " ";
    }
    cout << endl;

    return 0;
}
