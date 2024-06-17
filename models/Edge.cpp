#include "Edge.h"

#include <algorithm>
#include <sstream>

Edge::Edge(): edge(-1), fromNode(0), toNode(0), value(0)
{}

Edge::Edge(int f, int t, unsigned v): edge(-1), fromNode(f), toNode(t), value(v)
{
}

bool Edge::operator<(const Edge& other) const
{
    return value < other.value;
}

string Edge::ToString() const
{
    ostringstream oss;
    oss << "Edge: " << fromNode << " - " << toNode << " Weight: " << value;
    return oss.str();
}

string Edge::ArrayToString(const vector<Edge>& edges)
{
    ostringstream oss;
    for (const auto& edge : edges)
    {
        oss << edge.ToString() << "\n";
    }
    return oss.str();
}

void Edge::AddEdgeToList(vector<Edge>& edges, const Edge& edge)
{
    edges.push_back(edge);
    sort(edges.begin(), edges.end());
}

vector<Edge> Edge::SortEdges(vector<Edge>& edges)
{
    vector<Edge> sortedEdges = edges;
    sort(sortedEdges.begin(), sortedEdges.end());
    return sortedEdges;
}
