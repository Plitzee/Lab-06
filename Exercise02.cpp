#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
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

    // Recursive DFS helper function
    void dfsRecursiveHelper(int vertex, unordered_map<int, bool> &visited) {
        // Mark the current vertex as visited
        visited[vertex] = true;
        cout << vertex << " ";

        // Recursively visit all unvisited neighbors
        for (int neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                dfsRecursiveHelper(neighbor, visited);
            }
        }
    }

    // Recursive DFS function
    void dfsRecursive(int startVertex) {
        unordered_map<int, bool> visited;

        cout << "DFS (Recursive): ";
        dfsRecursiveHelper(startVertex, visited);
        cout << endl;
    }

    // Iterative DFS function
    void dfsIterative(int startVertex) {
        unordered_map<int, bool> visited;
        stack<int> s;

        s.push(startVertex);

        cout << "DFS (Iterative): ";
        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();

            // If the vertex has not been visited
            if (!visited[currentVertex]) {
                cout << currentVertex << " ";
                visited[currentVertex] = true;

                // Push all unvisited neighbors to the stack
                for (auto it = adjList[currentVertex].rbegin(); it != adjList[currentVertex].rend(); ++it) {
                    if (!visited[*it]) {
                        s.push(*it);
                    }
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Graph graph;

    // Add edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    graph.addEdge(2, 6);

    // Perform DFS
    graph.dfsRecursive(0);
    graph.dfsIterative(0);

    return 0;
}