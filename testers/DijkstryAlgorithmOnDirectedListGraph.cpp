#include "DijkstryAlgorithmOnDirectedListGraph.h"

#include <sstream>

// Funkcja implementująca algorytm Dijkstry
std::string DijkstryAlgorithmOnDirectedListGraph::TestGraphAlgorithm(const ListGraph& graph, int startNode, int endNode,
                                                                     bool outputResults) const
{
    int nodeCount = graph.nodeCount; // Liczba wierzchołków w grafie
    unsigned int* distances = new unsigned int[nodeCount]; // Tablica odległości od wierzchołka startowego do każdego innego wierzchołka
    int* predecessors = new int[nodeCount]; // Tablica poprzedników do rekonstrukcji ścieżki
    bool* sptSet = new bool[nodeCount]; // Tablica do śledzenia wierzchołków, których najkrótsza ścieżka została już znaleziona

    // Inicjalizacja
    for (int i = 0; i < nodeCount; i++)
    {
        distances[i] = UINT_MAX; // Ustawienie początkowej odległości jako nieskończoność (reprezentowana przez UINT_MAX)
        sptSet[i] = false; // Ustawienie wszystkich wierzchołków jako nieodwiedzone
        predecessors[i] = -1; // Ustawienie poprzedników na -1 (brak poprzednika)
    }

    distances[startNode] = 0; // Odległość do wierzchołka startowego wynosi 0

    // Algorytm Dijkstry
    for (int count = 0; count < nodeCount - 1; count++)
    {
        int u = MinDistance(distances, sptSet, nodeCount); // Znalezienie wierzchołka o minimalnej odległości, który nie został jeszcze przetworzony

        if (u == -1) break; // Przerywamy, jeśli nie znaleziono wierzchołka

        sptSet[u] = true; // Oznaczamy wierzchołek u jako przetworzony

        auto adjs = graph.nodes[u]; // Pobieranie sąsiadów wierzchołka u
        for (auto adj : adjs)
        {
            int v = adj.adjacentTo; // Wierzchołek sąsiedni v
            unsigned int weight = adj.value; // Waga krawędzi (u, v)

            // Aktualizacja odległości do wierzchołka v, jeśli znaleziono krótszą ścieżkę przez u
            if (!sptSet[v] && distances[u] != UINT_MAX && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight; // Aktualizacja odległości do wierzchołka v
                predecessors[v] = u; // Ustawienie poprzednika wierzchołka v na u
            }
        }
    }

    //// Wypisywanie wyników
    //std::ostringstream oss;
    //oss << "Total cost (shortest path Dijkstry) from node " << startNode << " to node " << endNode << " is: " <<
    //    distances[endNode] << "\n"; // Wyświetlenie całkowitego kosztu najkrótszej ścieżki od wierzchołka startowego do końcowego
//
    //oss << "Path: ";
    //if (distances[endNode] == UINT_MAX) // Jeśli nie ma ścieżki do wierzchołka końcowego
    //{
    //    oss << "No path\n"; // Wyświetlenie informacji o braku ścieżki
    //}
    //else
    //{
    //    int* path = new int[nodeCount]; // Dynamiczna tablica do przechowywania ścieżki
    //    int path_index = 0; // Indeks ścieżki
    //    for (int at = endNode; at != -1; at = predecessors[at])
    //    {
    //        path[path_index++] = at; // Dodanie wierzchołka do ścieżki
    //    }
    //    std::reverse(path, path + path_index); // Odwrócenie ścieżki, aby zaczynała się od wierzchołka startowego
    //    for (int i = 0; i < path_index; ++i)
    //    {
    //        oss << path[i] << " "; // Dodanie wierzchołka do wyniku
    //    }
    //    oss << "\n"; // Nowa linia na końcu ścieżki
    //    delete[] path; // Zwolnienie pamięci tablicy ścieżki
    //}

    // Wypisywanie wyników
    std::ostringstream oss;
    std::vector<int> path;
    int current = endNode;
    while (current != -1) {
        path.push_back(current);
        current = predecessors[current];
    }

    oss << "Path: ";
    if (path.size() == 1 && path[0] == endNode) { // Brak ścieżki
        //oss << "No path exists from node " << startNode << " to node " << endNode << "\n";
        oss << "no path\n";
    } else {
        std::reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); ++i) {
            if (i > 0) {
                int u = path[i-1];
                int v = path[i];
                int edgeWeight = distances[v] - distances[u]; // Obliczenie wagi krawędzi
                oss << u << " -> " << v << " (Weight: " << edgeWeight << ") ";
            }
        }
        oss << "\nTotal cost (shortest path Dijkstry) from node " << startNode << " to node " << endNode << " is: " << distances[endNode] << "\n";
    }

    // Zwolnienie pamięci
    delete[] distances; // Zwolnienie pamięci tablicy odległości
    delete[] predecessors; // Zwolnienie pamięci tablicy poprzedników
    delete[] sptSet; // Zwolnienie pamięci tablicy sptSet

    if (outputResults) cout << oss.str(); // Wyświetlenie wyniku, jeśli to wymagane
    return oss.str(); // Zwrócenie wyniku
}

// Funkcja pomocnicza do znalezienia minimalnej wartości w tablicy
int DijkstryAlgorithmOnDirectedListGraph::MinDistance(unsigned int dist[], bool sptSet[], int nodeCount) const
{
    unsigned int min = UINT_MAX; // Ustawienie minimalnej odległości jako nieskończoność
    int min_index = -1; // Indeks wierzchołka o minimalnej odległości

    for (int v = 0; v < nodeCount; v++)
        if (!sptSet[v] && dist[v] <= min) // Jeśli wierzchołek v nie został przetworzony i ma mniejszą odległość niż obecnie minimalna
        {
            min = dist[v]; // Aktualizacja minimalnej odległości
            min_index = v; // Ustawienie indeksu wierzchołka o minimalnej odległości
        }

    return min_index; // Zwrócenie indeksu wierzchołka o minimalnej odległości
}
