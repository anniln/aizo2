#include "BellmanFordAlgorithmOnDirectedListGraphTester.h"

BellmanFordAlgorithmOnDirectedListGraphTester::~BellmanFordAlgorithmOnDirectedListGraphTester()
{
}

void BellmanFordAlgorithmOnDirectedListGraphTester::TestGraphAlgorithm(const ListGraph& graph, int startNode, int endNode)
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
            Adjacency* current = graph.nodes[u];
            while (current)
            {
                int v = current->adjacentTo;
                unsigned int weight = current->value;
                if (distance[u] != UINT_MAX &&
                    distance[u] + weight < distance[v])
                {
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;
                }
                current = current->next;
            }
        }
    }

    // Sprawdzenie cyklu ujemnego
    for (int u = 0; u < nodeCount; ++u)
    {
        Adjacency* current = graph.nodes[u];
        while (current)
        {
            int v = current->adjacentTo;
            unsigned int weight = current->value;
            if (distance[u] != UINT_MAX &&
                distance[u] + weight < distance[v])
            {
                std::cout << "Cykl ujemny wykryty" << "\n";
                delete[] distance;
                delete[] predecessor;
                return;
            }
            current = current->next;
        }
    }

    // Wyświetlanie najkrótszej ścieżki
    std::cout << "Total cost (shortest path) from node " << startNode << " to node " << endNode << " is: " << distance[endNode] << "\n";
        
    // Konstruowanie ścieżki
    std::cout << "Path: ";
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
        std::cout << path[i] << " ";
    }
    std::cout << "\n";

    // Sprzątanie
    delete[] distance;
    delete[] predecessor;
    delete[] path;
}

