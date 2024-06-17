#pragma once
#include "../models/ListGraph.h"
#include <iostream>
#include <string>
#include "GraphShortPathAlgorithmTester.h"

class BellmanFordAlgorithmOnDirectedListGraphTester : public GraphShortPathAlgorithmTester<ListGraph>
{
public:
    std::string TestGraphAlgorithm(const ListGraph& graph, int startNode, int endNode, bool outputResults) const;
};
