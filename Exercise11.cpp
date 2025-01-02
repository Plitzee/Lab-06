#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;

// Struct to represent a point with x, y coordinates
struct Point {
    int x, y;
};

// Function to calculate Euclidean distance as the heuristic
double calculateHeuristic(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

class Graph {
private:
    unordered_map<int, vector<pair<int, double>>> adjList; // Adjacency list {node -> {neighbor, weight}}
    unordered_map<int, Point> points; // Mapping of node to its coordinates

public:
    // Add a node with coordinates
    void addPoint(int node, int x, int y) {
        points[node] = {x, y};
    }

    // Add an edge to the graph
    void addEdge(int u, int v, double weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // For undirected graph
    }

    // A* Algorithm
    vector<int> aStar(int start, int goal) {
        unordered_map<int, double> gScore; // Cost from start to each node
        unordered_map<int, double> fScore; // Estimated cost from start to goal through each node
        unordered_map<int, int> cameFrom; // To reconstruct the path
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq; // Min-heap priority queue

        for (auto &point : points) {
            gScore[point.first] = INT_MAX;
            fScore[point.first] = INT_MAX;
        }
        gScore[start] = 0;
        fScore[start] = calculateHeuristic(points[start], points[goal]);

        pq.push({fScore[start], start});

        while (!pq.empty()) {
            int current = pq.top().second;
            pq.pop();

            if (current == goal) {
                // Reconstruct the path
                vector<int> path;
                while (current != start) {
                    path.push_back(current);
                    current = cameFrom[current];
                }
                path.push_back(start);
                reverse(path.begin(), path.end());
                return path;
            }

            for (auto &neighbor : adjList[current]) {
                int neighborNode = neighbor.first;
                double weight = neighbor.second;

                double tentativeGScore = gScore[current] + weight;
                if (tentativeGScore < gScore[neighborNode]) {
                    cameFrom[neighborNode] = current;
                    gScore[neighborNode] = tentativeGScore;
                    fScore[neighborNode] = gScore[neighborNode] + calculateHeuristic(points[neighborNode], points[goal]);
                    pq.push({fScore[neighborNode], neighborNode});
                }
            }
        }

        return {}; // Return an empty path if no route is found
    }
};

int main() {
    Graph graph;
    int numPoints, numEdges;

    cout << "Enter the number of delivery points: ";
    cin >> numPoints;
    cout << "Enter the coordinates of each point (id x y):\n";
    for (int i = 0; i < numPoints; i++) {
        int id, x, y;
        cin >> id >> x >> y;
        graph.addPoint(id, x, y);
    }

    cout << "Enter the number of roads (edges): ";
    cin >> numEdges;
    cout << "Enter the roads (u v distance):\n";
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        double distance;
        cin >> u >> v >> distance;
        graph.addEdge(u, v, distance);
    }

    int start, goal;
    cout << "Enter the start and goal points: ";
    cin >> start >> goal;

    // Find the shortest path using A* algorithm
    vector<int> path = graph.aStar(start, goal);

    // Print the path
    if (!path.empty()) {
        cout << "Optimal route from " << start << " to " << goal << ":\n";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No route found from " << start << " to " << goal << endl;
    }

    return 0;
}
