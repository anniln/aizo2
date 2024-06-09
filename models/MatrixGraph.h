#pragma once
#include <string>

struct MatrixGraph
{
    int nodeCount;
    int edgeCount;
    unsigned int** values;

    MatrixGraph(int nodeCount, int edgeCount);
    ~MatrixGraph();
    void AddEdge(int edge, int fromNode, int toNode, unsigned int value) const;
    std::string ToString() const;
};
