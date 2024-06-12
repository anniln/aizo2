#pragma once
#include <string>

#include "GraphType.h"

struct MatrixGraph
{
    GraphType graphType;
    int edgeMultiplier = 2;
    int nodeCount;
    int edgeCount;
    int** values;

    MatrixGraph(int nodeCount, int edgeCount, GraphType graphType = Undirected);
    ~MatrixGraph();
    void AddEdge(int edge, int node1, int node2, unsigned int value) const;
    std::string ToString() const;
    int GetToNode(int edge) const; 
    int GetFromNode(int edge) const; 
};
