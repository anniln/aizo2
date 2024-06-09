#pragma once
#include <string>

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
    int nodeCount;
    int edgeCount;
    Adjacency** nodes;

    ListGraph(int nodeCount);
    ~ListGraph();
    static bool AdjacencyExists(Adjacency* nodeAdjacencies, int toNode);
    void AddAdjacency(const int fromNode, const int toNode, const unsigned int value); 
    std::string ToString() const;
};
