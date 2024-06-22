#include <bits/stdc++.h>

using namespace std;

class Graph
{
public:
    int V, E;
    vector<vector<pair<int, int>>> adjList;

    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
        adjList.resize(V);
    }

    void EdgeUV(int u, int v, int edW)
    {
        adjList[u].push_back({v, edW});
        adjList[v].push_back({u, edW});
    }

    void broadcast(int u)
    {
        // iterate over the adjacency list of node u and notify everyone
        for (auto pair : adjList[u])
        {
            cout << "Node " << u << " is notifying Node " << pair.first << endl;
        }
    }

    void dfs(int u, int parent, vector<int> &visited, vector<int> &stack, vector<vector<int>> &cycles)
    {
        visited[u] = 1;
        stack.push_back(u);

        for (auto pair : adjList[u])
        {
            int v = pair.first;
            if (!visited[v])
            {
                dfs(v, u, visited, stack, cycles);
            }
            else if (v != parent && find(stack.begin(), stack.end(), v) != stack.end())
            {
                vector<int> cycle;
                auto it = find(stack.begin(), stack.end(), v);
                for (; it != stack.end(); ++it)
                {
                    cycle.push_back(*it);
                }
                cycle.push_back(v);
                cycles.push_back(cycle);
            }
        }

        stack.pop_back();
    }

    void detectAllCycles()
    {
        vector<int> visited(V, 0);
        vector<int> stack;
        vector<vector<int>> cycles;

        for (int i = 0; i < V; ++i)
        {
            if (!visited[i])
            {
                dfs(i, -1, visited, stack, cycles);
            }
        }

        if (cycles.empty())
        {
            cout << "No cycles detected." << endl;
        }
        else
        {
            cout << "Cycles detected: " << endl;
            for (const auto &cycle : cycles)
            {
                for (int node : cycle)
                {
                    cout << node << " ";
                }
                cout << endl;
            }
        }
    }
};

int main()
{
    int n, e;
    cin >> n >> e;
    // initialise the graph
    Graph graph(n, e);
    // take input of the edges
    for (int i = 0; i < e; i++)
    {
        int u, v, edW;
        cin >> u >> v >> edW;
        graph.EdgeUV(u, v, edW);
    }

    // print the graph
    cout << endl;
    cout << "Printing the adjacency list: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << " -> ";
        for (auto pair : graph.adjList[i])
        {
            cout << pair.first << "(" << pair.second << ") ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Broadcasting message from user 0" << endl;
    graph.broadcast(0);
    cout << endl;
    graph.detectAllCycles();

    return 0;
}

/*
Sample Input:
7 10
0 1 4
1 0 4
0 3 4
0 2 4
2 1 3
1 6 3
1 5 2
3 4 10
3 1 5
4 1 1

*/
