#pragma once
#include "../models/MatrixGraph.h"
#include <iostream>
#include <sstream>

#include "GraphShortPathAlgorithmTester.h"

class BellmanFordAlgorithmOnDirectedMatrixGraphTester : public GraphShortPathAlgorithmTester<MatrixGraph>
{
public:
    virtual ~BellmanFordAlgorithmOnDirectedMatrixGraphTester() = default;

    std::string TestGraphAlgorithm(const MatrixGraph& graph, int startNode, int endNode, bool outputResults) const; 
};
