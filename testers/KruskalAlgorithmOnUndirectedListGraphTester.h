#pragma once
#include <iostream>

#include "./GraphMstAlgorithmTester.h"
#include "../models/ListGraph.h"
#include "../models/Edge.h"

using namespace std;

// Klasa reprezentująca strukturę zbiorów rozłącznych
class UnionFind
{
public:
    UnionFind(int size) : parent(new int[size]), rank(new int[size])
    {
        for (int i = 0; i < size; ++i)
        {
            parent[i] = i; // Inicjalizacja rodzica jako samego siebie
            rank[i] = 0; // Inicjalizacja rangi jako 0
        }
    }

    ~UnionFind()
    {
        delete[] parent; // Zwalnianie tablicy rodziców
        delete[] rank; // Zwalnianie tablicy rang
    }
    
    int Find(int p) // Znajdowanie reprezentanta zbioru z path compression
    {
        if (parent[p] != p)
        {
            parent[p] = Find(parent[p]); // path compression
        }
        return parent[p];
    }

    void Union(int p, int q) // Łączenie dwóch zbiorów
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

private:
    int* parent; // Tablica rodziców
    int* rank; // Tablica rang
};

class KruskalAlgorithmOnUndirectedListGraphTester : public GraphMstAlgorithmTester<ListGraph>
{
public:
    virtual ~KruskalAlgorithmOnUndirectedListGraphTester() = default;

    void TestGraphAlgorithm(const ListGraph& graph) const override
    {
        Edge* edges = graph.GetEdges(); // Pobieranie wszystkich krawędzi z grafu
        edges = Edge::SortEdges(edges); // Sortowanie krawędzi według wagi

        UnionFind uf(graph.nodeCount); // Inicjalizacja struktury zbiorów rozłącznych
        Edge* mst = nullptr; // Wskaźnik na początek listy MST
        Edge* last = nullptr; // Wskaźnik na ostatnią krawędź w MST

        unsigned int totalCost = 0; // Inicjalizacja sumy wag MST

        while (edges != nullptr)
        {
            if (uf.Find(edges->fromNode) != uf.Find(edges->toNode))
            {
                uf.Union(edges->fromNode, edges->toNode); // Łączenie zbiorów
                if (mst == nullptr)
                {
                    mst = edges; // Inicjalizacja listy MST
                }
                else
                {
                    last->next = edges; // Dodawanie krawędzi do MST
                }
                last = edges; // Aktualizacja wskaźnika na ostatnią krawędź w MST
                totalCost += edges->value; // Dodawanie wagi krawędzi do sumy MST
            }
            edges = edges->next; // Przechodzenie do następnej krawędzi
        }

        if (last != nullptr)
        {
            last->next = nullptr; // Zakończenie listy MST
        }
        cout << Edge::ArrayToString(mst);
        std::cout << "Total cost of MST (Kruskal): " << totalCost << "\n\n"; // Wypisywanie sumy wag MST
    }
};
