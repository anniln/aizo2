#pragma once
#include <iostream>
#include "GraphMstAlgorithmTester.h"
#include "KruskalAlgorithmOnUndirectedListGraphTester.h"
#include "../models/MatrixGraph.h"

using namespace std;

class KruskalAlgorithmOnUndirectedMatrixGraphTester : public GraphMstAlgorithmTester<MatrixGraph>
{
public:
    virtual ~KruskalAlgorithmOnUndirectedMatrixGraphTester() = default;

    void TestGraphAlgorithm(const MatrixGraph& graph) const override
    {
        int edgeCount = 0;
        Edge* edges = new Edge[graph.edgeCount];

        for (int edge = 0; edge < graph.edgeCount; ++edge)
        {
            int fromNode = -1;
            int toNode = -1;
            unsigned int value = 0;

            for (int node = 0; node < graph.nodeCount; ++node)
            {
                if (graph.values[node][edge] != 0)
                {
                    if (fromNode == -1)
                    {
                        fromNode = node;
                        value = graph.values[node][edge];
                    }
                    else
                    {
                        toNode = node;
                        break;
                    }
                }
            }

            if (fromNode != -1 && toNode != -1)
            {
                edges[edgeCount++] = Edge(fromNode, toNode, value);
            }
        }

        // Sortowanie krawędzi według wagi
        SortEdges(edges, edgeCount);

        UnionFind uf(graph.nodeCount);
        Edge* mst = new Edge[graph.nodeCount - 1];
        int mstEdgeCount = 0;
        unsigned int totalCost = 0;

        for (int i = 0; i < edgeCount; ++i)
        {
            if (uf.Find(edges[i].fromNode) != uf.Find(edges[i].toNode))
            {
                uf.Union(edges[i].fromNode, edges[i].toNode);
                mst[mstEdgeCount++] = edges[i];
                totalCost += edges[i].value;
            }
        }

        // Wyświetlanie wyniku
        cout << "Edges in the MST:\n";
        for (int i = 0; i < mstEdgeCount; ++i)
        {
            cout << "From: " << mst[i].fromNode << " To: " << mst[i].toNode << " Weight: " << mst[i].value << "\n";
        }
        cout << "Total cost of MST (Kruskal): " << totalCost << "\n\n";

        delete[] edges;
        delete[] mst;
    }

private:
    void SortEdges(Edge* edges, int count) const
    {
        for (int i = 0; i < count - 1; ++i)
        {
            for (int j = 0; j < count - i - 1; ++j)
            {
                if (edges[j].value > edges[j + 1].value)
                {
                    Swap(edges[j], edges[j + 1]);
                }
            }
        }
    }

    void Swap(Edge& a, Edge& b) const
    {
        Edge temp = a;
        a = b;
        b = temp;
    }
};
