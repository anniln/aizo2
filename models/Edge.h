#pragma once
#include <string>
#include <vector>

using namespace std;

struct Edge
{
    int edge; // dla przyszłego użycia listy krawędzi
    
    int fromNode, toNode;
    unsigned int value;

    Edge();

    Edge(int f, int t, unsigned int v);

    bool operator<(const Edge& other) const;

    string ToString() const;

    static string ArrayToString(const vector<Edge>& edges);

    static void AddEdgeToList(vector<Edge>& edges, const Edge& edge);

    static vector<Edge> SortEdges(vector<Edge>& edges);
};

