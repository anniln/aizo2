#include "KruskalAlgorithmOnUndirectedMatrixGraphTester.h"

#include <algorithm>
#include <sstream>

std::string KruskalAlgorithmOnUndirectedMatrixGraphTester::TestGraphAlgorithm(const MatrixGraph& graph,
                                                                              bool outputResults) const
{
    vector<Edge> edges; // Wektor do przechowywania wszystkich krawędzi grafu

    // Iteracja przez wszystkie krawędzie w macierzy incydencji
    for (int edge = 0; edge < graph.edgeCount*graph.edgeMultiplier; ++edge)
    {
        int fromNode = -1;  // Wierzchołek początkowy krawędzi
        int toNode = -1;    // Wierzchołek końcowy krawędzi
        unsigned int value = 0;  // Waga krawędzi

        // Iteracja przez wierzchołki grafu w celu znalezienia krawędzi
        for (int node = 0; node < graph.nodeCount; ++node)
        {
            if (graph.values.at(node).at(edge) != 0) // Sprawdzanie, czy krawędź istnieje między wierzchołkami
            {
                if (fromNode == -1)
                {
                    fromNode = node;   // Ustawienie wierzchołka początkowego
                    value = graph.values.at(node).at(edge); // Pobranie wagi krawędzi
                }
                else
                {
                    toNode = node; // Ustawienie wierzchołka końcowego
                    break;  // Przerywanie pętli po znalezieniu obu wierzchołków
                }
            }
        }

        if (fromNode != -1 && toNode != -1) // Jeśli krawędź ma oba końce, dodajemy ją do listy
        {
            edges.emplace_back(fromNode, toNode, value); // Dodawanie krawędzi do wektora
        }
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.value < b.value; // Sortowanie krawędzi wg wagi rosnąco
    });

    UnionFind uf(graph.nodeCount); // Tworzenie struktury UnionFind dla wierzchołków grafu
    vector<Edge> mst; // Wektor przechowujący krawędzie MST
    unsigned int totalCost = 0; // Zmienna przechowująca całkowity koszt MST

    // Iteracja przez posortowane krawędzie
    for (const auto& edge : edges)
    {
        if (uf.Find(edge.fromNode) != uf.Find(edge.toNode)) // Sprawdzanie, czy dodanie krawędzi nie tworzy cyklu
        {
            uf.Union(edge.fromNode, edge.toNode); // Łączenie zbiorów
            mst.push_back(edge); // Dodawanie krawędzi do MST
            totalCost += edge.value; // Dodawanie wagi krawędzi do całkowitego kosztu
        }
    }
        
    // Przygotowanie strumienia wyjściowego do zwrócenia lub wyświetlenia wyniku
    std::ostringstream oss;
    oss << "Edges in the MST:\n";
    for (const auto& edge : mst)
    {
        oss << "From: " << edge.fromNode << " To: " << edge.toNode << " Weight: " << edge.value << "\n"; // Wypisywanie krawędzi MST
    }
    oss << "Total cost of MST (Kruskal): " << totalCost << "\n\n"; // Wypisywanie całkowitego kosztu MST

    if (outputResults) cout << oss.str(); // Wyświetlanie wyników, jeśli jest to żądane
    return oss.str(); // Zwracanie wyników jako string
}