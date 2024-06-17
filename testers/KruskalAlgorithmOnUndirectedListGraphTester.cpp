#include "KruskalAlgorithmOnUndirectedListGraphTester.h"

#include <algorithm>
#include <sstream>

UnionFind::UnionFind(int size): parent(size), rank(size, 0)
{
    for (int i = 0; i < size; ++i)
    {
        parent[i] = i; // Inicjalizacja rodzica jako samego siebie
    }
}

int UnionFind::Find(int p)
{
    if (parent[p] != p)
    {
        parent[p] = Find(parent[p]); // path compression
    }
    return parent[p];
}

void UnionFind::Union(int p, int q)
{
    int rootP = Find(p);
    int rootQ = Find(q);
    if (rootP != rootQ)
    {
        if (rank[rootP] > rank[rootQ])
        {
            parent[rootQ] = rootP; // Łączenie drzew według rangi
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

std::string KruskalAlgorithmOnUndirectedListGraphTester::TestGraphAlgorithm(const ListGraph& graph,
    bool outputResults) const
{
    vector<Edge> edges = graph.GetEdges(); // Pobieranie wszystkich krawędzi z grafu

    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.value < b.value;
    });        

    UnionFind uf(graph.nodeCount); // Inicjalizacja struktury zbiorów rozłącznych
    vector<Edge> mst; // Wektor krawędzi MST
    unsigned int totalCost = 0; // Inicjalizacja sumy wag MST

    for (const auto& edge : edges)
    {
        if (uf.Find(edge.fromNode) != uf.Find(edge.toNode))
        {
            uf.Union(edge.fromNode, edge.toNode); // Łączenie zbiorów
            mst.push_back(edge); // Dodawanie krawędzi do MST
            totalCost += edge.value; // Dodawanie wagi krawędzi do sumy MST
        }
    }
        
    std::ostringstream oss;
    oss << Edge::ArrayToString(mst);
    oss << "Total cost of MST (Kruskal): " << totalCost << "\n\n"; // Wypisywanie sumy wag MST

    if (outputResults)
        cout<< oss.str();
    return oss.str();
}
