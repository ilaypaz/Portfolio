#include "WeightedGraph.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <climits> // For INT_MAX
using namespace std;

int main() {
    // Create an adjacency matrix to represent the graph
    vector<vector<int> > adjacencyMatrix = {
        {0, 1, 3, 0, 0},
        {1, 0, 1,-6,0},
        {3, 1, 0,-4,2}, 
        {0, -6,-4,0,5}, 
        {0, 0, 2, 5,0}
    };

    // Instantiate the WeightedGraph object using the adjacency matrix
    WeightedGraph graph(adjacencyMatrix);

    // Test Prim's Minimum Spanning Tree
    int startVertex = 0;
    pair<set<int>, map<int, int> > result = graph.PrimMinimumSpanningTree(graph,startVertex);

    // Display the MST vertices
    cout << "Minimum Spanning Tree includes the following vertices:\n";
    for (int vertex : result.first) {
        cout << vertex << " ";
    }
    cout << endl;

    // Display the parent map (edges in the MST)
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto& entry : result.second) {
        int vertex = entry.first;
        int parent = entry.second;
        if (parent != -1) { // Don't display the placeholder value for the root vertex
            cout << "(" << parent << " - " << vertex << ")\n";
        }
    }

    // // Test Dijkstra's algorithm
    // cout << "\nTesting Dijkstra's Algorithm:\n";
    // vector<int> distances = graph.Dijkstra(graph, startVertex);

    // // Display shortest distances
    // cout << "Shortest distances from vertex " << startVertex << ":\n";
    // for (size_t i = 0; i < distances.size(); ++i) {
    //     if (distances[i] == INT_MAX) {
    //         cout << "Vertex " << i << ": Unreachable\n";
    //     } else {
    //         cout << "Vertex " << i << ": " << distances[i] << "\n";
    //     }
    // }

cout << "\nTesting Bellman-Ford Algorithm:\n";
    vector<int> bf_distances = graph.BellmanFord(graph,startVertex);

    if (!bf_distances.empty()) {
        // Display shortest distances from the source using Bellman-Ford
        cout << "Shortest distances from vertex " << startVertex << ":\n";
        for (size_t i = 0; i < bf_distances.size(); ++i) {
            if (bf_distances[i] == INT_MAX) {
                cout << "Vertex " << i << ": Unreachable\n";
            } else {
                cout << "Vertex " << i << ": " << bf_distances[i] << "\n";
            }
        }
    }

    cout << "\nTesting Floyd-Warshall Algorithm:\n";
    vector<vector<int> > fw_distances = graph.FloydWarshall( graph);

    cout << "Shortest distances between all pairs of vertices:\n";
    for (size_t i = 0; i < fw_distances.size(); ++i) {
        for (size_t j = 0; j < fw_distances[i].size(); ++j) {
            if (fw_distances[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << fw_distances[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
