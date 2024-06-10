#pragma once
#include "GraphMstAlgorithmTester.h"
#include "../models/ListGraph.h"
#include <iostream>

class PrimAlgorithmOnUndirectedListGraphTester final : GraphMstAlgorithmTester<ListGraph>
{
public:
    // Funkcja pomocnicza do znalezienia minimalnego klucza
    int MinKey(unsigned int key[], bool mstSet[], int V) {
        unsigned int min = UINT_MAX;
        int min_index = -1;

        for (int v = 0; v < V; v++) {
            if (mstSet[v] == false && key[v] < min) {
                min = key[v];
                min_index = v;
            }
        }
        return min_index;
    }

    //Algorytm Prima dla listy
    void TestGraphAlgorithm(const ListGraph& graph) override {
        // Wierzchołek startowy z góry założony
        int startNode = 0;
        // Tablica do przechowywania minimalnych wag krawędzi
        unsigned int* key = new unsigned int[graph.nodeCount];
        // Tablica do przechowywania rodziców (poprzedników) w MST
        int* parent = new int[graph.nodeCount];
        // Tablica do śledzenia, czy wierzchołek jest już w MST
        bool* inMST = new bool[graph.nodeCount];
        
        // Inicjalizacja tablic: ustawienie kluczy na "nieskończoność", rodziców na -1, a MST na false
        for (int i = 0; i < graph.nodeCount; ++i) {
            key[i] = UINT_MAX;  // Nieskończoność
            parent[i] = -1;     // Brak rodzica
            inMST[i] = false;   // Nie jest jeszcze w MST
        }
        key[startNode] = 0; // Klucz wierzchołka startowego ustawiony na 0

        unsigned int totalCost = 0; // Całkowity koszt drzewa MST

        // Iterowanie przez wszystkie wierzchołki, aby zbudować MST
        for (int count = 0; count < graph.nodeCount; ++count) {
            // Wybierz wierzchołek z minimalnym kluczem, który nie jest jeszcze w MST
            int u = MinKey(key, inMST, graph.nodeCount);
            inMST[u] = true; // Dodaj wybrany wierzchołek do MST

            // Przejrzyj wszystkie sąsiadujące wierzchołki wybranego wierzchołka
            Adjacency* adj = graph.nodes[u];
            while (adj != nullptr) {
                int v = adj->adjacentTo; // Wierzchołek sąsiadujący
                unsigned int weight = adj->value; // Waga krawędzi

                // Jeśli wierzchołek v nie jest jeszcze w MST i waga krawędzi u-v jest mniejsza niż obecny klucz v
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight; // Zaktualizuj klucz dla v
                    parent[v] = u;   // Ustaw u jako rodzica v
                }
                adj = adj->next; // Przejdź do następnego sąsiada
            }
        }

        // Wyświetlanie MST
        for (int i = 1; i < graph.nodeCount; ++i) {
            if (parent[i] != -1) {
                std::cout << "Edge: " << parent[i] << " - " << i << " Weight: " << key[i] << "\n";
                totalCost += key[i]; // Dodawanie wagi krawędzi do całkowitego kosztu
            }
        }

        // Wyświetlanie całkowitego kosztu drzewa MST
        std::cout << "Total cost of MST (Prim): " << totalCost << "\n\n";
        
        // Zwolnienie zaalokowanej pamięci
        delete[] key;
        delete[] parent;
        delete[] inMST;
    }
    
};
