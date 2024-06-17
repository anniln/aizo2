#include "GraphFileReader.h"

#include <fstream>
#include <iostream>

ListGraph* GraphFileReader::ReadListGraph(GraphType graphType, std::string graphFilePath)
{
    std::ifstream file(graphFilePath);
    try
    {
        int edgeCount, nodeCount;
        file >> edgeCount >> nodeCount;
        if (!file.is_open()) {
            std::cerr << "Cannot open file " << graphFilePath << "\n";
            return nullptr;  // Zwraca pusty ListGraph, jeśli nie można otworzyć pliku
        }
        
        ListGraph* graph = new ListGraph(nodeCount, graphType);

        int fromNode, toNode;
        unsigned int value;
        for (int i = 0; i < edgeCount; i++)
        {
            file >> fromNode >> toNode >> value;
            graph->AddAdjacency(fromNode, toNode, value);
        }

        file.close();
        std::cout << "The file was loaded correctly\n";
        return graph;
    }
    catch (...)
    {
        std::cerr << "Can't find input file " << graphFilePath << "\n";
        return nullptr;
    }
}

