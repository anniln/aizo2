#include "DijkstryAlgorithmOnDirectedListGraph.h"

#include <sstream>
// Funkcja implementująca algorytm Dijkstry
std::string DijkstryAlgorithmOnDirectedListGraph::TestGraphAlgorithm(const ListGraph& graph, int startNode, int endNode,
                                                                     bool outputResults) const
{
    int nodeCount = graph.nodeCount;
    unsigned int* distances = new unsigned int[nodeCount];
    int* predecessors = new int[nodeCount];
    bool* sptSet = new bool[nodeCount];

    // Inicjalizacja
    for (int i = 0; i < nodeCount; i++)
    {
        distances[i] = UINT_MAX;
        sptSet[i] = false;
        predecessors[i] = -1;
    }

    distances[startNode] = 0;

    // Algorytm Dijkstry
    for (int count = 0; count < nodeCount - 1; count++)
    {
        int u = MinDistance(distances, sptSet, nodeCount);

        if (u == -1) break; // Przerywamy, jeśli nie znaleziono wierzchołka

        sptSet[u] = true;

        auto adjs = graph.nodes[u];
        for (auto adj : adjs)
        {
            int v = adj.adjacentTo;
            unsigned int weight = adj.value;

            if (!sptSet[v] && distances[u] != UINT_MAX && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                predecessors[v] = u;
            }
        }
    }

    // Wypisywanie wyników
    std::ostringstream oss;
    oss << "Total cost (shortest path) from node " << startNode << " to node " << endNode << " is: " <<
        distances[
            endNode] << "\n";

    oss << "Path: ";
    if (distances[endNode] == UINT_MAX)
    {
        oss << "No path\n";
    }
    else
    {
        int* path = new int[nodeCount];
        int path_index = 0;
        for (int at = endNode; at != -1; at = predecessors[at])
        {
            path[path_index++] = at;
        }
        std::reverse(path, path + path_index);
        for (int i = 0; i < path_index; ++i)
        {
            oss << path[i] << " ";
        }
        oss << "\n";
        delete[] path;
    }

    // Zwolnienie pamięci
    delete[] distances;
    delete[] predecessors;
    delete[] sptSet;

    if (outputResults) cout << oss.str();
    return oss.str();
}

// Funkcja pomocnicza do znalezienia minimalnej wartości w tablicy
int DijkstryAlgorithmOnDirectedListGraph::MinDistance(unsigned int dist[], bool sptSet[], int nodeCount) const
{
    unsigned int min = UINT_MAX;
    int min_index = -1;

    for (int v = 0; v < nodeCount; v++)
        if (!sptSet[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}
