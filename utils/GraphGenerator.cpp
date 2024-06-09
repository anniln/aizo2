#include "GraphGenerator.h"

#include <cmath>
#include <cstdlib>

#include "RandomGenerator.h"
#include "../models/ListGraph.h"

auto GraphGenerator::GenerateMatrixGraphRepresentation(int numberOfNodes, float fill) -> MatrixGraph
{
    MatrixGraph matrixGraph(numberOfNodes, CalculateNumberOfEdges(numberOfNodes, fill));
    GenerateSpanningTree(matrixGraph);
    FillRandomSpanningTreeAdjacency(matrixGraph);
    return matrixGraph;
}

void GraphGenerator::FillRandomSpanningTreeAdjacency(MatrixGraph& matrixGraph)
{
    for (int i = matrixGraph.nodeCount-1; i < matrixGraph.edgeCount*2; i++)
    {
        int fromNode = RandomGenerator::random(0, matrixGraph.nodeCount-1);
        int toNode;
        do {
            toNode = RandomGenerator::random(0, matrixGraph.nodeCount-1);
        } while(fromNode == toNode);
        matrixGraph.AddEdge(i, fromNode, toNode, RandomGenerator::random(1, matrixGraph.nodeCount));
        
    }
}

void GraphGenerator::GenerateSpanningTree(MatrixGraph& matrixGraph)
{
    for (int i = 1; i < matrixGraph.nodeCount; i++)
    {
        matrixGraph.AddEdge(i-1, 0, i, RandomGenerator::random(1, matrixGraph.nodeCount));    
    }
    
}


void GraphGenerator::GenerateSpanningTree(ListGraph& listGraph)
{
    for(int i = 1; i < listGraph.nodeCount; i++)
    {
        listGraph.AddAdjacency(0, i, RandomGenerator::random(1, listGraph.nodeCount));
    }
}

int GraphGenerator::CalculateNumberOfEdges(int nodeCount, float fill)
{
    return static_cast<int>(((nodeCount - 1) * nodeCount / 2.0) * fill);
}

void GraphGenerator::FillRandomSpanningTreeAdjacency(ListGraph& listGraph, int numberOfEdgesToFill)
{
    for (int i = 1; i <= numberOfEdgesToFill; i++)
    {
        listGraph.AddAdjacency(i, i+1, RandomGenerator::random(1, listGraph.nodeCount));
    }
}

auto GraphGenerator::GenerateListGraphRepresentation(int numberOfNodes, float fill) -> ListGraph
{
    ListGraph listGraph;
    listGraph.nodeCount = numberOfNodes;
    // listGraph.nodes = new Adjacency*[numberOfNodes]();
    Adjacency** nodes = new Adjacency*[numberOfNodes]();
    listGraph.nodes = nodes;
    GenerateSpanningTree(listGraph);
    const int numberOfEdgesToFill = CalculateNumberOfEdges(listGraph.nodeCount, fill) - numberOfNodes + 1;
    FillRandomSpanningTreeAdjacency(listGraph, numberOfEdgesToFill);
    return listGraph; 
}



