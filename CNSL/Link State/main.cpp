#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

class Graph {
public:
    int V;
    vector<vector<int>> adj;

    Graph(int vertices) {
        V = vertices;
        adj.resize(V, vector<int>(V, INF));
    }

    void addEdge(int u, int v, int weight) {
        adj[u][v] = weight;
        adj[v][u] = weight;
    }

    void dijkstra(int src) {
        vector<int> distance(V, INF);
        vector<bool> visited(V, false);

        distance[src] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = minDistance(distance, visited);
            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (!visited[v] && adj[u][v] != INF && distance[u] != INF &&
                    (distance[u] + adj[u][v] < distance[v])) {
                    distance[v] = distance[u] + adj[u][v];
                }
            }
        }

        printShortestPaths(distance, src);
    }

    int minDistance(const vector<int>& distance, const vector<bool>& visited) {
        int min = INF, min_index = 0;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && distance[v] <= min) {
                min = distance[v];
                min_index = v;
            }
        }
        return min_index;
    }

    void printShortestPaths(const vector<int>& distance, int src) {
        cout << "Shortest Paths from Source " << src << " to Other Router:\n";
        for (int i = 0; i < V; i++) {
            if (i != src) {
                cout << "Router " << src << " to Router " << i << ": Distance = ";
                if (distance[i] == INF)
                    cout << "No path" << endl;
                else
                    cout << distance[i] << endl;
            }
        }
    }
};

int main() {
    int V;
    cout<<"Enter Number of router"<<endl;
    cin>>V;
    Graph network(V);
    int source;

    while (true) {
        cout << "Menu:\n";
        cout << "1. Add Edge\n";
        cout << "2. Find Shortest Path\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
       
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                int u, v, weight;
                cout << "Enter source router : ";
                cin >> u;
                cout << "Enter destination router: ";
                cin >> v;
                cout << "Enter link weight: ";
                cin >> weight;
                network.addEdge(u, v, weight);
                cout << "Edge added between router " << u << " and " << v << " with weight " << weight << ".\n";
                break;
            case 2:
                cout << "Enter the source router for the shortest path: ";
                cin >> source;
                network.dijkstra(source);
                break;
            case 3:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}