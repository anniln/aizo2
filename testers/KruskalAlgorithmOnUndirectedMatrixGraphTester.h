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

    std::string TestGraphAlgorithm(const MatrixGraph& graph) const override
    {
        vector<Edge> edges;

        for (int edge = 0; edge < graph.edgeCount; ++edge)
        {
            int fromNode = -1;
            int toNode = -1;
            unsigned int value = 0;

            for (int node = 0; node < graph.nodeCount; ++node)
            {
                if (graph.values.at(node).at(edge) != 0)
                {
                    if (fromNode == -1)
                    {
                        fromNode = node;
                        value = graph.values.at(node).at(edge);
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
                edges.emplace_back(fromNode, toNode, value);
            }
        }

        // Sortowanie krawędzi według wagi
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.value < b.value;
        });

        UnionFind uf(graph.nodeCount);
        vector<Edge> mst;
        unsigned int totalCost = 0;

        for (const auto& edge : edges)
        {
            if (uf.Find(edge.fromNode) != uf.Find(edge.toNode))
            {
                uf.Union(edge.fromNode, edge.toNode);
                mst.push_back(edge);
                totalCost += edge.value;
            }
        }
        
        // Wyświetlanie wyniku
        std::ostringstream oss;
        oss << "Edges in the MST:\n";
        for (const auto& edge : mst)
        {
            oss << "From: " << edge.fromNode << " To: " << edge.toNode << " Weight: " << edge.value << "\n";
        }
        oss << "Total cost of MST (Kruskal): " << totalCost << "\n\n";

        return oss.str();
    }

private:
};
