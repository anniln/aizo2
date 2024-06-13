#pragma once
#include "../models/MatrixGraph.h"
#include <iostream>

#include "GraphShortPathAlgorithmTester.h"

class DijkstryAlgorithmOnDirectedMatrixGraph : public GraphShortPathAlgorithmTester<MatrixGraph>
{
public:
    virtual ~DijkstryAlgorithmOnDirectedMatrixGraph() = default;

    // Funkcja implementująca algorytm Dijkstry
    void TestGraphAlgorithm(const MatrixGraph &graph, int startNode, int endNode) const override
    {
        int nodeCount = graph.nodeCount;
        unsigned int *distances = new unsigned int[nodeCount]; // Tablica przechowująca odległości od wierzchołka startowego
        int *predecessors = new int[nodeCount]; // Tablica przechowująca poprzedników w najkrótszej ścieżce
        bool *sptSet = new bool[nodeCount]; // Tablica przechowująca informacje o tym, czy wierzchołek został już odwiedzony

        // Inicjalizacja
        for (int i = 0; i < nodeCount; i++)
        {
            distances[i] = UINT_MAX; // Ustawienie początkowych odległości na nieskończoność
            sptSet[i] = false; // Żaden wierzchołek jeszcze nie został odwiedzony
            predecessors[i] = -1; // Brak poprzedników dla początkowego wierzchołka
        }

        distances[startNode] = 0; // Odległość od wierzchołka początkowego do samego siebie wynosi zero

        // Algorytm Dijkstry
        for (int count = 0; count < nodeCount - 1; count++)
        {
            int u = MinDistance(distances, sptSet, nodeCount); // Wybór wierzchołka o najmniejszej odległości

            if (u == -1)
                break; // Przerywamy, jeśli nie znaleziono wierzchołka

            sptSet[u] = true; // Oznaczamy wierzchołek jako odwiedzony

            // Iterujemy przez kolumny macierzy incydencji
            for (int v = 0; v < graph.edgeCount; v++)
            {
                if (graph.values[u][v] > 0) // Sprawdzamy czy istnieje krawędź z wierzchołka u do v
                {
                    // int neighborIndex = (graph.values[u][v] > 0) ? 1 : 0; // Indeks wierzchołka sąsiedniego
                    // int neighbor = (graph.values[u][v] > 0) ? graph.values[u][v] - 1 : -graph.values[u][v] - 1; // Numer wierzchołka sąsiedniego
                    // unsigned int weight = abs(graph.values[neighbor][neighborIndex]); // Waga krawędzi
                    
                    unsigned int weight = graph.values[u][v]; // Waga krawędzi
                    const int neighbor = graph.GetToNode(v);
                    if (!sptSet[neighbor] && distances[u] != UINT_MAX && distances[u] + weight < distances[neighbor])
                    {
                        distances[neighbor] = distances[u] + weight; // Aktualizacja odległości do sąsiada
                        predecessors[neighbor] = u; // Zapisanie poprzednika dla aktualnej ścieżki
                    }
                }
            }
        }

        // Wypisywanie wyników
        std::cout << "Total cost (shortest path) from node " << startNode << " to node " << endNode << " is: " << distances[endNode] << "\n";

        std::cout << "Path: ";
        if (distances[endNode] == UINT_MAX)
        {
            std::cout << "No path\n";
        }
        else
        {
            int *path = new int[nodeCount]; // Tablica przechowująca wierzchołki w najkrótszej ścieżce
            int path_index = 0;
            for (int at = endNode; at != -1; at = predecessors[at]) // Iteracja od wierzchołka docelowego do początkowego
            {
                path[path_index++] = at; // Dodawanie wierzchołków do ścieżki
                //std::cout << "predecessor" << at << " " << predecessors[at] << "\n";
            }
            std::reverse(path, path + path_index); // Odwrócenie tablicy, aby ścieżka była w kolejności od wierzchołka początkowego do docelowego
            for (int i = 0; i < path_index; ++i)
            {
                std::cout << path[i] << " "; // Wypisanie ścieżki
            }
            std::cout << "\n";
            delete[] path; // Zwolnienie pamięci zaalokowanej dla tablicy ścieżki
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

        return min_index; // Zwracamy indeks wierzchołka o najmniejszej odległości
    }
  
};