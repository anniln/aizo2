#pragma once
#include "../models/ListGraph.h"
#include <iostream>

#include "GraphShortPathAlgorithmTester.h"

class DijkstryAlgorithmOnDirectedListGraph : public GraphShortPathAlgorithmTester<ListGraph>
{
public:
    virtual ~DijkstryAlgorithmOnDirectedListGraph() = default;
    std::string TestGraphAlgorithm(const ListGraph& graph, int startNode, int endNode, bool outputResults) const;

private:
    int MinDistance(unsigned int dist[], bool sptSet[], int nodeCount) const;
};
