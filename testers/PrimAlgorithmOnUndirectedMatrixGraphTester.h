#pragma once
#include "GraphMstAlgorithmTester.h"
#include "../models/MatrixGraph.h"
#include <iostream>
#include <sstream>

class PrimAlgorithmOnUndirectedMatrixGraphTester final : public GraphMstAlgorithmTester<MatrixGraph>
{
public:
    // Funkcja pomocnicza do znalezienia minimalnego klucza
    int MinKey(unsigned int key[], bool mstSet[], int V) const
    {
        unsigned int min = UINT_MAX;
        int min_index = -1;

        for (int v = 0; v < V; v++)
        {
            if (mstSet[v] == false && key[v] < min)
            {
                min = key[v];
                min_index = v;
            }
        }

        return min_index;
    }

    // Algorytm Prima
    std::string TestGraphAlgorithm(const MatrixGraph& graph, bool outputResults) const override {
        unsigned int* key = new unsigned int[graph.nodeCount]; // tablica przechowująca minimalne wagi krawędzi
        int* parent = new int[graph.nodeCount]; // tablica przechowująca rodziców wierzchołków w MST
        bool* inMST = new bool[graph.nodeCount]; // tablica przechowująca informacje, czy wierzchołek jest w MST

        int start = 0; // wierzchołek startowy to 0

        for (int i = 0; i < graph.nodeCount; ++i)
        {
            key[i] = UINT_MAX; // inicjalizacja kluczy jako nieskończoność
            parent[i] = -1; // inicjalizacja rodziców jako brak (czyli -1)
            inMST[i] = false; // inicjalizacja stanu MST jako false (czyli nie jest w MST)
        }

        key[start] = 0; // ustawienie klucza wierzchołka startowego na 0, aby był wybrany jako pierwszy

        unsigned int totalCost = 0; // zmienna przechowująca całkowity koszt drzewa MST

        for (int count = 0; count < graph.nodeCount - 1; ++count)
        {
            // iteracja po wszystkich wierzchołkach, aby skonstruować MST
            int u = MinKey(key, inMST, graph.nodeCount);
            // znalezienie wierzchołka o minimalnym kluczu, który nie jest jeszcze w MST
            inMST[u] = true; // dodanie wierzchołka do MST

            for (int e = 0; e < graph.edgeCount; ++e)
            {
                // iteracja po wszystkich krawędziach
                if (graph.values[u][e] != 0)
                {
                    // jeśli istnieje krawędź
                    int v = -1;
                    for (int i = 0; i < graph.nodeCount; ++i)
                    {
                        // znalezienie drugiego końca krawędzi
                        if (i != u && graph.values[i][e] != 0)
                        {
                            v = i;
                            break;
                        }
                    }

                    if (v != -1 && !inMST[v] && graph.values[u][e] < key[v])
                    {
                        // jeśli drugi koniec nie jest w MST i waga krawędzi jest mniejsza niż obecny klucz
                        key[v] = graph.values[u][e]; // zaktualizowanie klucza
                        parent[v] = u; // zaktualizowanie rodzica
                    }
                }
            }
        }

        // Wyświetlanie MST i zliczanie całkowitego kosztu
        std::ostringstream oss;
        for (int i = 1; i < graph.nodeCount; ++i)
        {
            // iteracja po wszystkich wierzchołkach, aby wyświetlić MST
            if (parent[i] != -1)
            {
                // jeśli wierzchołek ma rodzica (jest w MST)
                oss << "Edge: " << parent[i] << " - " << i << " Weight: " << key[i] << "\n";
                // wyświetlenie krawędzi i jej wagi
                totalCost += key[i]; // dodanie wagi krawędzi do całkowitego kosztu
            }
        }

        // Wyświetlanie całkowitego kosztu drzewa MST
        oss << "Total cost of MST (Prim): " << totalCost << "\n\n";

        delete[] key;
        delete[] parent;
        delete[] inMST;

        if (outputResults)
            std::cout<< oss.str();

        return oss.str();
    }
};
