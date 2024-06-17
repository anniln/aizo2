#include "BellmanFordAlgorithmOnDirectedMatrixGraph.h"

std::string BellmanFordAlgorithmOnDirectedMatrixGraphTester::TestGraphAlgorithm(const MatrixGraph& graph, int startNode,
    int endNode, bool outputResults) const
{
    int nodeCount = graph.nodeCount; // Liczba wierzchołków w grafie
    int edgeCount = graph.edgeCount; // Liczba krawędzi w grafie
    unsigned int* distance = new unsigned int[nodeCount](); // Tablica odległości od wierzchołka startowego do każdego innego wierzchołka
    int* predecessor = new int[nodeCount](); // Tablica poprzedników do rekonstrukcji ścieżki

    // Inicjalizacja odległości
    for (int i = 0; i < nodeCount; ++i)
    {
        distance[i] = UINT_MAX; // Ustawienie początkowej odległości jako nieskończoność (reprezentowana przez UINT_MAX)
        predecessor[i] = -1; // Ustawienie poprzedników na -1 (brak poprzednika)
    }
    distance[startNode] = 0; // Odległość do wierzchołka startowego wynosi 0

    // Relaksacja krawędzi
    // Wykonujemy nodeCount - 1 iteracji, ponieważ w najgorszym przypadku najdłuższa możliwa
    // ścieżka między dwoma wierzchołkami w grafie bez cykli to (nodeCount - 1) krawędzi.
    for (int i = 1; i <= nodeCount - 1; ++i) // Powtarzanie procesu relaksacji |V| - 1 razy
    {
        // Przechodzimy przez każdą krawędź w grafie
        for (int e = 0; e < edgeCount * graph.edgeMultiplier; ++e)
        {
            int u = graph.GetFromNode(e); // Wierzchołek początkowy krawędzi
            int v = graph.GetToNode(e); // Wierzchołek końcowy krawędzi
            if (u != -1 && v != -1)
            {
                unsigned int weight = graph.values[u][e]; // Waga krawędzi

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
        int u = graph.GetFromNode(e); // Wierzchołek początkowy krawędzi
        int v = graph.GetToNode(e); // Wierzchołek końcowy krawędzi
        if (u != -1 && v != -1)
        {
            unsigned int weight = graph.values[u][e]; // Waga krawędzi
            if (distance[u] != UINT_MAX &&
                distance[u] + weight < distance[v])
            {
                oss << "Cykl ujemny wykryty" << "\n"; // Wykrycie cyklu ujemnego
                delete[] distance; // Zwolnienie pamięci tablicy odległości
                delete[] predecessor; // Zwolnienie pamięci tablicy poprzedników
                if (outputResults) std::cout << oss.str(); // Wyświetlenie wyniku, jeśli to wymagane
                return oss.str(); // Zwrócenie wyniku
            }
        }
    }

    // Konstruowanie ścieżki
    oss << "Path: ";
    if (distance[endNode] == UINT_MAX) // Jeśli nie ma ścieżki do wierzchołka końcowego
    {
        oss << "No path\n"; // Wyświetlenie informacji o braku ścieżki
    }
    else
    {
        int current = endNode; // Zaczynamy od wierzchołka końcowego
        int* path = new int[nodeCount](); // Dynamiczna tablica do przechowywania ścieżki
        int pathLength = 0;

        while (current != -1) // Przechodzenie wstecz po poprzednikach aż do wierzchołka startowego
        {
            path[pathLength++] = current; // Dodanie aktualnego wierzchołka do ścieżki
            current = predecessor[current]; // Przejście do poprzednika
        }

        // Drukowanie ścieżki w odpowiedniej kolejności
        for (int i = pathLength - 1; i >= 0; --i) // Iterowanie od końca do początku, aby wydrukować ścieżkę od wierzchołka startowego do końcowego
        {
            oss << path[i] << " "; // Dodanie wierzchołka do wyniku
        }
        // Wyświetlanie najkrótszej ścieżki
        oss << "Total cost (shortest path Bellman-Ford) from node " << startNode << " to node " << endNode << " is: " << distance[endNode] << "\n"; // Wyświetlenie całkowitego kosztu najkrótszej ścieżki od wierzchołka startowego do końcowego
        delete[] path; // Zwolnienie pamięci tablicy ścieżki
    }

    // Zwolnienie pamięci
    delete[] distance; // Zwolnienie pamięci tablicy odległości
    delete[] predecessor; // Zwolnienie pamięci tablicy poprzedników

    if (outputResults) std::cout << oss.str(); // Wyświetlenie wyniku, jeśli to wymagane
    return oss.str(); // Zwrócenie wyniku
}