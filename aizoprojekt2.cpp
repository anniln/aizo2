#include <iomanip>
#include <iostream>

#include "Simulation.h"
#include "testers/BellmanFordAlgorithmOnDirectedListGraphTester.h"
#include "testers/BellmanFordAlgorithmOnDirectedMatrixGraph.h"
#include "testers/DijkstryAlgorithmOnDirectedListGraph.h"
#include "testers/DijkstryAlgorithmOnDirectedMatrixGraph.h"
#include "testers/KruskalAlgorithmOnUndirectedListGraphTester.h"
#include "testers/KruskalAlgorithmOnUndirectedMatrixGraphTester.h"
#include "testers/PrimAlgorithmOnUndirectedMatrixGraphTester.h"
#include "testers/PrimAlgorithmOnUndirectedListGraphTester.h"
#include "utils/GraphFileReader.h"

#include "utils/GraphGenerator.h"

using namespace std;

enum class GraphRepresentation
{
    Matrix,
    List
};

std::string GetGraphRepresentationName(GraphRepresentation graphRepresentation)
{
    switch (graphRepresentation)
    {
    case GraphRepresentation::Matrix: return "Matrix";
    case GraphRepresentation::List: return "List";
    }
    return "";
}

enum class Problem
{
    Mst,
    ShortPath
};

std::string GetProblemName(Problem problem)
{
    switch (problem)
    {
    case Problem::Mst: return "MST";
    case Problem::ShortPath: return "Shortest Path";
    }
    return "";
}

template <typename T>
T* FreeGraph(T* graph)
{
    if (graph != nullptr)
    {
        delete graph;
    }
    return nullptr;
}

int main1(int argc, char* argv[])
{
    Simulation simulation;
    simulation.Execute();
    return 1;
}


int main2(int argc, char* argv[])
{
    auto graph1 = GraphGenerator::GenerateListGraphRepresentation(Undirected, 512, 0.99);
    // auto graph1 = new ListGraph(5, Undirected);
    // graph1->AddAdjacency(0, 1, 1);
    // graph1->AddAdjacency(2, 4, 2);
    // graph1->AddAdjacency(0, 2, 3);
    // graph1->AddAdjacency(1, 2, 3);
    // graph1->AddAdjacency(2, 3, 4);
    // graph1->AddAdjacency(3, 4, 5);
    // graph1->AddAdjacency(1, 3, 6);

    cout << graph1->ToString();
    KruskalAlgorithmOnUndirectedListGraphTester test1;
    auto graph2 = GraphGenerator::ListGraphToMatrixGraph(*graph1);
    test1.TestGraphAlgorithm(*graph1, true);
    delete graph1;

    cout << graph2->ToString();
    KruskalAlgorithmOnUndirectedMatrixGraphTester test2;
    test2.TestGraphAlgorithm(*graph2, true);
    delete graph2;

    return 1;
}

bool ValidateRequiredGraphs(void* graph1, void* graph2)
{
    if (graph1 == nullptr || graph2 == nullptr)
    {
        cout << "Missing tester required graphs. Initialize them random or read from file";
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    try
    {
        string testOutput = R"(C:\Temp\GraphTest)";
        string graphFilePath = testOutput + R"(\graph.txt)";

        auto graphRepresentation = GraphRepresentation::List;
        auto graphType = GraphType::Directed;
        Problem problemToTest;

        MatrixGraph* directedMatrixGraph = nullptr;
        MatrixGraph* undirectedMatrixGraph = nullptr;
        ListGraph* directedListGraph = nullptr;
        ListGraph* undirectedListGraph = nullptr;


        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        do
        {
            cout << "\n\n";
            cout << "Author: Anna Ilnicka-Wandycz (CZW/N 11:15)\n";
            cout << "Ctrl+C to exit program\n";

            string representation;
            cout << "Graph representation ('list' = ('d')efault or '(m)atrix'): ";
            cin >> representation;
            graphRepresentation = (representation == "m" || representation == "matrix")
                                      ? GraphRepresentation::Matrix
                                      : GraphRepresentation::List;

            string type;
            cout << "Graph type ('directed' = ('d')efault or '(u)ndirected'): ";
            cin >> type;
            graphType = (type == "u" || type == "undirected") ? GraphType::Undirected : GraphType::Directed;

            int numberOfNodes = 0;

            float fill = 0.0;
            cout << "Fill value 0.0 > float < 1.0 ((d)efault = 0.5): ";
            cin >> fill;
            if (std::cin.fail())
            {
                std::cout << "Cannot read fill number. Presume 0.5" << '\n';
                fill = 0.5f;
                std::cin.clear();
                std::cin.ignore();
            }

            string problem;
            cout << "Problem to test ('mst' = ('d')efault or 'sp' ShortestPath): ";
            cin >> problem;
            problemToTest = problem == "sp" ? Problem::ShortPath : Problem::Mst;

            string option = "9";
            do
            {
                cout << "\n\n";
                cout << "==================================================================================\n";
                cout << "Menu for graph: "
                    << GetGraphRepresentationName(graphRepresentation)
                    << ", GraphType: " << (graphType == GraphType::Directed ? "Directed" : "Undirected")
                    << ", Number of Nodes: " << numberOfNodes
                    << ", Fill value: " << std::fixed << std::setprecision(2) << fill
                    << ", problem: " << GetProblemName(problemToTest)
                    << "\n";
                cout << "'1' - Read data from file \n";
                cout << "'2' - Generate random graphs \n";
                cout << "'3' - Print graphs \n";
                cout << "'4' - Algorithm " << (problemToTest == Problem::Mst ? "Prim" : "Dijkstra") << "\n";
                cout << "'5' - Algorithm " << (problemToTest == Problem::Mst ? "Kruskal" : "Ford-Bellmann") << "\n";
                cout << '\n';
                cout << "'7' - Simulation - Output be written to C:\\Temp\\GraphTest" << "\n";
                cout << "'9' - Back to previous menu" << "\n";
                cin >> option;

                if (option == "1")
                {
                    std::string filepath;
                    cout << "File path (use " << graphFilePath << " as (d)efault): ";
                    cin >>  filepath;
                    if (filepath != "d")
                    {
                        graphFilePath = filepath;
                    }

                    if (graphType == GraphType::Directed)
                    {
                        directedListGraph = FreeGraph<ListGraph>(directedListGraph);
                        directedMatrixGraph = FreeGraph<MatrixGraph>(directedMatrixGraph);
                        directedListGraph = GraphFileReader::ReadListGraph(graphType, graphFilePath);
                        if (directedListGraph != nullptr)
                        {
                            directedMatrixGraph = GraphGenerator::ListGraphToMatrixGraph(*directedListGraph);
                            numberOfNodes = directedListGraph->nodeCount;
                        }
                    }
                    else
                    {
                        undirectedListGraph = FreeGraph<ListGraph>(undirectedListGraph);
                        undirectedMatrixGraph = FreeGraph<MatrixGraph>(undirectedMatrixGraph);
                        undirectedListGraph = GraphFileReader::ReadListGraph(graphType, graphFilePath);
                        if (undirectedListGraph != nullptr)
                        {
                            undirectedMatrixGraph = GraphGenerator::ListGraphToMatrixGraph(*undirectedListGraph);
                            numberOfNodes = undirectedListGraph->nodeCount;
                        }
                    }
                }
                else if (option == "2")
                {
                    cout << "Number of nodes: ";
                    cin >> numberOfNodes;
                    if (std::cin.fail())
                    {
                        std::cout << "Cannot read node number. Presume 10." << '\n';
                        numberOfNodes = 10;
                        std::cin.clear();
                        std::cin.ignore();
                    }
                    
                    if (graphType == GraphType::Directed)
                    {
                        directedListGraph = FreeGraph<ListGraph>(directedListGraph);
                        directedMatrixGraph = FreeGraph<MatrixGraph>(directedMatrixGraph);
                        directedListGraph = GraphGenerator::GenerateListGraphRepresentation(
                            graphType, numberOfNodes, fill);
                        directedMatrixGraph = GraphGenerator::ListGraphToMatrixGraph(*directedListGraph);
                    }
                    else
                    {
                        undirectedListGraph = FreeGraph<ListGraph>(undirectedListGraph);
                        undirectedMatrixGraph = FreeGraph<MatrixGraph>(undirectedMatrixGraph);
                        undirectedListGraph = GraphGenerator::GenerateListGraphRepresentation(
                            graphType, numberOfNodes, fill);
                        undirectedMatrixGraph = GraphGenerator::ListGraphToMatrixGraph(*undirectedListGraph);
                    }
                }
                else if (option == "3")
                {
                    if (graphType == GraphType::Directed)
                    {
                        if (directedListGraph != nullptr) cout << directedListGraph->ToString() << '\n';
                        if (directedMatrixGraph != nullptr) cout << directedMatrixGraph->ToString() << '\n';
                    }
                    else
                    {
                        if (undirectedListGraph != nullptr) cout << undirectedListGraph->ToString() << '\n';
                        if (undirectedMatrixGraph != nullptr) cout << undirectedMatrixGraph->ToString() << '\n';
                    }
                }
                else if (option == "4")
                {
                    if (problemToTest == Problem::Mst)
                    {
                        cout << "\nList\n";
                        PrimAlgorithmOnUndirectedListGraphTester tester1;
                        tester1.TestGraphAlgorithm(*undirectedListGraph, true);
                        cout << "\nMatrix\n";
                        PrimAlgorithmOnUndirectedMatrixGraphTester tester2;
                        tester2.TestGraphAlgorithm(*undirectedMatrixGraph, true);
                    }
                    else // Dijkstra
                    {
                        int startNode, endNode;
                        cout << "Start Node: ";
                        cin >> startNode;
                        cout << ", End Node: ";
                        cin >> endNode;

                        cout << "\nList\n";
                        DijkstryAlgorithmOnDirectedListGraph tester1;
                        tester1.TestGraphAlgorithm(*directedListGraph, startNode, endNode, true);
                        cout << "\nMatrix\n";
                        DijkstryAlgorithmOnDirectedMatrixGraph tester2;
                        tester2.TestGraphAlgorithm(*directedMatrixGraph, startNode, endNode, true);
                    }
                }
                else if (option == "5")
                {
                    if (problemToTest == Problem::Mst)
                    {
                        cout << "\nList\n";
                        KruskalAlgorithmOnUndirectedListGraphTester tester1;
                        tester1.TestGraphAlgorithm(*undirectedListGraph, true);
                        cout << "\nMatrix\n";
                        KruskalAlgorithmOnUndirectedMatrixGraphTester tester2;
                        tester2.TestGraphAlgorithm(*undirectedMatrixGraph, true);
                    }
                    else // Ford-Bellmann
                    {
                        int startNode, endNode;
                        cout << "Start Node: ";
                        cin >> startNode;
                        cout << ", End Node: ";
                        cin >> endNode;

                        cout << "\nList\n";
                        BellmanFordAlgorithmOnDirectedListGraphTester tester1;
                        tester1.TestGraphAlgorithm(*directedListGraph, startNode, endNode, true);
                        cout << "\nMatrix\n";
                        BellmanFordAlgorithmOnDirectedMatrixGraphTester tester2;
                        tester2.TestGraphAlgorithm(*directedMatrixGraph, startNode, endNode, true);
                    }
                }
                else if (option == "7")
                {
                    Simulation simulation;
                    simulation.Execute();
                }
            }
            while (option != "9");

            directedListGraph = FreeGraph<ListGraph>(directedListGraph);
            undirectedListGraph = FreeGraph<ListGraph>(undirectedListGraph);
            directedMatrixGraph = FreeGraph<MatrixGraph>(directedMatrixGraph);
            undirectedMatrixGraph = FreeGraph<MatrixGraph>(undirectedMatrixGraph);
        }
        while (true);
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught exception: " << e.what() << '\n';
    }

    return 0;
}
