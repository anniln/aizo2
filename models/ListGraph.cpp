#include "ListGraph.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Adjacency::Adjacency(int adjacentTo, const unsigned value, Adjacency* next)
    : adjacentTo(adjacentTo), value(value)
{
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
    nodes.resize(nodeCount);
}

bool ListGraph::AdjacencyExists(int fromNode, int toNode) const
{
    return AdjacencyExists(nodes.at(fromNode), toNode); 
}

bool ListGraph::AdjacencyExists(const std::vector<Adjacency>& nodeAdjacencies,int toNode)
{
    for (const auto& adjacency : nodeAdjacencies)
    {
        if (adjacency.adjacentTo == toNode)
        {
            return true;
        }
    }
    return false;
}

string ListGraph::ToString() const
{
    ostringstream oss;
    oss << "ListGraph[" << '\n';
    for (int i = 0; i < nodeCount; ++i)
    {
        oss << i << ": ";
        for (const auto& adjacency : nodes.at(i))
        {
            oss << adjacency.ToString() << " ";
        }
        oss << '\n';
    }
    oss << ']' << '\n';
    return oss.str();
}

void ListGraph::AddAdjacency(const int fromNode, const int toNode, const unsigned int value)
{
    // fromNode adjacency
    if (!AdjacencyExists(nodes.at(fromNode), toNode))
    {
        nodes.at(fromNode).emplace_back(toNode, value);
        edgeCount += 1;
    }
    // toNode adjacency
    if (graphType == Undirected)
    {
        if (!AdjacencyExists(nodes.at(toNode), fromNode))
        {
            nodes.at(toNode).emplace_back(fromNode, value);
            edgeCount += 1;
        }
    }
}

std::vector<Edge> ListGraph::GetEdges() const
{
    std::vector<Edge> edges;
    for (int fromNode = 0; fromNode < nodeCount; ++fromNode)
    {
        for (const auto& adjacency : nodes.at(fromNode))
        {
            // if (graphType == Undirected && fromNode > adjacency.adjacentTo)
            // {
            //     continue;  // Avoid adding duplicate edges in undirected graph
            // }
            edges.emplace_back(fromNode, adjacency.adjacentTo, adjacency.value);
        }
    }
    return edges;
}

