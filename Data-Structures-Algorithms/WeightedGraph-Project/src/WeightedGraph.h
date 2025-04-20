#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <set>
#include <map>
using namespace std;

class Edge
{
public:
    int u;      // Source vertex
    int v;      // Destination vertex
    int weight; // Weight of the edge

    // Default constructor
    Edge() : u(-1), v(-1), weight(0) {}

    // Constructor for edges with specified vertices and weight
    Edge(int _u, int _v, int _weight) : u(_u), v(_v), weight(_weight) {}
};

class WeightedGraph
{
private:
    vector<int> vertices;                         // List of vertices
    vector<vector<pair<int, int> > > adjacencyList; // Adjacency list (pair: neighbor, weight)
    vector<Edge> edgeList;                        // List of edges

public:
    WeightedGraph() {}

    // Constructor using an adjacency matrix
    WeightedGraph(const vector<vector<int> > &adjacencyMatrix)
    {
        BuildVertices(adjacencyMatrix.size());
        BuildAdjacencyList(adjacencyMatrix);
        BuildEdgeList();
    }

    // Build vertices from the given number of vertices
    void BuildVertices(int numberOfVertices)
    {
        vertices.resize(numberOfVertices);
        for (int i = 0; i < numberOfVertices; i++)
        {
            vertices[i] = i;
        }
    }

    // Build adjacency list from adjacency matrix
    void BuildAdjacencyList(const vector<vector<int> > &adjacencyMatrix)
    {
        int n = adjacencyMatrix.size();
        adjacencyList.resize(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adjacencyMatrix[i][j] != 0)
                {
                    adjacencyList[i].emplace_back(j, adjacencyMatrix[i][j]);
                }
            }
        }
    }

    // Build edge list from the adjacency list
    void BuildEdgeList()
    {
        edgeList.clear();
        for (int i = 0; i < adjacencyList.size(); i++)
        {
            for (const auto &neighbor : adjacencyList[i])
            {
                if (i < neighbor.first)
                {
                    edgeList.emplace_back(i, neighbor.first, neighbor.second);
                }
            }
        }
    }

    // Display vertices
    void ShowVertices()
    {
        cout << "Vertices: ";
        for (int v : vertices)
        {
            cout << v << " ";
        }
        cout << endl;
    }

    // Display adjacency list
    void ShowAdjacencyList()
    {
        cout << "Adjacency List:\n";
        for (int i = 0; i < adjacencyList.size(); i++)
        {
            cout << i << ": ";
            for (const auto &neighbor : adjacencyList[i])
            {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    // Display edge list
    void ShowEdgeList()
    {
        cout << "Edge List:\n";
        for (const Edge &e : edgeList)
        {
            cout << "(" << e.u << ", " << e.v << ", weight: " << e.weight << ")\n";
        }
    }

    // Count vertices
    int VertexCount()
    {
        return vertices.size();
    }

    // Count edges
    int EdgeCount()
    {
        return edgeList.size();
    }

    // Check if an edge exists
    bool HasEdge(int v1, int v2)
    {
        if (!IsValidVertex(v1) || !IsValidVertex(v2))
        {
            return false;
        }
        for (const auto &neighbor : adjacencyList[v1])
        {
            if (neighbor.first == v2)
            {
                return true;
            }
        }
        return false;
    }

    // Depth First Search to find a path from v1 to v2
    void DFS(int v1, int v2, vector<bool> &visited, vector<int> &path)
    {
        visited[v1] = true;
        path.push_back(v1);
        if (v1 == v2)
        {
            return;
        }
        for (const auto &neighbor : adjacencyList[v1])
        {
            if (!visited[neighbor.first])
            {
                DFS(neighbor.first, v2, visited, path);
                if (!path.empty() && path.back() == v2)
                {
                    return;
                }
                path.pop_back();
            }
        }
    }

    // Get path from v1 to v2
    vector<int> Path(int v1, int v2)
    {
        if (!IsValidVertex(v1) || !IsValidVertex(v2))
        {
            cout << "Invalid vertex index!\n";
            return vector<int>();
        }
        vector<bool> visited(vertices.size(), false);
        vector<int> path;
        DFS(v1, v2, visited, path);
        return (visited[v2]) ? path : vector<int>(0);
    }

    // Display path
    void ShowPath(int v1, int v2, const vector<int> &path)
    {
        if (path.empty())
        {
            cout << "No path from " << v1 << " to " << v2 << endl;
            return;
        }
        cout << "Path from " << v1 << " to " << v2 << ": ";
        for (int v : path)
        {
            cout << v << " ";
        }
        cout << endl;
    }

    // Check if vertex is valid
    bool IsValidVertex(int v)
    {
        return v >= 0 && v < adjacencyList.size();
    }

    pair<set<int>, map<int, int> > PrimMinimumSpanningTree(WeightedGraph &graph, int start_vertex)
    {
        set<int> MST; // Set to keep track of the vertices included in the MST
        auto comp = [](Edge left, Edge right)
        {
            if (left.weight == right.weight)
            {
                return left.u > right.u; // Break ties by choosing the edge with the smaller starting vertex
            }
            return left.weight > right.weight; // Comparing weights
        };

        priority_queue<Edge, vector<Edge>, decltype(comp)> edges(comp);
        map<int, int> cost;   // Map to track the minimum cost to reach each vertex
        map<int, int> parent; // Map to track the parent of each vertex in the MST

        // Initialize cost and parent for each vertex
        for (int i = 0; i < VertexCount(); i++)
        {
            cost[i] = INT_MAX; // Cost set to infinity initially
            parent[i] = -1;    // Parent initialized to -1 (no parent)
        }

        // Start with the initial vertex
        cost[start_vertex] = 0;

        // Add all edges connected to the start vertex to the priority queue
        for (const auto &neighbor : graph.adjacencyList[start_vertex])
        {
            int next_vertex = neighbor.first;
            int weight = neighbor.second;
            edges.push(Edge(start_vertex, next_vertex, weight));
        }

        while (!edges.empty())
        {
            Edge current_edge = edges.top();
            edges.pop();

            int u = current_edge.u;
            int v = current_edge.v;
            int weight = current_edge.weight;

            if (MST.find(u) == MST.end() || MST.find(v) == MST.end())
            {
                int new_vertex = (MST.find(u) == MST.end()) ? u : v;
                int adjacent_vertex = (MST.find(u) == MST.end()) ? v : u;
                // Add the new vertex to the MST
                MST.insert(new_vertex);

                for (const auto &neighbor : graph.adjacencyList[new_vertex])
                {
                    int next_vertex = neighbor.first;
                    int next_weight = neighbor.second;

                    // Only add edge if the vertex is not in the MST and the new weight is minimal
                    if (MST.find(next_vertex) == MST.end() && cost[next_vertex] > next_weight)
                    {
                        cost[next_vertex] = next_weight;
                        parent[next_vertex] = new_vertex;
                        edges.push(Edge(new_vertex, next_vertex, next_weight));
                    }
                }
            }
        }
        return make_pair(MST, parent); // Return the set of vertices included in the MST and the parent mapping
    }

    vector<int> Dijkstra(WeightedGraph &graph, int source)
    {
        int numVertices = graph.VertexCount();
        vector<int> dist(numVertices, INT_MAX); // Distance from source to each vertex
        vector<int> prev(numVertices, -1);      // Previous node in the optimal path

        // Custom comparator for min-heap
        auto comp = [](pair<int, int> left, pair<int, int> right)
        {
            return left.first > right.first; // Compare by distance, smaller comes first
        };

        // Min-heap priority queue (distance, vertex)
        priority_queue<pair<int, int>, vector<pair<int, int> >, decltype(comp)> pq(comp);

        // Initialize source
        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty())
        {
            // Get the vertex with the smallest distance
            int u = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();

            // If the distance in the queue is outdated, skip this vertex
            if (currentDist > dist[u])
            {
                continue;
            }

            // Traverse neighbors of u
            for (const auto &neighbor : graph.adjacencyList[u])
            {
                int v = neighbor.first;
                int weight = neighbor.second;

                // Relaxation step
                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push({dist[v], v}); // Add the updated distance to the queue
                }
            }
        }

        return dist; // Returns the shortest distances
    }

    vector<int> BellmanFord(WeightedGraph &graph, int source)
    {
        int V = graph.VertexCount(); // Number of vertices
        int E = graph.EdgeCount();   // Number of edges

        // Step 1: Initialize distances
        vector<int> distance(V, INT_MAX); // array of size equal to number of vertices in Graph, initially filled with INFINITY
        distance[source] = 0;

        // Step 2: Relax all edges |V| - 1 times,  trying to update the shortest known distance to a vertex by considering whether an edge can provide a shorter path to that vertex.
        for (int i = 1; i < V; ++i)
        {
            for (const Edge &edge : graph.edgeList)
            {
                int u = edge.u;
                int v = edge.v;
                int weight = edge.weight;

if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
{
    distance[v] = distance[u] + weight;
}
            }
        }

        // Step 3: Check for negative-weight cycles
        for (const Edge &edge : graph.edgeList)
        {
            int u = edge.u;
            int v = edge.v;
            int weight = edge.weight;

            if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
            {
                cout << "Graph contains a negative-weight cycle\n";
                return vector<int>(); // Return an empty vector to indicate failure
            }
        }

        return distance; // Return the computed distances
    }
    vector<vector<int> > FloydWarshall(WeightedGraph &graph)
{
    int n =graph.VertexCount(); // Number of vertices
    vector<vector<int> > dist(n, vector<int>(n, 0)); // Distance matrix initialized to infinity

    // Initialize the distance matrix with the edge weights from the adjacency list
    for (int i = 0; i < n; i++)
    {
        dist[i][i] = 0; // The distance from a vertex to itself is always 0
        for (const auto &neighbor : graph.adjacencyList[i])
        {
            int v = neighbor.first;
            int weight = neighbor.second;
            dist[i][v] = weight; // Set the direct edge weight between i and v
        }
    }

    // Floyd-Warshall Algorithm
    for (int k = 0; k < n; k++) // Intermediate vertex
    {
        for (int i = 0; i < n; i++) // Start vertex
        {
            for (int j = 0; j < n; j++) // End vertex
            {
                if (dist[i][k] != 0 && dist[k][j] != 0) { 

              dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]); // Update the shortest path
                
            }
        }
    }

    return dist; // Return the distance matrix with the shortest paths
}
}
};

#endif // WEIGHTEDGRAPH_H