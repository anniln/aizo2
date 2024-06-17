#pragma once
#include "GraphMstAlgorithmTester.h"
#include "../models/ListGraph.h"
#include <iostream>

class PrimAlgorithmOnUndirectedListGraphTester : public GraphMstAlgorithmTester<ListGraph>
{
public:
    // Funkcja pomocnicza do znalezienia minimalnego klucza
    static int MinKey(unsigned int key[], bool mstSet[], int V);

    //Algorytm Prima dla listy
    std::string TestGraphAlgorithm(const ListGraph& graph, bool outputResults) const override;
};
