#include "BellmanFordAlgorithmOnDirectedListGraphTester.h"

BellmanFordAlgorithmOnDirectedListGraphTester::~BellmanFordAlgorithmOnDirectedListGraphTester()
{
}

std::string BellmanFordAlgorithmOnDirectedListGraphTester::TestGraphAlgorithm(const ListGraph& graph, int startNode,
                                                                       int endNode) const
{
    int nodeCount = graph.nodeCount;
    int* distance = new int[nodeCount];
    int* predecessor = new int[nodeCount];

    // Inicjalizacja odległości
    for (int i = 0; i < nodeCount; ++i)
    {
        distance[i] = UINT_MAX;
        predecessor[i] = -1;
    }
    distance[startNode] = 0;

    // Relaksacja krawędzi
    for (int i = 1; i <= nodeCount - 1; ++i)
    {
        for (int u = 0; u < nodeCount; ++u)
        {
            auto adjs = graph.nodes[u];
            for (auto adj : adjs)
            {
                int v = adj.adjacentTo;
                unsigned int weight = adj.value;
                if (distance[u] != UINT_MAX &&
                    distance[u] + weight < distance[v])
                {
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;
                }
            }
        }
    }

    // Sprawdzenie cyklu ujemnego
    std::ostringstream oss;
    for (int u = 0; u < nodeCount; ++u)
    {
        auto adjs = graph.nodes[u];
        for (auto adj : adjs)
        {
            int v = adj.adjacentTo;
            unsigned int weight = adj.value;
            if (distance[u] != UINT_MAX &&
                distance[u] + weight < distance[v])
            {
                oss << "Cykl ujemny wykryty" << "\n";
                delete[] distance;
                delete[] predecessor;
                return oss.str();
            }
        }
    }

    // Wyświetlanie najkrótszej ścieżki
    oss << "Total cost (shortest path) from node " << startNode << " to node " << endNode << " is: " << distance[
        endNode] << "\n";

    // Konstruowanie ścieżki
    oss << "Path: ";
    int current = endNode;
    int* path = new int[nodeCount]; // dynamiczna tablica do przechowywania ścieżki
    int pathLength = 0;

    while (current != -1)
    {
        path[pathLength++] = current;
        current = predecessor[current];
    }

    // Drukowanie ścieżki w odpowiedniej kolejności
    for (int i = pathLength - 1; i >= 0; --i)
    {
        oss << path[i] << " ";
    }
    oss << "\n";

    // Sprzątanie
    delete[] distance;
    delete[] predecessor;
    delete[] path;
    return oss.str();
}
