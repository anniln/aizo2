#pragma once
#include "../models/ListGraph.h"
#include "../models/MatrixGraph.h"

class GraphGenerator
{
public:
    static auto GenerateListGraphRepresentation(int numberOfNodes, float fill) -> ListGraph;
    static auto GenerateMatrixGraphRepresentation(int numberOfNodes, float fill) -> MatrixGraph;

private:
    static auto GenerateSpanningTree(ListGraph& listGraph);
    static auto GenerateSpanningTree(MatrixGraph& listGraph);
    static int CalculateNumberOfEdges(int nodeCount, float fill);
    static auto FillRandomSpanningTreeAdjacency(ListGraph& listGraph, int numberOfEdgesToFill);
    static auto ConvertListGraphToMatrixGraph(ListGraph& listGraph) -> MatrixGraph;
    static auto ConvertListMatrixToListGraph(MatrixGraph& listGraph) -> ListGraph;
};
