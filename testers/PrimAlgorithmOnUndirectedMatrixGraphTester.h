#pragma once
#include "GraphMstAlgorithmTester.h"
#include "../models/MatrixGraph.h"
#include <iostream>
#include <sstream>

class PrimAlgorithmOnUndirectedMatrixGraphTester final : public GraphMstAlgorithmTester<MatrixGraph>
{
public:
    // Funkcja pomocnicza do znalezienia minimalnego klucza
    static int MinKey(unsigned int key[], bool mstSet[], int V);

    // Algorytm Prima
    std::string TestGraphAlgorithm(const MatrixGraph& graph, bool outputResults) const override;
};
