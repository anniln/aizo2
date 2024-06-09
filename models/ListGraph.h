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
    Adjacency** nodes;

    ~ListGraph();
    void AddAdjacency(const int fromNode, const int toNode, const unsigned int value) const; 
    std::string ToString() const;
};
