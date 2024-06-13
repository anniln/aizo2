#pragma once
#include "../models/ListGraph.h"
#include <iostream>
#include "GraphShortPathAlgorithmTester.h"

class BellmanFordAlgorithmOnDirectedListGraphTester : public GraphShortPathAlgorithmTester<ListGraph>
{
public:
    virtual ~BellmanFordAlgorithmOnDirectedListGraphTester();

    void TestGraphAlgorithm(const ListGraph& graph, int startNode, int endNode) const override;
};
