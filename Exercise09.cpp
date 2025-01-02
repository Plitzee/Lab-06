#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <cmath>
using namespace std;

class Graph {
private:
    unordered_map<int, vector<int>> adjList; // Adjacency list for outgoing links
    unordered_map<int, vector<int>> incomingLinks; // Adjacency list for incoming links
    int numVertices;

public:
    Graph(int vertices) : numVertices(vertices) {}

    // Add a directed edge to the graph
    void addEdge(int u, int v) {
        adjList[u].push_back(v);          // Outgoing link from u to v
        incomingLinks[v].push_back(u);    // Incoming link to v from u
    }

    // PageRank algorithm
    vector<double> computePageRank(double dampingFactor = 0.85, int iterations = 100, double tolerance = 1e-6) {
        vector<double> rank(numVertices, 1.0 / numVertices); // Initialize ranks
        vector<double> newRank(numVertices, 0.0);            // For storing updated ranks

        for (int iter = 0; iter < iterations; iter++) {
            // Distribute rank contributions
            for (int i = 0; i < numVertices; i++) {
                newRank[i] = (1.0 - dampingFactor) / numVertices; // Base rank (teleport factor)
            }

            for (int u = 0; u < numVertices; u++) {
                if (adjList[u].empty()) {
                    // Distribute rank equally if no outgoing links
                    for (int i = 0; i < numVertices; i++) {
                        newRank[i] += dampingFactor * (rank[u] / numVertices);
                    }
                } else {
                    // Distribute rank to outgoing links
                    double contribution = dampingFactor * (rank[u] / adjList[u].size());
                    for (int v : adjList[u]) {
                        newRank[v] += contribution;
                    }
                }
            }

            // Check for convergence
            double diff = 0.0;
            for (int i = 0; i < numVertices; i++) {
                diff += abs(newRank[i] - rank[i]);
            }

            rank = newRank; // Update rank
            if (diff < tolerance) {
                break; // Stop if converged
            }
        }

        return rank;
    }

    // Print the PageRank values
    void printPageRank(const vector<double> &rank) {
        cout << "PageRank Values:\n";
        for (int i = 0; i < rank.size(); i++) {
            cout << "Page " << i << ": " << fixed << setprecision(6) << rank[i] << endl;
        }
    }
};

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of web pages (vertices): ";
    cin >> numVertices;

    cout << "Enter the number of hyperlinks (edges): ";
    cin >> numEdges;

    Graph graph(numVertices);

    cout << "Enter the hyperlinks (u -> v):\n";
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    // Compute PageRank
    vector<double> pageRank = graph.computePageRank();

    // Print the PageRank values
    graph.printPageRank(pageRank);

    return 0;
}
