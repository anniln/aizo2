#pragma once
#include "../models/ListGraph.h"
#include <iostream>

#include "GraphShortPathAlgorithmTester.h"

class DijkstryAlgorithmOnDirectedListGraph: public GraphShortPathAlgorithmTester<ListGraph>
{
public:
    virtual ~DijkstryAlgorithmOnDirectedListGraph() = default;
    
    // Funkcja implementująca algorytm Dijkstry
    void TestGraphAlgorithm(const ListGraph& graph, int startNode, int endNode) const override
    {
        int nodeCount = graph.nodeCount;
        unsigned int* distances = new unsigned int[nodeCount];
        int* predecessors = new int[nodeCount];
        bool* sptSet = new bool[nodeCount];

        // Inicjalizacja
        for (int i = 0; i < nodeCount; i++)
        {
            distances[i] = UINT_MAX;
            sptSet[i] = false;
            predecessors[i] = -1;
        }

        distances[startNode] = 0;

        // Algorytm Dijkstry
        for (int count = 0; count < nodeCount - 1; count++)
        {
            int u = MinDistance(distances, sptSet, nodeCount);

            if (u == -1) break; // Przerywamy, jeśli nie znaleziono wierzchołka

            sptSet[u] = true;

            Adjacency* neighbor = graph.nodes[u];
            while (neighbor != nullptr)
            {
                int v = neighbor->adjacentTo;
                unsigned int weight = neighbor->value;

                if (!sptSet[v] && distances[u] != UINT_MAX && distances[u] + weight < distances[v])
                {
                    distances[v] = distances[u] + weight;
                    predecessors[v] = u;
                }
                neighbor = neighbor->next;
            }
        }

        // Wypisywanie wyników
        std::cout << "Total cost (shortest path) from node " << startNode << " to node " << endNode << " is: " << distances[
            endNode] << "\n";

        std::cout << "Path: ";
        if (distances[endNode] == UINT_MAX)
        {
            std::cout << "No path\n";
        }
        else
        {
            int* path = new int[nodeCount];
            int path_index = 0;
            for (int at = endNode; at != -1; at = predecessors[at])
            {
                path[path_index++] = at;
            }
            std::reverse(path, path + path_index);
            for (int i = 0; i < path_index; ++i)
            {
                std::cout << path[i] << " ";
            }
            std::cout << "\n";
            delete[] path;
        }

        // Zwolnienie pamięci
        delete[] distances;
        delete[] predecessors;
        delete[] sptSet;
    }

private:
    // Funkcja pomocnicza do znalezienia minimalnej wartości w tablicy
    int MinDistance(unsigned int dist[], bool sptSet[], int nodeCount) const 
    {
        unsigned int min = UINT_MAX;
        int min_index = -1;

        for (int v = 0; v < nodeCount; v++)
            if (!sptSet[v] && dist[v] <= min)
            {
                min = dist[v];
                min_index = v;
            }

        return min_index;
    }

};
