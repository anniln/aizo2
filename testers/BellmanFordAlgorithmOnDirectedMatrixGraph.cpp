#include "BellmanFordAlgorithmOnDirectedMatrixGraph.h"

std::string BellmanFordAlgorithmOnDirectedMatrixGraphTester::TestGraphAlgorithm(const MatrixGraph& graph, int startNode,
    int endNode, bool outputResults) const
{
    int nodeCount = graph.nodeCount;
    int edgeCount = graph.edgeCount;
    unsigned int* distance = new unsigned int[nodeCount]();
    int* predecessor = new int[nodeCount]();

    // Inicjalizacja odległości
    for (int i = 0; i < nodeCount; ++i)
    {
        distance[i] = UINT_MAX;
        predecessor[i] = -1;
    }
    distance[startNode] = 0;

    // Relaksacja krawędzi
    // Wykonujemy nodeCount - 1 iteracji, ponieważ w najgorszym przypadku najdłuższa możliwa
    // ścieżka między dwoma węzłami w grafie bez cykli to (nodeCount - 1) krawędzi.
    for (int i = 1; i <= nodeCount - 1; ++i)
    {
        // Przechodzimy przez każdą krawędź w grafie
        for (int e = 0; e < edgeCount * graph.edgeMultiplier; ++e)
        {
            int u = graph.GetFromNode(e); // wierzchołek początkowy krawędzi
            int v = graph.GetToNode(e); // wierzchołek końcowy krawędzi
            if (u != -1 && v != -1)
            {
                unsigned int weight = graph.values[u][e]; // waga krawędzi

                // Sprawdzamy, czy aktualna odległość do wierzchołka u jest mniejsza niż nieskończoność
                // oraz czy przejście przez krawędź (u, v) skróciłoby odległość do wierzchołka v
                if (distance[u] != UINT_MAX &&
                    distance[u] + weight < distance[v])
                {
                    // Aktualizujemy odległość do wierzchołka v
                    distance[v] = distance[u] + weight;
                    // Ustawiamy poprzednika wierzchołka v na u, aby móc odtworzyć ścieżkę
                    predecessor[v] = u;
                }
            }
        }
    }

    // Sprawdzenie cyklu ujemnego (u nas nie będzie)
    std::ostringstream oss;
    for (int e = 0; e < edgeCount * graph.edgeMultiplier; ++e)
    {
        int u = graph.GetFromNode(e);
        int v = graph.GetToNode(e);
        if (u != -1 && v != -1)
        {
            unsigned int weight = graph.values[u][e];
            if (distance[u] != UINT_MAX &&
                distance[u] + weight < distance[v])
            {
                oss << "Cykl ujemny wykryty" << "\n";
                delete[] distance;
                delete[] predecessor;
                if (outputResults) std::cout << oss.str();
                return oss.str();
            }
        }
    }

    // Wyświetlanie najkrótszej ścieżki


    // Wyświetlanie najkrótszej ścieżki
    oss << "Total cost (shortest path) from node " << startNode << " to node " << endNode << " is: " <<
        distance[endNode] << "\n";

    // Konstruowanie ścieżki
    oss << "Path: ";
    int current = endNode;
    int* path = new int[nodeCount](); // dynamiczna tablica do przechowywania ścieżki
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
    delete [] distance;
    delete [] predecessor;
    delete [] path;

    if (outputResults) std::cout << oss.str();
    return oss.str();
}
