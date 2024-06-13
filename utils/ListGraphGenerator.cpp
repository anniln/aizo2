#include <chrono>

#include "GraphGenerator.h"

#include <cstdlib>
#include <iostream>

#include "RandomGenerator.h"
#include "../models/ListGraph.h"

MatrixGraph* GraphGenerator::ListGraphToMatrixGraph(const ListGraph& listGraph)
{
    MatrixGraph* matrixGraph = new MatrixGraph(listGraph.nodeCount, listGraph.edgeCount / 2, listGraph.graphType);
    int edgeIndex = 0;
    for (int i = 0; i < listGraph.nodeCount; ++i)
    {
        Adjacency* adjacency = listGraph.nodes[i];
        while (adjacency != nullptr)
        {
            matrixGraph->AddEdge(edgeIndex, i, adjacency->adjacentTo, adjacency->value);
            edgeIndex++;
            adjacency = adjacency->next;
        }
    }
    return matrixGraph;
}

void GraphGenerator::GenerateSpanningTree(ListGraph& listGraph)
{
    for (int i = 1; i < listGraph.nodeCount; i++)
    {
        listGraph.AddAdjacency(i-1, i, RandomGenerator::random(1, listGraph.nodeCount));
    }
    listGraph.AddAdjacency(listGraph.nodeCount-1, 0, RandomGenerator::random(1, listGraph.nodeCount));
}

int GraphGenerator::CalculateNumberOfEdges(int nodeCount, float fill)
{
    return static_cast<int>(((nodeCount - 1) * nodeCount / 2.0) * fill + (nodeCount % 2 == 0 ? 0 : 1));
}

void GraphGenerator::FillRandomSpanningTreeAdjacency(ListGraph& listGraph, int numberOfEdgesToFill)
{
    for (int i = 0; i < numberOfEdgesToFill; i++)
    {
        int fromNode = -1;
        int toNode = -1;
        do
        {
            fromNode = RandomGenerator::random(0, listGraph.nodeCount-1);
            toNode = RandomGenerator::random(0, listGraph.nodeCount-1);
        } while (fromNode == toNode || listGraph.AdjacencyExists(fromNode, toNode));
        listGraph.AddAdjacency(fromNode, toNode, RandomGenerator::random(1, listGraph.nodeCount));
    }
}

auto GraphGenerator::GenerateListGraphRepresentation(GraphType graphType, int numberOfNodes, float fill) -> ListGraph*
{
    ListGraph* listGraph = new ListGraph(numberOfNodes, graphType);
    GenerateSpanningTree(*listGraph);
    const int numberOfEdgesToFill = CalculateNumberOfEdges(numberOfNodes, fill) - numberOfNodes + 1;
    FillRandomSpanningTreeAdjacency(*listGraph, numberOfEdgesToFill);
    return listGraph;
}
