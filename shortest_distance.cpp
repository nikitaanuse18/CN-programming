#include <iostream>
#include <iomanip>
using namespace std;

#define V 7
#define INF 999999

int main()
{
    char nodes[V] = {'A','B','C','D','E','F','G'};

    int graph[V][V] = {
        {0,4,2,0,0,0,0},
        {4,0,1,5,0,0,0},
        {2,1,0,8,10,0,0},
        {0,5,8,0,2,6,0},
        {0,0,10,2,0,3,5},
        {0,0,0,6,3,0,1},
        {0,0,0,0,5,1,0}
    };

    char start, end;

    cout << "Available Nodes: A B C D E F G\n";
    cout << "Enter starting node: ";
    cin >> start;
    cout << "Enter ending node: ";
    cin >> end;

    if (start >= 'a' && start <= 'g') start -= 32;
    if (end >= 'a' && end <= 'g') end -= 32;

    if (start < 'A' || start > 'G' ||
        end < 'A' || end > 'G')
    {
        cout << "Invalid node!\n";
        return 1;
    }

    int source = start - 'A';
    int destination = end - 'A';

    int dist[V], parent[V];
    bool visited[V] = {false};

    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[source] = 0;

    // Dijkstra's algorithm
    for (int count = 0; count < V; count++)
    {
        int u = -1, minimum = INF;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && dist[i] < minimum)
            {
                minimum = dist[i];
                u = i;
            }
        }

        if (u == -1) break;

        visited[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && graph[u][v] > 0 &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "\n========== SHORTEST PATH RESULT ==========\n";
    cout << "Starting Node: " << start << "\n";
    cout << "Ending Node: " << end << "\n";

    if (dist[destination] == INF)
    {
        cout << "No path exists between these nodes.\n";
        return 0;
    }

    int path[V], length = 0;

    for (int current = destination; current != -1;
         current = parent[current])
    {
        path[length++] = current;
    }

    cout << "Shortest Path: ";
    for (int i = length - 1; i >= 0; i--)
    {
        cout << nodes[path[i]];
        if (i > 0) cout << " -> ";
    }

    cout << "\n\n";
    cout << left << setw(12) << "From"
         << setw(12) << "To"
         << setw(15) << "Edge Weight"
         << "Cumulative Distance\n";

    cout << "-----------------------------------------------\n";

    int total = 0;

    for (int i = length - 1; i > 0; i--)
    {
        int u = path[i];
        int v = path[i - 1];

        total += graph[u][v];

        cout << left << setw(12) << nodes[u]
             << setw(12) << nodes[v]
             << setw(15) << graph[u][v]
             << total << "\n";
    }

    cout << "-----------------------------------------------\n";
    cout << "Total Shortest Distance: "
         << dist[destination] << "\n";

    return 0;
}

//OUTPUT
//Available Nodes: A B C D E F G
//Enter starting node: A
//Enter ending node: D

//========== SHORTEST PATH RESULT ==========
//Starting Node: A
//Ending Node: D
//Shortest Path: A -> C -> B -> D

//From        To          Edge Weight    Cumulative Distance
//-----------------------------------------------
//A           C           2              2
//C           B           1              3
//B           D           5              8
//-----------------------------------------------
//Total Shortest Distance: 8
