#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int src, dest, weight;
};

class Graph {
public:
    int V, E;  // Number of vertices and edges
    vector<Edge> edges;

    Graph(int V, int E) {
        this->V = V;
        this->E = E;
        edges.resize(E);
    }

    void addEdge(int u, int v, int w, int i) {
        edges[i].src = u;
        edges[i].dest = v;
        edges[i].weight = w;
    }

    void bellmanFord(int src) {
        // Step 1: Initialize distances from src to all other vertices as INFINITE
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        // Step 2: Relax all edges |V| - 1 times.
        for (int i = 1; i <= V - 1; i++) {
            for (int j = 0; j < E; j++) {
                int u = edges[j].src;
                int v = edges[j].dest;
                int weight = edges[j].weight;

                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }

        // Step 3: Check for negative-weight cycles.
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                cout << "Graph contains negative-weight cycle" << endl;
                return;
            }
        }

        // Step 4: Print the calculated shortest distances
        printSolution(dist);
    }

    void printSolution(vector<int>& dist) {
        cout << "Vertex Distance from Source" << endl;
        for (int i = 0; i < V; i++) {
            if (dist[i] == INT_MAX) {
                cout << i << " \t\t " << "INF" << endl;
            } else {
                cout << i << " \t\t " << dist[i] << endl;
            }
        }
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    Graph graph(V, E);

    cout << "Enter the edges with source, destination, and weight:" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w, i);
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    graph.bellmanFord(source);

    return 0;
}
