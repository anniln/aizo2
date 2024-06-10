#include "MatrixGraph.h"

#include <iomanip>
#include <sstream>

using namespace std;

MatrixGraph::MatrixGraph(int nodeCount, int edgeCount, GraphType graphType)
    : graphType(graphType), nodeCount(nodeCount), edgeCount(edgeCount), edgeMultiplier(graphType == Undirected ? 2 : 1)
{
    values = new int*[nodeCount]();
    for (int i = 0; i < nodeCount; i++)
    {
        values[i] = new int[edgeCount * edgeMultiplier]();
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

void MatrixGraph::AddEdge(const int edge, const int node1, const int node2, const unsigned int value) const
{
    values[node1][edge] = value;
    values[node2][edge] = graphType == Undirected ? value : (-1) * value;
}

std::string MatrixGraph::ToString() const
{
    ostringstream oss;
    oss << "MatrixGraph[" << '\n';
    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < edgeCount * edgeMultiplier; j++)
        {
            oss << setw(2) << values[i][j];
        }

        oss << '\n';
    }
    oss << ']' << '\n';
    return oss.str();
}
