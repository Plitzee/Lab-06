#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
using namespace std;

// Class representing a graph
class Graph {
private:
    unordered_map<int, vector<pair<int, int>>> adjList; // Adjacency list (node -> {neighbor, weight})

public:
    // Add an edge to the graph
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // For undirected graph
    }

    // Dijkstra's Algorithm
    vector<int> dijkstra(int source, int vertices) {
        vector<int> distances(vertices, INT_MAX); // Initialize distances to all vertices as infinity
        distances[source] = 0;

        // Min-heap priority queue: {distance, vertex}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int currentVertex = pq.top().second;
            pq.pop();

            // If the distance in the queue is greater than the known distance, skip
            if (currentDistance > distances[currentVertex]) {
                continue;
            }

            // Explore neighbors
            for (auto neighbor : adjList[currentVertex]) {
                int neighborVertex = neighbor.first;
                int weight = neighbor.second;

                // Relaxation step
                if (distances[currentVertex] + weight < distances[neighborVertex]) {
                    distances[neighborVertex] = distances[currentVertex] + weight;
                    pq.push({distances[neighborVertex], neighborVertex});
                }
            }
        }

        return distances;
    }
};

int main() {
    Graph graph;
    int vertices, edges, source;

    // Input the number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> vertices;

    cout << "Enter the number of edges: ";
    cin >> edges;

    // Input the edges
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < edges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph.addEdge(u, v, weight);
    }

    // Input the source vertex
    cout << "Enter the source vertex: ";
    cin >> source;

    // Find shortest paths
    vector<int> shortestDistances = graph.dijkstra(source, vertices);

    // Output the distances
    cout << "Shortest distances from vertex " << source << ":\n";
    for (int i = 0; i < vertices; i++) {
        if (shortestDistances[i] == INT_MAX) {
            cout << "Vertex " << i << ": INF\n";
        } else {
            cout << "Vertex " << i << ": " << shortestDistances[i] << "\n";
        }
    }

    return 0;
}
