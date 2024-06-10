#pragma once
#include <sstream>
#include <string>

using namespace std;

struct Edge
{
    int edge;
    int fromNode, toNode;
    unsigned int value;
    Edge* next;

    Edge() : edge(-1), fromNode(0), toNode(0), value(0), next(nullptr) {}
    Edge(int f, int t, unsigned int v) : edge(-1), fromNode(f), toNode(t), value(v), next(nullptr) 
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

        //ostringstream oss;
        //oss << "E[";
        //if (edge != -1)
        //{
        //    oss << "" << edge << ",";
        //}
        //oss << "N:" << fromNode << ",V:" << value << ",N:" << value;
        //oss << "]";
        //return oss.str();
    }

    static string ArrayToString(const Edge* edges)
    {
        ostringstream oss;
        const Edge* it = edges;
        while (it != nullptr)
        {
            oss << it->ToString() << "\n";
            it = it->next;
        }
        return oss.str();
    }
    
    static void AddEdgeToList(Edge*& edges, Edge* edge)
    {
        if (edges == nullptr || edge->value < edges->value)
        {
            edge->next = edges;
            edges = edge;
        }
        else
        {
            Edge* current = edges;
            while (current->next != nullptr && current->next->value < edge->value)
            {
                current = current->next;
            }
            edge->next = current->next;
            current->next = edge;
        }
    }

    static Edge* SortEdges(Edge* edges)
    {
        Edge* sortedEdges = nullptr;
        while (edges != nullptr)
        {
            Edge* next = edges->next;
            Edge::AddEdgeToList(sortedEdges, edges);
            edges = next;
        }
        return sortedEdges;
    }
};

