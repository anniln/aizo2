#include "BellmanFordAlgorithmOnDirectedListGraphTester.h"

#include <sstream>

std::string BellmanFordAlgorithmOnDirectedListGraphTester::TestGraphAlgorithm(const ListGraph& graph, int startNode,
                                                                              int endNode, bool outputResults) const
{
    int nodeCount = graph.nodeCount; // Liczba wierzchołków w grafie
    int* distance = new int[nodeCount]; // Tablica odległości od wierzchołka startowego do każdego innego wierzchołka
    int* predecessor = new int[nodeCount]; // Tablica poprzedników do rekonstrukcji ścieżki

    // Inicjalizacja odległości
    for (int i = 0; i < nodeCount; ++i)
    {
        distance[i] = UINT_MAX; // Ustawienie początkowej odległości jako nieskończoność (reprezentowana przez UINT_MAX)
        predecessor[i] = -1; // Ustawienie poprzedników na -1 (brak poprzednika)
    }
    distance[startNode] = 0; // Odległość do wierzchołka startowego wynosi 0

    // Relaksacja krawędzi
    for (int i = 1; i <= nodeCount - 1; ++i) // Powtarzanie procesu relaksacji |V| - 1 razy
    {
        for (int u = 0; u < nodeCount; ++u) // Dla każdego wierzchołka u
        {
            auto adjs = graph.nodes[u]; // Pobieranie sąsiadów wierzchołka u
            for (auto adj : adjs) // Dla każdego sąsiada adj wierzchołka u
            {
                int v = adj.adjacentTo; // Wierzchołek sąsiedni v
                unsigned int weight = adj.value; // Waga krawędzi (u, v)
                if (distance[u] != UINT_MAX && distance[u] + weight < distance[v]) // Jeśli możliwe jest skrócenie ścieżki do v przez u
                {
                    distance[v] = distance[u] + weight; // Aktualizacja odległości do v
                    predecessor[v] = u; // Ustawienie poprzednika v na u
                }
            }
        }
    }

    // Sprawdzenie cyklu ujemnego
    std::ostringstream oss;
    for (int u = 0; u < nodeCount; ++u) // Dla każdego wierzchołka u
    {
        auto adjs = graph.nodes[u]; // Pobieranie sąsiadów wierzchołka u
        for (auto adj : adjs) // Dla każdego sąsiada adj wierzchołka u
        {
            int v = adj.adjacentTo; // Wierzchołek sąsiedni v
            unsigned int weight = adj.value; // Waga krawędzi (u, v)
            if (distance[u] != UINT_MAX && distance[u] + weight < distance[v]) // Jeśli można jeszcze skrócić odległość do v, to istnieje cykl ujemny
            {
                oss << "Cykl ujemny wykryty" << "\n"; // Wykrycie cyklu ujemnego
                delete[] distance; // Zwolnienie pamięci tablicy odległości
                delete[] predecessor; // Zwolnienie pamięci tablicy poprzedników
                if (outputResults) cout << oss.str(); // Wyświetlenie wyniku, jeśli to wymagane
                return oss.str(); // Zwrócenie wyniku
            }
        }
    }

    //// Wyświetlanie najkrótszej ścieżki
    //oss << "Total cost (shortest path Bellman-Ford) from node " << startNode << " to node " << endNode << " is: " << distance[
    //    endNode] << "\n"; // Wyświetlenie całkowitego kosztu najkrótszej ścieżki od wierzchołka startowego do końcowego

    //// Konstruowanie ścieżki
    //oss << "Path: ";
    //if (distance[endNode] == UINT_MAX) // Jeśli nie ma ścieżki do wierzchołka końcowego
    //{
    //    oss << "No path\n"; // Wyświetlenie informacji o braku ścieżki
    //}
    //else
    //{
    //    int current = endNode; // Zaczynamy od wierzchołka końcowego
    //    int* path = new int[nodeCount]; // Dynamiczna tablica do przechowywania ścieżki
    //    int pathLength = 0; // Długość ścieżki

    //    while (current != -1) // Przechodzenie wstecz po poprzednikach aż do wierzchołka startowego
    //    {
    //        path[pathLength++] = current; // Dodanie aktualnego wierzchołka do ścieżki
    //        current = predecessor[current]; // Przejście do poprzednika
    //    }

    //    // Drukowanie ścieżki w odpowiedniej kolejności
    //    for (int i = pathLength - 1; i >= 0; --i) // Iterowanie od końca do początku, aby wydrukować ścieżkę od wierzchołka startowego do końcowego
    //    {
    //        oss << path[i] << " "; // Dodanie wierzchołka do wyniku
    //    }
    //    oss << "\n"; 
    //    delete[] path; // Zwolnienie pamięci tablicy ścieżki
    //}

    // Wyświetlanie najkrótszej ścieżki i wag
    std::vector<int> path;
    int current = endNode;
    while (current != -1) {
        path.push_back(current);
        current = predecessor[current];
    }

    oss << "Path: ";
    if (path.size() == 1 && path[0] == endNode) { // Brak ścieżki
        oss << "No path\n";
    } else {
        reverse(path.begin(), path.end());
        
        for (size_t i = 0; i < path.size(); ++i) {
            if (i > 0) {
                int u = path[i-1];
                int v = path[i];
                int edgeWeight = distance[v] - distance[u]; // Obliczenie wagi krawędzi
                oss << u << " -> " << v << " (Weight: " << edgeWeight << ") ";
            }
        }
        oss << "\nTotal cost (shortest path Bellman-Ford) from node " << startNode << " to node " << endNode << " is: " << distance[endNode] << "\n";
    }


    //Zwalnianie pamięci
    delete[] distance; // Zwolnienie pamięci tablicy odległości
    delete[] predecessor; // Zwolnienie pamięci tablicy poprzedników

    if (outputResults) // Jeśli wymagane jest wyświetlenie wyników
        cout << oss.str(); // Wyświetlenie wyniku
    return oss.str(); // Zwrócenie wyniku
}
