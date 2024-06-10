#include "ListGraph.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Adjacency::Adjacency(int adjacentTo, const unsigned value, Adjacency* next)
    : adjacentTo(adjacentTo), value(value), next(next)
{
}

Edge* ListGraph::GetEdges() const
{
    Edge* edges = nullptr;
    Edge* last = nullptr;
    for (int i = 0; i < nodeCount; ++i)
    {
        Adjacency* adj = nodes[i];
        while (adj != nullptr)
        {
            Edge* newEdge = new Edge(i, adj->adjacentTo, adj->value);
            if (edges == nullptr)
            {
                edges = newEdge;
            }
            else
            {
                last->next = newEdge;
            }
            last = newEdge;
            adj = adj->next;
        }
    }
    return edges;
}

string Adjacency::ToString() const
{
    ostringstream oss;
    oss << "->(N:" << adjacentTo << ",v:" << value << ")";
    //oss << "-" << value << "->[" << adjacentTo << "] ";
    return oss.str();
}

ListGraph::ListGraph(int nodeCount, GraphType graphType)
: graphType(graphType), nodeCount(nodeCount), edgeCount(0)
{
    // TODO: problem with memory????
    // nodes = new Adjacency*[nodeCount]();
    Adjacency** nodes_ = new Adjacency*[nodeCount]();
    nodes = nodes_;
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

bool ListGraph::AdjacencyExists(int fromNode, int toNode) const
{
    return ListGraph::AdjacencyExists(nodes[fromNode], toNode); 
}

bool ListGraph::AdjacencyExists(Adjacency* nodeAdjacencies, int toNode)
{
    Adjacency* it = nodeAdjacencies;
    while (it != nullptr)
    {
        if (it->adjacentTo == toNode)
        {
            return true;
        }
        it = it->next;
    }
    return false;
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

void ListGraph::AddAdjacency(const int fromNode, const int toNode, const unsigned int value)
{
    // fromNode adjacency
    if (!AdjacencyExists(nodes[fromNode], toNode))
    {
        Adjacency* next = nodes[fromNode];
        Adjacency* newAdjacentTo = new Adjacency(toNode, value, next);
        nodes[fromNode] = newAdjacentTo;
        edgeCount += 1;
    }
    // toNode adjacency
    if (graphType == Undirected)
    {
        if (!AdjacencyExists(nodes[toNode], fromNode))
        {
            Adjacency* next = nodes[toNode];
            Adjacency* newAdjacentTo = new Adjacency(fromNode, value, next);
            nodes[toNode] = newAdjacentTo;
            edgeCount += 1;
        }
    }
}
