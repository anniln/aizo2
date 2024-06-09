#include "ListGraph.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Adjacency::Adjacency(int adjacentTo, const unsigned value, Adjacency* next)
    : adjacentTo(adjacentTo), value(value), next(next)
{
}

string Adjacency::ToString() const
{
    ostringstream oss;
    oss << "Adjacency[->N:" << adjacentTo << ",V:" << value << "]";
    return oss.str();  
}

ListGraph::~ListGraph()
{
    for (int i = 0; i < nodeCount; i++)
    {
        Adjacency* p = nodes[i];
        while (p)
        {
            Adjacency* r = p;
            p = p->next;
            delete r;
        }
        nodes[i] = nullptr;
    }

    delete [] nodes;
    nodes = nullptr;
}

string ListGraph::ToString() const
{
    ostringstream oss;
    oss << "GraphList[" << '\n';
    for (int i = 0; i < nodeCount; i++)
    {
        oss << "N[" << i << "] = ";
        Adjacency* p = nodes[i];
        while (p)
        {
            oss << p->ToString() << " ";
            p = p->next;
        }
        oss << '\n';
    }
    oss << ']' << '\n';
    return oss.str(); 
}

void ListGraph::AddAdjacency(const int fromNode, const int toNode, const unsigned int value) const
{
    // fromNode adjacency
    Adjacency* next = nodes[fromNode];
    Adjacency* newAdjacentTo = new Adjacency(toNode, value, next);
    nodes[fromNode] =  newAdjacentTo;
    // toNode adjacency
    next = nodes[toNode];
    newAdjacentTo = new Adjacency(fromNode, value, next);
    nodes[toNode] =  newAdjacentTo;
}
