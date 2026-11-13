
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

// Dijkstra's algorithm
void dijkstra(vector<vector<int>> cost, int n, int start)
{
    vector<int> d(n, INF);
    vector<int> parent(n, -1);
    vector<bool> done(n, false);

    d[start] = 0;

    for(int i = 0; i < n; i++)
    {
        int u = -1, least = INF;

        // Find unvisited node with minimum distance
        for(int v = 0; v < n; v++)
        {
            if(!done[v] && d[v] < least)
            {
                u = v;
                least = d[v];
            }
        }

        if(u == -1)
            break;

        done[u] = true;

        // Update distances of neighbouring nodes
        for(int v = 0; v < n; v++)
        {
            int w = cost[u][v];

            if(w != 0 && !done[v] && d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                parent[v] = u;
            }
        }
    }

    // Print distances and paths
    cout << "\nNode\tDistance\tPath\n";

    for(int v = 0; v < n; v++)
    {
        cout << v << "\t";

        if(d[v] == INF)
        {
            cout << "INF\t\tNo path\n";
        }
        else
        {
            cout << d[v] << "\t\t";

            vector<int> p;
            int x = v;

            while(x != -1)
            {
                p.push_back(x);
                x = parent[x];
            }

            reverse(p.begin(), p.end());

            for(int j = 0; j < p.size(); j++)
            {
                cout << p[j];

                if(j != p.size() - 1)
                    cout << " -> ";
            }

            cout << endl;
        }
    }
}

int main()
{
    int n, start;

    cout << "Enter number of nodes: ";
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));

    cout << "Enter cost adjacency matrix (0 = no edge):\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> cost[i][j];
        }
    }

    cout << "Enter source node: ";
    cin >> start;

    dijkstra(cost, n, start);

    return 0;
}
   