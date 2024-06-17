#pragma once
#include <string>
#include "../models/ListGraph.h"

class GraphFileReader
{
public:
    static ListGraph* ReadListGraph(GraphType graphType, std::string graphFilePath);
};
