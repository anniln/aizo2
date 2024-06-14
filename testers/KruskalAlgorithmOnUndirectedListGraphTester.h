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

    std::string TestGraphAlgorithm(const ListGraph& graph, bool outputResults) const override
    {
        vector<Edge> edges = graph.GetEdges(); // Pobieranie wszystkich krawędzi z grafu

        // TODO: use own sort implementation
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
private:
    static void HeapSort(std::vector<Edge>& vec) {
        HeapCreateDown(vec);

        for (int i = vec.size() - 1; i > 0; i--) {
            std::swap(vec[0].value, vec[i].value);
            HeapFixDown(vec, 0, i);
        }
    }

    static void HeapCreateDown(std::vector<Edge>& vec) {
        for (int i = (vec.size() - 1 - 1) / 2; i >= 0; --i) {
            HeapFixDown(vec, i, vec.size());
        }
    }

    static void HeapFixDown(std::vector<Edge>& vec, int index, int size) {
        while (index < size) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int parent = index;

            if (leftChild < size && vec[leftChild].value > vec[parent].value)
                parent = leftChild;
            if (rightChild < size && vec[rightChild].value > vec[parent].value)
                parent = rightChild;

            if (parent != index) {
                std::swap(vec[index].value, vec[parent].value);
                index = parent;
            } else {
                break;
            }
        }
    }
};
;
