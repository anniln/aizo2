#pragma once
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Edge
{
    int edge;
    int fromNode, toNode;
    unsigned int value;

    Edge() : edge(-1), fromNode(0), toNode(0), value(0) {}
    Edge(int f, int t, unsigned int v) : edge(-1), fromNode(f), toNode(t), value(v) 
    {
    }

    bool operator<(const Edge& other) const
    {
        return value < other.value;
    }

    string ToString() const
    {
        ostringstream oss;
        oss << "Edge: " << fromNode << " - " << toNode << " Weight: " << value;
        return oss.str();
    }

    static string ArrayToString(const vector<Edge>& edges)
    {
        ostringstream oss;
        for (const auto& edge : edges)
        {
            oss << edge.ToString() << "\n";
        }
        return oss.str();
    }
    
    static void AddEdgeToList(vector<Edge>& edges, const Edge& edge)
    {
        edges.push_back(edge);
        sort(edges.begin(), edges.end());
    }

    static vector<Edge> SortEdges(vector<Edge>& edges)
    {
        vector<Edge> sortedEdges = edges;
        sort(sortedEdges.begin(), sortedEdges.end());
        return sortedEdges;
    }
};

