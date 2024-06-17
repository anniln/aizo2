#include "KruskalAlgorithmOnUndirectedListGraphTester.h"

#include <algorithm>
#include <sstream>

// Konstruktor klasy UnionFind inicjalizujący wektory parent i rank
UnionFind::UnionFind(int size) : parent(size), rank(size, 0)
{
    // Inicjalizacja rodzica jako samego siebie dla każdego wierzchołka
    for (int i = 0; i < size; ++i)
    {
        parent[i] = i; 
    }
}

// Metoda Find z path compression
int UnionFind::Find(int p)
{
    // Jeśli p nie jest korzeniem, znajdź jego korzeń rekurencyjnie
    // i zaktualizuj rodzica p (path compression)
    if (parent[p] != p)
    {
        parent[p] = Find(parent[p]); 
    }
    return parent[p];
}

// Metoda Union łącząca dwa zbiory
void UnionFind::Union(int p, int q)
{
    int rootP = Find(p); // Znajdź korzeń dla p
    int rootQ = Find(q); // Znajdź korzeń dla q
    // Jeśli korzenie są różne, połącz drzewa
    if (rootP != rootQ)
    {
        // Łączenie drzew według rangi
        if (rank[rootP] > rank[rootQ])
        {
            parent[rootQ] = rootP; 
        }
        else if (rank[rootP] < rank[rootQ])
        {
            parent[rootP] = rootQ;
        }
        else
        {
            parent[rootQ] = rootP;
            rank[rootP]++;
        }
    }
}

// Algorytm Kruskala
std::string KruskalAlgorithmOnUndirectedListGraphTester::TestGraphAlgorithm(const ListGraph& graph, bool outputResults) const
{
    // Pobieranie wszystkich krawędzi z grafu
    vector<Edge> edges = graph.GetEdges(); 

    // Sortowanie krawędzi według wagi
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.value < b.value;
    });

    // Inicjalizacja struktury zbiorów rozłącznych
    UnionFind uf(graph.nodeCount); 
    // Wektor krawędzi MST
    vector<Edge> mst; 
    // Inicjalizacja sumy wag MST
    unsigned int totalCost = 0; 

    // Przechodzenie przez wszystkie krawędzie
    for (const auto& edge : edges)
    {
        // Jeśli wierzchołki krawędzi są w różnych zbiorach, dodaj krawędź do MST
        if (uf.Find(edge.fromNode) != uf.Find(edge.toNode))
        {
            // Łączenie zbiorów
            uf.Union(edge.fromNode, edge.toNode); 
            // Dodawanie krawędzi do MST
            mst.push_back(edge); 
            // Dodawanie wagi krawędzi do sumy MST
            totalCost += edge.value; 
        }
    }

    // Tworzenie strumienia wyjściowego do wyświetlenia wyników
    std::ostringstream oss;
    oss << Edge::ArrayToString(mst);
    oss << "Total cost of MST (Kruskal): " << totalCost << "\n\n"; // Wypisywanie sumy wag MST

    // Jeśli outputResults jest prawdziwy, wyświetl wyniki
    if (outputResults)
        cout << oss.str();
    return oss.str();
}