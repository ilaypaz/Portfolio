#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;

class Edge
{
public:
    // assume u and v are two vertices
    // vertices are zero-indexed
    int u;
    int v;

    Edge() : u(-1), v(-1) {} // invalid vertex index
    Edge(int _u, int _v) : u(_u), v(_v) {}
};

class Graph
{
private:
    vector<int> vertices;
    vector<vector<int> > adjacencyList;
    vector<Edge> edgeList;

public:
    Graph() {}

    Graph(vector<vector<bool> > adjacencyMatrix)
    {
        // adjacencyMatrix has dimension n x n with zeroes along the main diagonal
        // assume row 0 is for vertex 0, row 1 is for vertex 1 and so on
        BuildVertices(adjacencyMatrix.size());
        BuildAdjacencyList(adjacencyMatrix);
        BuildEdgeList();
    }

    void BuildVertices(int numberOfVertices)
    {
        vertices.resize(numberOfVertices);
        for (int i = 0; i < numberOfVertices; i++)
        {
            vertices[i] = i;
        }
    }

    void BuildAdjacencyList(vector<vector<bool> > adjacencyMatrix)
    {
        int n = adjacencyMatrix.size();
        adjacencyList.resize(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adjacencyMatrix[i][j])
                {
                    adjacencyList[i].push_back(j);
                }
            }
        }
    }

    void BuildEdgeList()
    {
        edgeList.clear();
        for (int i = 0; i < adjacencyList.size(); i++)
        {
            for (int j : adjacencyList[i])
            {
                if (i < j)
                {
                    edgeList.push_back(Edge(i, j));
                }
            }
        }
    }

    void ShowVertices()
    {
        cout << "Vertices: ";
        for (int v : vertices)
        {
            cout << v << ", ";
        }
        cout << endl;
    }

    void ShowAdjacencyList()
    {
        cout << "Adjacency List:\n";
        for (int i = 0; i < adjacencyList.size(); i++)
        {
            cout << i << ": ";
            for (int neighbor : adjacencyList[i])
            {
                cout << neighbor << ", ";
            }
            cout << endl;
        }
    }

    void ShowEdgeList()
    {
        cout << "Edge List:\n";
        for (Edge e : edgeList)
        {
            cout << "(" << e.u << ", " << e.v << ")\n";
        }
    }

    int VertexCount()
    {
        return vertices.size();
    }

    int EdgeCount()
    {
        return edgeList.size();
    }

    void ShowNeighbors(int v)
    {
        // display neighbors of vertex v i.e. all friends of v
        if (!IsValidVertex(v))
        {
            cout << "Invalid vertex index!\n";
            return;
        }
        cout << "Neighbors of " << v << ": ";
        for (int neighbor : adjacencyList[v])
        {
            cout << neighbor << ", ";
        }
        cout << endl;
    }

    int Degree(int v)
    {
        // return the degree of vertex v i.e. number of friends of v
        if (!IsValidVertex(v))
        {
            cout << "Invalid vertex index!\n";
            return -1;
        }
        return adjacencyList[v].size();
    }

    void ShowDegrees()
    {
        // display degrees of all vertices sorted in descending order of degree
        cout << "Degrees of vertices:\n";
        vector<pair<int, int> > degrees;
        for (int i = 0; i < vertices.size(); i++)
        {
        degrees.push_back(std::make_pair(Degree(i), i)); 
        }
        sort(degrees.rbegin(), degrees.rend());
        for (auto &deg : degrees)
        {
            cout << deg.first << ", ";
        }
        cout << endl;
    }

    bool HasEdge(int v1, int v2)
    {
        // returns true if there is an edge between vertices v1 n v2; false otherwise
        if (!IsValidVertex(v1) || !IsValidVertex(v2))
        {
            return false;
        }
        return find(adjacencyList[v1].begin(), adjacencyList[v1].end(), v2) != adjacencyList[v1].end();
    }

    void DFS(int v1, int v2, vector<bool> &visited, vector<int> &path)
    {
        // depth first search to find a path from v1 to v2
        visited[v1] = true;
        path.push_back(v1);
        if (v1 == v2)
            return;

        for (int neighbor : adjacencyList[v1])
        {
            if (!visited[neighbor])
            {
                DFS(neighbor, v2, visited, path);
                if (!path.empty() && path.back() == v2)
                    return;
                path.pop_back();
            }
        }
    }

    vector<int> Path(int v1, int v2)
    {
        // returns the path (all vertices that fall along the path) from vertex v1 to vertex v2
        // if there is no path, return an empty vector
        if (v1 < 0 || v1 >= adjacencyList.size() || v2 < 0 || v2 >= adjacencyList.size() || v1 == v2)
        {
            cout << "Invalid vertex index!\n";
            return vector<int>();
        }

        vector<bool> visited(vertices.size(), false);
        vector<int> path;
        DFS(v1, v2, visited, path);
        if (!visited[v2])
        {
            path.clear();
        }
        return path;
    }

    void ShowPath(int v1, int v2, vector<int> path)
    {
        if (v1 < 0 || v1 >= adjacencyList.size() || v2 < 0 || v2 >= adjacencyList.size())
        {
            cout << "Invalid vertex index!\n";
            return;
        }

        if (path.size() == 0)
        {
            cout << "No path from " << v1 << " to " << v2 << endl;
            return;
        }

        cout << "Path from " << v1 << " to " << v2 << ": ";
        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i] << ", ";
        }
        cout << endl;
    }

    bool HasCycle()
    {
        // return true if graph has a cycle (starting from a node we follow edges to return back to the same vertex); false otherwise
        vector<bool> visited(vertices.size(), false);
        vector<bool> inStack(vertices.size(), false);

        for (int i = 0; i < vertices.size(); i++)
        {
            if (!visited[i] && HasCycleUtil(i, visited, inStack))
            {
                return true;
            }
        }
        return false;
    }

    bool HasCycleUtil(int v, vector<bool> &visited, vector<bool> &inStack)
    {
        visited[v] = true;
        inStack[v] = true;

        for (int neighbor : adjacencyList[v])
        {
            if (!visited[neighbor] && HasCycleUtil(neighbor, visited, inStack))
            {
                return true;
            }
            else if (inStack[neighbor])
            {
                return true;
            }
        }

        inStack[v] = false;
        return false;
    }

    bool IsValidVertex(int v)
    {
        // returns true if vertex index v is valid; false otherwise
        return v >= 0 && v < adjacencyList.size();
    }

        void DFS2(int startVertex, vector<bool> &visited, vector<int> &visitedNodes)
    {
        visited[startVertex] = true;

        // Explore all adjacent vertices
        for (int neighbor : adjacencyList[startVertex])
        {
            if (!visited[neighbor])
            {
                DFS2(neighbor, visited, visitedNodes);
            }
        }

        // Insert the vertex into visitedNodes after processing all its neighbors
        visitedNodes.push_back(startVertex);
    }
    
        vector<int> TopSort()
    {
        int N = VertexCount();
        vector<bool> visited(N, false);
        vector<int> ordering(N, 0);
        int k = N - 1;

        // Perform DFS for each unvisited node
        for (int i = 0; i < N; i++)
        {
            if (!visited[i])
            {
                vector<int> visitedNodes;
                DFS2(i, visited, visitedNodes);

                // Fill the ordering array in reverse order
                for (int j = visitedNodes.size() - 1; j >= 0; j--)
                {
                    ordering[k--] = visitedNodes[j];
                }
            }
        }

        return ordering;
    }
    

};

#endif
