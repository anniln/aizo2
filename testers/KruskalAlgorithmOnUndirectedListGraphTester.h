﻿#pragma once
#include <iostream>

#include "./GraphMstAlgorithmTester.h"
#include "../models/ListGraph.h"
#include "../models/Edge.h"

using namespace std;

// Klasa reprezentująca strukturę zbiorów rozłącznych
class UnionFind
{
public:
    UnionFind(int size) : parent(size), rank(size, 0)
    {
        for (int i = 0; i < size; ++i)
        {
            parent[i] = i; // Inicjalizacja rodzica jako samego siebie
        }
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
    vector<int> parent; // Wektor rodziców
    vector<int> rank; // Wektor rang
};

class KruskalAlgorithmOnUndirectedListGraphTester : public GraphMstAlgorithmTester<ListGraph>
{
public:
    virtual ~KruskalAlgorithmOnUndirectedListGraphTester() = default;

    std::string TestGraphAlgorithm(const ListGraph& graph) const override
    {
        vector<Edge> edges = graph.GetEdges(); // Pobieranie wszystkich krawędzi z grafu
        BubbleSort(edges); // Sortowanie krawędzi według wagi

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

        return oss.str();
    }
private:
    void BubbleSort(vector<Edge>& edges) const
    {
        int n = edges.size();
        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = 0; j < n - i - 1; ++j)
            {
                if (edges[j].value > edges[j + 1].value)
                {
                    Swap(edges[j], edges[j + 1]);
                }
            }
        }
    }

    void Swap(Edge& a, Edge& b) const
    {
        Edge temp = a;
        a = b;
        b = temp;
    }
};
;
