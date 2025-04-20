#include "Graph.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Test Case 1: Simple Directed Acyclic Graph (DAG)
    cout << "Test Case 1: Simple DAG\n";
    vector<vector<bool> > adjacencyMatrix1 = {
        {0, 1, 0, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    Graph g1(adjacencyMatrix1);
    g1.ShowAdjacencyList();
    g1.ShowVertices();
    vector<int> path = g1.Path(0, 3);
    g1.ShowPath(0, 3, path);

    // Test Case 2: Empty Graph
    cout << "\nTest Case 2: Empty Graph\n";
    vector<vector<bool> > adjacencyMatrix2 = {};
    Graph g2(adjacencyMatrix2);
    g2.ShowAdjacencyList();
    g2.ShowVertices();

    // Test Case 3: Independent Chains (Should show no cycles and path from 0 to 2)
    cout << "\nTest Case 3: Independent Chains\n";
    vector<vector<bool> > adjacencyMatrix3 = {
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    Graph g3(adjacencyMatrix3);
    g3.ShowAdjacencyList();
    g3.ShowVertices();
    vector<int> path2 = g3.Path(0, 2);
    g3.ShowPath(0, 2, path2);
    cout << "Has Cycle: " << (g3.HasCycle() ? "Yes" : "No") << endl;

    // Test Case 4: Graph with a Cycle
    cout << "\nTest Case 4: Graph with a Cycle\n";
    vector<vector<bool> > adjacencyMatrix4 = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0} // Cycle
    };
    Graph g4(adjacencyMatrix4);
    g4.ShowAdjacencyList();
    g4.ShowVertices();
    cout << "Has Cycle: " << (g4.HasCycle() ? "Yes" : "No") << endl;

    // Test Case 5: General Graph with 5 vertices
    cout << "\nTest Case 5: General Graph with 5 vertices\n";
    vector<vector<bool> > adjacencyMatrix5 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    Graph g5(adjacencyMatrix5);
    g5.ShowAdjacencyList();
    g5.ShowVertices();
    vector<int> path3 = g5.Path(0, 4);
    g5.ShowPath(0, 4, path3);
    cout << "Has Cycle: " << (g5.HasCycle() ? "Yes" : "No") << endl;

    // Test Case 6: Topological Sorting for DAG
    cout << "\nTest Case 6: Topological Sorting for DAG\n";
    vector<vector<bool> > adjacencyMatrix6 = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };
    Graph g6(adjacencyMatrix6);
    g6.ShowAdjacencyList();
    g6.ShowVertices();
    vector<int> topSort = g6.TopSort();
    cout << "Topological Sort: ";
    for (int v : topSort) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}