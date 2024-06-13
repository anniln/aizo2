#include "MatrixGraph.h"

#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

MatrixGraph::MatrixGraph(int nodeCount, int edgeCount, GraphType graphType)
    : graphType(graphType), nodeCount(nodeCount), edgeCount(edgeCount), edgeMultiplier(graphType == Undirected ? 2 : 1)
{
    values.resize(nodeCount, vector<int>(edgeCount * edgeMultiplier, 0));
}

void MatrixGraph::AddEdge(const int edge, const int node1, const int node2, const unsigned int value)
{
    values.at(node1).at(edge) = value;
    values.at(node2).at(edge) = graphType == Undirected ? value : (-1) * value;
}

std::string MatrixGraph::ToString() const
{
    ostringstream oss;
    oss << "MatrixGraph[" << '\n';
    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < edgeCount * edgeMultiplier; j++)
        {
            oss << setw(2) << values.at(i).at(j);
        }

        oss << '\n';
    }
    oss << ']' << '\n';
    return oss.str();
}

int MatrixGraph::GetToNode(int edge) const
{
    for (int i = 0; i < nodeCount; i++)
    {
        if (values.at(i).at(edge) < 0)
        {
            return i;
        }
    }
    return -1;
}

int MatrixGraph::GetFromNode(int edge) const
{
    for (int i = 0; i < nodeCount; i++)
    {
        if (values.at(i).at(edge) > 0)
        {
            return i;
        }
    }
    return -1;
}
