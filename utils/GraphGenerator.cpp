#include "GraphGenerator.h"

#include <cmath>
#include <cstdlib>

#include "RandomGenerator.h"
#include "../models/ListGraph.h"

auto GraphGenerator::GenerateSpanningTree(MatrixGraph& matrixGraph)
{
    for (int i = 1; i < matrixGraph.nodeCount; i++)
    {
        matrixGraph.AddEdge(i-1, 0, i, RandomGenerator::random(1, matrixGraph.nodeCount));    
    }
    
}


auto GraphGenerator::GenerateMatrixGraphRepresentation(int numberOfNodes, float fill) -> MatrixGraph
{
    MatrixGraph matrixGraph(numberOfNodes, CalculateNumberOfEdges(numberOfNodes, fill) * 2);
    GenerateSpanningTree(matrixGraph);
    
    return matrixGraph;
}



auto GraphGenerator::ConvertListGraphToMatrixGraph(ListGraph& listGraph) -> MatrixGraph
{
    return MatrixGraph(0,0);
}

auto GraphGenerator::ConvertListMatrixToListGraph(MatrixGraph& listGraph) -> ListGraph
{
    return ListGraph();
}

auto GraphGenerator::GenerateSpanningTree(ListGraph& listGraph)
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

auto GraphGenerator::FillRandomSpanningTreeAdjacency(ListGraph& listGraph, int numberOfEdgesToFill)
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



