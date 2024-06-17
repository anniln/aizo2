#pragma once
#include "../models/MatrixGraph.h"
#include <iostream>
#include <sstream>

#include "GraphShortPathAlgorithmTester.h"

class DijkstryAlgorithmOnDirectedMatrixGraph : public GraphShortPathAlgorithmTester<MatrixGraph>
{
public:
    virtual ~DijkstryAlgorithmOnDirectedMatrixGraph() = default;
    std::string TestGraphAlgorithm(const MatrixGraph& graph, int startNode, int endNode, bool outputResults) const;

private:
    int MinDistance(unsigned int dist[], bool sptSet[], int nodeCount) const;
};
