#include "MatrixGraph.h"

#include <iomanip>
#include <sstream>

using namespace std;

MatrixGraph::MatrixGraph(int nodeCount, int edgeCount): nodeCount(nodeCount),
                                                            edgeCount(edgeCount)
{
    values = new unsigned int*[nodeCount]();
    for (int i = 0; i < nodeCount; i++)
    {
        values[i] = new unsigned int[edgeCount*2]();
    }
}

MatrixGraph::~MatrixGraph()
{
    for (int i = 0; i < nodeCount; i++)
    {
        delete [] values[i];
        values[i] = nullptr;
    }
    delete [] values;
}

void MatrixGraph::AddEdge(const int edge, const int fromNode, const int toNode, const unsigned int value) const 
{
    values[fromNode][edge] = value;
    values[toNode][edge] = value;
}

std::string MatrixGraph::ToString() const
{
    ostringstream oss;
    oss << "MatrixGraph[" << '\n';
    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < edgeCount*2; j++)
        {
            oss << setw(2) << values[i][j];
        }
        
        oss << '\n';
    }
    oss << ']' << '\n';
    return oss.str(); }
