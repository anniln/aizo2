#pragma once
#include <string>

#include "GraphType.h"
#include <vector>

struct MatrixGraph
{
    GraphType graphType;
    int edgeMultiplier = 2;

    int nodeCount;
    int edgeCount;
    std::vector<std::vector<int>> values; // nodeCount * edgeCount

    MatrixGraph(int nodeCount, int edgeCount, GraphType graphType);
    void AddEdge(int edge, int node1, int node2, unsigned int value);
    
    std::string ToString() const;
    int GetToNode(int edge) const; 
    int GetFromNode(int edge) const; 
};
