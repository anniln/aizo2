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

template <typename T> T* FreeGraph(T* graph)
{
    if (graph != nullptr)
    {
        delete graph;
    }
    return nullptr;
}

int main(int argc, char* argv[])
{
    Simulation simulation;
    simulation.Execute();
    return 0;
}

int main2(int argc, char* argv[])
{
    try
    {
        string testOutput = R"(C:\Temp\SortTest)";

        auto graphRepresentation = GraphRepresentation::List;
        auto graphType = GraphType::Directed;
        Problem problemToTest;

        MatrixGraph* directedMatrixGraph = nullptr;
        MatrixGraph* undirectedMatrixGraph = nullptr;
        ListGraph* directedListGraph = nullptr;
        ListGraph* undirectedListGraph = nullptr;
        do
        {
            cout << "\n\n";
            cout << "Author: Anna Ilnicka-Wandycz (CZW/N 11:15)\n";
            cout << "Ctrl+C to exit program\n";

            string representation;
            cout << "Graph representation ('list' = ('d')efault or '(m)atrix'): ";
            cin >> representation;
            graphRepresentation = (representation == "m" || representation == "matrix") ? GraphRepresentation::Matrix : GraphRepresentation::List;

            string type;
            cout << "Graph type ('directed' = ('d')efault or '(u)ndirected'): ";
            cin >> type;
            graphType = (representation == "u" || representation == "undirected") ? GraphType::Undirected : GraphType::Directed;

            int numberOfNodes = 0;
            cout << "Number of nodes: ";
            cin >> numberOfNodes;
            if (std::cin.fail()) {
                std::cout << "Cannot read node number. Presume 10." << '\n';
                numberOfNodes = 10;
            }
            
            float  fill = 0.0;
            cout << "Fill value 0 > float < 1: ";
            cin >> fill;
            if (std::cin.fail()) {
                std::cout << "Cannot read fill number. Presume 0.5" << '\n';
                fill = 0.5f;
            }
            
            string problem;
            cout << "Problem to test ('mst' = ('d')efault or 'sp' ShortestPath): ";
            cin >> problem;
            problemToTest = problem == "sp" ? Problem::ShortPath : Problem::Mst;

            string option = "9";
            do
            {
                cout << "\n\n";
                cout << "Menu for graph: "
                    << GetGraphRepresentationName(graphRepresentation)
                    << ", GraphType: " << (graphType == GraphType::Directed ? "Directed" : "Undirected") 
                    << ", Number of Nodes: " << numberOfNodes
                    << ", Fill value: " << std::fixed << std::setprecision(2) << fill
                    << ", problem: " << GetProblemName(problemToTest)
                << "\n";
                cout << "'0' - Read data from file \n";
                cout << "'1' - Generate random graph \n";
                cout << "'2' - Print graph \n";
                cout << "'3' - Algorithm " << (problemToTest == Problem::Mst ? "Prim" : "Dijkstra") << "\n";
                cout << "'4' - Algorithm " << (problemToTest == Problem::Mst ? "Kruskal" : "Ford-Bellmann") << "\n";
                cout << '\n';
                cout << "'7' - Simulation - Output be written to C:\\Temp\\GraphTest" << "\n";
                cout << "'9' - Back to previous menu" << "\n";
                cin >> option;
                
                if (option == "0")
                {
                    
                }
                else if (option == "1")
                    {
                        if (graphType == GraphType::Directed)
                        {
                            directedListGraph = FreeGraph<ListGraph>(directedListGraph);
                            directedMatrixGraph = FreeGraph<MatrixGraph>(directedMatrixGraph);
                            directedListGraph = GraphGenerator::GenerateListGraphRepresentation(graphType, numberOfNodes, fill);
                            directedMatrixGraph = GraphGenerator::ListGraphToMatrixGraph(*directedListGraph);
                        }
                        else
                        {
                            undirectedListGraph = FreeGraph<ListGraph>(undirectedListGraph);
                            undirectedMatrixGraph = FreeGraph<MatrixGraph>(undirectedMatrixGraph);
                            undirectedListGraph = GraphGenerator::GenerateListGraphRepresentation(graphType, numberOfNodes, fill);
                            undirectedMatrixGraph = GraphGenerator::ListGraphToMatrixGraph(*undirectedListGraph);
                        }
                    }
                else if ( option == "2")
                    {
                        if (graphType == GraphType::Directed)
                        {                        
                            if (directedListGraph != nullptr)  cout << directedListGraph->ToString() << '\n';
                            if (directedMatrixGraph != nullptr)  cout << directedMatrixGraph->ToString() << '\n';
                        }
                        else
                        {
                            if (undirectedListGraph != nullptr)  cout << undirectedListGraph->ToString() << '\n';
                            if (undirectedMatrixGraph != nullptr)  cout << undirectedMatrixGraph->ToString() << '\n';
                        }
                    }
                else if ( option == "3")
                {
                    if (problemToTest == Problem::Mst)
                    {
                        cout << "\nList\n";
                        PrimAlgorithmOnUndirectedListGraphTester tester1;
                        count << tester1.TestGraphAlgorithm(*undirectedListGraph).c_str();
                        cout << "\nMatrix\n";
                        PrimAlgorithmOnUndirectedMatrixGraphTester tester2;
                        count << tester2.TestGraphAlgorithm(*undirectedMatrixGraph).c_str();
                    }
                    else
                    {
                        
                    }
                }
                else if ( option == "4")
                {
                    
                }
                else if ( option == "7")
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
