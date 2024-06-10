#pragma once
#include <string>

#include "Edge.h"
#include "GraphType.h"

struct Adjacency
{
    Adjacency(int adjacentTo, unsigned int value, Adjacency* next = nullptr);

    int adjacentTo;
    unsigned int value;
    Adjacency* next;

    std::string ToString() const;
};

struct ListGraph
{
    GraphType graphType;
    int nodeCount;
    int edgeCount;
    Adjacency** nodes;

    ListGraph(int nodeCount, GraphType graphType = Undirected);
    ~ListGraph();
    static bool AdjacencyExists(Adjacency* nodeAdjacencies, int toNode);
    bool AdjacencyExists(int fromNode, int toNode) const;
    void AddAdjacency(const int fromNode, const int toNode, const unsigned int value);
    Edge* GetEdges() const;
    std::string ToString() const;
};
