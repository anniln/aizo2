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

MatrixGraph GraphGenerator::ListGraphToMatrixGraph(const ListGraph& listGraph)
{
    MatrixGraph* matrixGraph = new MatrixGraph(listGraph.nodeCount, listGraph.edgeCount / 2);
    int edgeIndex = 0;
    for (int i = 0; i < listGraph.nodeCount; ++i) {
        Adjacency* adjacency = listGraph.nodes[i];
        while (adjacency != nullptr) {
            matrixGraph->AddEdge(edgeIndex, i, adjacency->adjacentTo, adjacency->value);
            edgeIndex++;
            adjacency = adjacency->next;
        }
    }
    return *matrixGraph;
}

ListGraph GraphGenerator::MatrixGraphToListGraph(const MatrixGraph& matrixGraph)
{
    ListGraph* listGraph = new ListGraph(matrixGraph.nodeCount);
    for (int i = 0; i < matrixGraph.edgeCount*2; i++) {
        int fromNode = -1;
        int toNode = -1;
        unsigned int value = 0;
        for (int j = 0; j < matrixGraph.nodeCount; j++) {
            if (matrixGraph.values[j][i] != 0) {
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
    ListGraph* listGraph = new ListGraph(numberOfNodes);
    GenerateSpanningTree(*listGraph);
    const int numberOfEdgesToFill = CalculateNumberOfEdges(numberOfNodes, fill) - numberOfNodes + 1;
    FillRandomSpanningTreeAdjacency(*listGraph, numberOfEdgesToFill);
    return *listGraph; 
}



