#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <numeric>
#include <limits>
#include <set>
using namespace std;

// Class representing the graph
class Graph {
private:
    unordered_map<int, vector<pair<int, double>>> adjList; // Adjacency list {node -> {neighbor, weight}}
    int numVertices;

public:
    Graph(int vertices) : numVertices(vertices) {}

    // Add an edge to the graph
    void addEdge(int u, int v, double weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Undirected graph
    }

    // Function to calculate modularity
    double calculateModularity(const map<int, int>& community, double totalWeight) {
        double modularity = 0.0;
        unordered_map<int, double> inDegree, totalDegree;

        // Calculate in-degree and total-degree for each community
        for (const auto& pair : adjList) {
            int node = pair.first;
            int comm = community.at(node);
            for (const auto& neighbor : pair.second) {
                if (community.at(neighbor.first) == comm) {
                    inDegree[comm] += neighbor.second; // Internal edge weight
                }
                totalDegree[comm] += neighbor.second; // Total degree (all edges)
            }
        }

        // Calculate modularity based on in-degree and total-degree
        for (const auto& pair : inDegree) {
            int comm = pair.first;
            double in = pair.second / 2.0; // Internal edges are counted twice
            double total = totalDegree[comm] / (2.0 * totalWeight);
            modularity += (in / totalWeight) - (total * total);
        }

        return modularity;
    }

    // Louvain method for community detection
    map<int, int> louvainMethod() {
        map<int, int> community; // Node -> Community
        for (int i = 0; i < numVertices; i++) {
            community[i] = i; // Initially, each node is its own community
        }

        double totalWeight = 0.0;
        for (const auto& pair : adjList) {
            for (const auto& neighbor : pair.second) {
                totalWeight += neighbor.second;
            }
        }
        totalWeight /= 2.0; // Since the graph is undirected

        bool improvement = true;
        while (improvement) {
            improvement = false;
            for (int node = 0; node < numVertices; node++) {
                int bestCommunity = community[node];
                double maxGain = 0.0;

                // Remove the node from its current community
                community[node] = -1;

                // Explore neighboring communities
                unordered_map<int, double> communityWeights;
                for (const auto& neighbor : adjList[node]) {
                    int neighborComm = community[neighbor.first];
                    if (neighborComm != -1) {
                        communityWeights[neighborComm] += neighbor.second;
                    }
                }

                // Find the best community for the node
                for (const auto& pair : communityWeights) {
                    int targetComm = pair.first;
                    double gain = pair.second - (adjList[node].size() * pair.second / totalWeight);
                    if (gain > maxGain) {
                        maxGain = gain;
                        bestCommunity = targetComm;
                    }
                }

                // Move the node to the best community
                if (bestCommunity != -1 && bestCommunity != community[node]) {
                    improvement = true;
                    community[node] = bestCommunity;
                } else {
                    community[node] = node; // Restore the original community
                }
            }
        }

        return community;
    }

    // Print communities
    void printCommunities(const map<int, int>& community) {
        map<int, vector<int>> clusters;
        for (const auto& pair : community) {
            clusters[pair.second].push_back(pair.first);
        }

        cout << "Detected Communities:\n";
        for (const auto& pair : clusters) {
            cout << "Community " << pair.first << ": ";
            for (int node : pair.second) {
                cout << node << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    Graph graph(numVertices);

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        double weight;
        cin >> u >> v >> weight;
        graph.addEdge(u, v, weight);
    }

    // Detect communities using Louvain method
    map<int, int> community = graph.louvainMethod();

    // Print detected communities
    graph.printCommunities(community);

    return 0;
}
