#pragma once
#include "../models/ListGraph.h"
#include <iostream>
#include "GraphShortPathAlgorithmTester.h"

class BellmanFordAlgorithmOnDirectedListGraph : GraphShortPathAlgorithmTester<ListGraph>
{
public:
    virtual ~BellmanFordAlgorithmOnDirectedListGraph();

    void TestGraphAlgorithm(const ListGraph& graph, int startNode, int endNode) override;
};
