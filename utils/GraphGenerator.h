﻿#pragma once
#include "../models/ListGraph.h"
#include "../models/MatrixGraph.h"

class GraphGenerator
{
public:
    static auto GenerateListGraphRepresentation(int numberOfNodes, float fill) -> ListGraph*;
    static auto GenerateMatrixGraphRepresentation(int numberOfNodes, float fill) -> MatrixGraph*;
    static void FindPotentialEdge(MatrixGraph& matrixGraph, int& fromNode, int& toNode);

    static auto ListGraphToMatrixGraph(const ListGraph& listGraph) -> MatrixGraph;
    static auto MatrixGraphToListGraph(const MatrixGraph& matrixGraph) -> ListGraph;

private:
    static int CalculateNumberOfEdges(int nodeCount, float fill);
    
    static void GenerateSpanningTree(ListGraph& listGraph);
    static void FillRandomSpanningTreeAdjacency(ListGraph& listGraph, int numberOfEdgesToFill);
    
    static void GenerateSpanningTree(MatrixGraph& matrixGraph);
    static bool EdgeExists(const MatrixGraph& matrixGraph, int fromNode, int toNode);
    static void FillRandomSpanningTreeAdjacency(MatrixGraph& matrixGraph);
};
