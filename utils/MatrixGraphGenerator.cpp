#include "GraphGenerator.h"

#include <cstdlib>
#include <iostream>

#include "RandomGenerator.h"
#include "../models/ListGraph.h"

auto GraphGenerator::GenerateMatrixGraphRepresentation(GraphType graphType, int numberOfNodes, float fill) -> MatrixGraph*
{
    MatrixGraph* matrixGraph = new MatrixGraph(numberOfNodes, CalculateNumberOfEdges(numberOfNodes, fill), graphType);
    GenerateSpanningTree(*matrixGraph);
    FillRandomSpanningTreeAdjacency(*matrixGraph);
    return matrixGraph;
}

void GraphGenerator::FindPotentialEdge(const MatrixGraph& matrixGraph, int& fromNode, int& toNode)
{
    fromNode = RandomGenerator::random(0, matrixGraph.nodeCount - 1);
    do
    {
        toNode = RandomGenerator::random(0, matrixGraph.nodeCount - 1);
    }
    while (fromNode == toNode);
}

void GraphGenerator::FillRandomSpanningTreeAdjacency(const MatrixGraph& matrixGraph)
{
    for (int i = matrixGraph.nodeCount; i < matrixGraph.edgeCount * matrixGraph.edgeMultiplier; i++) 
    {
        int fromNode = -1;
        int toNode = -1;
        do
        {
            FindPotentialEdge(matrixGraph, fromNode, toNode);
        }
        while (EdgeExists(matrixGraph, fromNode, toNode));
        matrixGraph.AddEdge(i, fromNode, toNode, RandomGenerator::random(1, matrixGraph.nodeCount));
    }
}

bool GraphGenerator::EdgeExists(const MatrixGraph& matrixGraph, int fromNode, int toNode)
{
    for (int i = 0; i < matrixGraph.edgeCount * matrixGraph.edgeMultiplier; i++)
    {
        if (matrixGraph.values[fromNode][i] != 0 && matrixGraph.values[toNode][i] != 0)
        {
            return true;
        }
    }
    return false;
}


ListGraph GraphGenerator::MatrixGraphToListGraph(const MatrixGraph& matrixGraph)
{
    ListGraph* listGraph = new ListGraph(matrixGraph.nodeCount);
    for (int i = 0; i < matrixGraph.edgeCount * 2; i++)
    {
        int fromNode = -1;
        int toNode = -1;
        unsigned int value = 0;
        for (int j = 0; j < matrixGraph.nodeCount; j++)
        {
            if (matrixGraph.values[j][i] != 0)
            {
                value = matrixGraph.values[j][i];
                if (fromNode == -1)
                {
                    fromNode = j;
                }
                else
                {
                    toNode = j;
                    break;
                }
            }
        }
        listGraph->AddAdjacency(fromNode, toNode, value);
    }
    return *listGraph;
}

void GraphGenerator::GenerateSpanningTree(const MatrixGraph& matrixGraph)
{
    for (int i = 0; i < matrixGraph.nodeCount; i++)
    {
        if (i == matrixGraph.nodeCount - 1)
        {
            matrixGraph.AddEdge(i, i, 0, RandomGenerator::random(1, matrixGraph.nodeCount));
        }
        else
        {
            matrixGraph.AddEdge(i, i, i + 1, RandomGenerator::random(1, matrixGraph.nodeCount));
        }
    }
}

