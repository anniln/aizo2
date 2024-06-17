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
    UnionFind(int size);

    // Znajdowanie reprezentanta zbioru z path compression
    int Find(int p);

    // Łączenie dwóch zbiorów
    void Union(int p, int q);

private:
    vector<int> parent; // Wektor rodziców
    vector<int> rank; // Wektor rang
};

class KruskalAlgorithmOnUndirectedListGraphTester : public GraphMstAlgorithmTester<ListGraph>
{
public:
    virtual ~KruskalAlgorithmOnUndirectedListGraphTester() = default;

    std::string TestGraphAlgorithm(const ListGraph& graph, bool outputResults) const override;

private:
};
