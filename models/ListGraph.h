#pragma once
#include <string>
#include <vector>

#include "Edge.h"
#include "GraphType.h"

struct Adjacency
{
    Adjacency(int adjacentTo, unsigned int value, Adjacency* next = nullptr);

    int adjacentTo;
    unsigned int value;

    std::string ToString() const;
};

struct ListGraph
{
    GraphType graphType;
    int nodeCount;
    int edgeCount;
    std::vector<std::vector<Adjacency>> nodes;

    ListGraph(int nodeCount, GraphType graphType = Undirected);
    static bool AdjacencyExists(const std::vector<Adjacency>& nodeAdjacencies, int toNode);
    bool AdjacencyExists(int fromNode, int toNode) const;
    void AddAdjacency(const int fromNode, const int toNode, const unsigned int value);
    std::vector<Edge> GetEdges() const;
    std::string ToString() const;
};
