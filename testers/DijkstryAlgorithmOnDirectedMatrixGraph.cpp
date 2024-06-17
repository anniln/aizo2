#include "DijkstryAlgorithmOnDirectedMatrixGraph.h"

// Funkcja implementująca algorytm Dijkstry
std::string DijkstryAlgorithmOnDirectedMatrixGraph::TestGraphAlgorithm(const MatrixGraph& graph, int startNode, int endNode,
                               bool outputResults) const 
{
    int nodeCount = graph.nodeCount; // Liczba wierzchołków w grafie
    unsigned int* distances = new unsigned int[nodeCount]; // Tablica przechowująca odległości od wierzchołka startowego
    int* predecessors = new int[nodeCount]; // Tablica przechowująca poprzedników w najkrótszej ścieżce
    bool* sptSet = new bool[nodeCount]; // Tablica przechowująca informacje o tym, czy wierzchołek został już odwiedzony

    // Inicjalizacja
    for (int i = 0; i < nodeCount; i++)
    {
        distances[i] = UINT_MAX; // Ustawienie początkowych odległości na nieskończoność
        sptSet[i] = false; // Żaden wierzchołek jeszcze nie został odwiedzony
        predecessors[i] = -1; // Brak poprzedników dla początkowego wierzchołka
    }

    distances[startNode] = 0; // Odległość od wierzchołka początkowego do samego siebie wynosi zero

    // Algorytm Dijkstry
    for (int count = 0; count < nodeCount - 1; count++)
    {
        int u = MinDistance(distances, sptSet, nodeCount); // Wybór wierzchołka o najmniejszej odległości

        if (u == -1)
            break; // Przerywamy, jeśli nie znaleziono wierzchołka

        sptSet[u] = true; // Oznaczamy wierzchołek jako odwiedzony

        // Iterujemy przez kolumny macierzy incydencji
        for (int v = 0; v < graph.edgeCount * graph.edgeMultiplier; v++)
        {
            if (graph.values[u][v] > 0) // Sprawdzamy, czy istnieje krawędź z wierzchołka u do v
            {
                unsigned int weight = graph.values[u][v]; // Waga krawędzi
                const int neighbor = graph.GetToNode(v); // Pobieramy wierzchołek sąsiedni

                // Aktualizacja odległości do sąsiada, jeśli znaleziono krótszą ścieżkę
                if (!sptSet[neighbor] && distances[u] != UINT_MAX && distances[u] + weight < distances[neighbor])
                {
                    distances[neighbor] = distances[u] + weight; // Aktualizacja odległości do sąsiada
                    predecessors[neighbor] = u; // Zapisanie poprzednika dla aktualnej ścieżki
                }
            }
        }
    }

    // Wypisywanie wyników
    std::ostringstream oss;

    oss << "Path: ";
    if (distances[endNode] == UINT_MAX)
    {
        oss << "no path\n"; // Wyświetlenie informacji o braku ścieżki
    }
    else
    {
        int* path = new int[nodeCount]; // Tablica przechowująca wierzchołki w najkrótszej ścieżce
        int path_index = 0;
        for (int at = endNode; at != -1; at = predecessors[at])
        {
            path[path_index++] = at; // Dodawanie wierzchołków do ścieżki
        }
        std::reverse(path, path + path_index); // Odwrócenie tablicy, aby ścieżka była w kolejności od wierzchołka początkowego do docelowego
        for (int i = 0; i < path_index; ++i)
        {
            oss << path[i] << " "; // Wypisanie ścieżki
        }

        oss << "Total cost (shortest path Dijkstry) from node " << startNode << " to node " << endNode << " is: " << distances[endNode] << "\n"; // Wyświetlenie całkowitego kosztu najkrótszej ścieżki od wierzchołka startowego do końcowego

        delete[] path; // Zwolnienie pamięci zaalokowanej dla tablicy ścieżki
    }

    // Zwolnienie pamięci
    delete[] distances; // Zwolnienie pamięci tablicy odległości
    delete[] predecessors; // Zwolnienie pamięci tablicy poprzedników
    delete[] sptSet; // Zwolnienie pamięci tablicy sptSet

    if (outputResults)
        std::cout << oss.str(); // Wyświetlenie wyniku, jeśli to wymagane

    return oss.str(); // Zwrócenie wyniku
}

// Funkcja pomocnicza do znalezienia minimalnej wartości w tablicy
int DijkstryAlgorithmOnDirectedMatrixGraph::MinDistance(unsigned int dist[], bool sptSet[], int nodeCount) const
{
    unsigned int min = UINT_MAX; // Ustawienie minimalnej odległości na nieskończoność
    int min_index = -1; // Indeks wierzchołka o najmniejszej odległości

    for (int v = 0; v < nodeCount; v++)
        if (!sptSet[v] && dist[v] <= min) // Jeśli wierzchołek v nie został przetworzony i ma mniejszą odległość niż obecnie minimalna
        {
            min = dist[v]; // Aktualizacja minimalnej odległości
            min_index = v; // Ustawienie indeksu wierzchołka o minimalnej odległości
        }

    return min_index; // Zwracamy indeks wierzchołka o najmniejszej odległości
}


