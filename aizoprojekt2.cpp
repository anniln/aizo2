#include <iostream>

#include "testers/BellmanFordAlgorithmOnDirectedListGraph.h"
#include "testers/BellmanFordAlgorithmOnDirectedMatrixGraph.h"
#include "testers/DijkstryAlgorithmOnDirectedListGraph.h"
#include "testers/DijkstryAlgorithmOnDirectedMatrixGraph.h"
#include "testers/KluskalAlgorithmOnUndirectedGraphTester.h"
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
    //ListGraph* graph = GraphGenerator::GenerateListGraphRepresentation(GraphType::Directed, 10, 0.75);
    //cout << graph->ToString();
    //DijkstryAlgorithmOnDirectedListGraph tester;
    //tester.TestGraphAlgorithm(*graph, 0, 7);
    //BellmanFordAlgorithmOnDirectedListGraph tester2;
    //tester2.TestGraphAlgorithm(*graph, 0, 7);
    //delete graph;

    MatrixGraph* graph = GraphGenerator::GenerateMatrixGraphRepresentation(GraphType::Directed,11, 0.5);
    cout << graph->ToString();
    // DijkstryAlgorithmOnDirectedMatrixGraph tester;
    // tester.TestGraphAlgorithm(*graph,0,2);
    BellmanFordAlgorithmOnDirectedMatrixGraph tester2;
    tester2.TestGraphAlgorithm(*graph,0,5);
    delete graph;
    
    //ListGraph* graph = GraphGenerator::GenerateListGraphRepresentation(5, 0.5);
    //cout << graph->ToString();
    //PrimAlgorithmOnUndirectedListGraphTester tester;
    //tester.TestGraphAlgorithm(*graph);
    //delete graph;

    // MatrixGraph* graph = GraphGenerator::GenerateMatrixGraphRepresentation(7, 0.5);
    // cout << graph->ToString();
    // cout.flush();
    // PrimAlgorithmOnUndirectedMatrixGraphTester tester;
    // tester.TestGraphAlgorithm(*graph);
    // KruskalAlgorithmOnMatrixGraphTester tester2;
    // tester2.TestGraphAlgorithm(*graph);
    // delete graph;

    // MatrixGraph graph3(5, 7);
    // graph3.AddEdge(0,0, 1, 2);
    // graph3.AddEdge(1,0, 3, 6);
    // graph3.AddEdge(2,1, 2, 3);
    // graph3.AddEdge(3,1, 3, 8);
    // graph3.AddEdge(4,1, 4, 5);
    // graph3.AddEdge(5,2, 4, 7);
    // graph3.AddEdge(6,3, 4, 9);
    //
    // cout << graph3.ToString();
    // PrimAlgorithmOnUndirectedMatrixGraphTester tester3;
    // tester3.TestGraphAlgorithm(graph3);
    //delete graph3;

    // MatrixGraph* graph2 = GraphGenerator::GenerateMatrixGraphRepresentation(5, 0.75);
    // cout << graph2->ToString();
    // PrimAlgorithmOnUndirectedMatrixGraphTester tester2;
    // tester2.TestGraphAlgorithm(*graph2);
    // delete graph2;
    
    // ListGraph* graph = GraphGenerator::GenerateListGraphRepresentation(5, 0.5);
    // cout << graph->ToString();
    // cout.flush();
    // KluskalAlgorithmOnUndirectedGraphTester tester;
    // PrimAlgorithmOnUndirectedListGraphTester tester2;
    // tester.TestGraphAlgorithm(*graph);
    // tester2.TestGraphAlgorithm(*graph);
    // delete graph;
    return 0;
}

// int main2(int argc, char* argv[])
// {
//     try
//     {
//         string testOutput = R"(C:\Temp\SortTest)";
//         const auto fill = 0.05f;
//         const auto numberOfNodes = 5;
//         const auto testIterations = 100;
//
//         auto graphRepresentation = GraphRepresentation::List;
//         Problem problemToTest;
//
//         MatrixGraph* directedMatrixGraph = nullptr;
//         MatrixGraph* undirectedMatrixGraph = nullptr;
//         ListGraph* directedListGraph = nullptr;
//         ListGraph* undirectedListGraph = nullptr;
//         do
//         {
//             cout << "\n\n";
//             cout << "Author: Anna Ilnicka-Wandycz (CZW/N 11:15)\n";
//             cout << "Ctrl+C to exit program\n";
//
//             string representation;
//             cout << "Graph representation ('list' = ('d')efault or 'matrix'): ";
//             cin >> representation;
//             graphRepresentation = representation == "matrix" ? GraphRepresentation::Matrix : GraphRepresentation::List;
//
//             string problem;
//             cout << "Problem to test ('mst' = ('d')efault or 'sp' ShortestPath): ";
//             cin >> problem;
//             problemToTest = problem == "sp" ? Problem::ShortPath : Problem::Mst;
//
//             string option = "9";
//             do
//             {
//                 cout << "\n\n";
//                 cout << "Menu for graph: " << GetGraphRepresentationName(graphRepresentation) << ", problem: " <<
//                     GetProblemName(problemToTest) << "\n";
//                 cout << "'0' - Read data from file \n";
//                 cout << "'1' - Generate random graph \n";
//                 cout << "'2' - Print graph \n";
//                 cout << "'3' - Algorithm " << (problemToTest == Problem::Mst ? "Prim" : "Dijkstra") << "\n";
//                 cout << "'4' - Algorithm " << (problemToTest == Problem::Mst ? "Kruskal" : "Ford-Bellmann") << "\n";
//                 cout << "'9' - Back to previous menu" << "\n";
//                 cin >> option;
//                 
//                 if (option == "0")
//                 {
//                     
//                 }
//                 else if (option == "1")
//                     {
//                         if (graphRepresentation == GraphRepresentation::List)
//                         {
//                             directedListGraph = FreeGraph<ListGraph>(directedListGraph);
//                             undirectedListGraph = FreeGraph<ListGraph>(undirectedListGraph);
//                             undirectedListGraph = GraphGenerator::GenerateListGraphRepresentation(GraphType::Undirected, numberOfNodes, fill);
//                         }
//                         else
//                         {
//                             directedMatrixGraph = FreeGraph<MatrixGraph>(directedMatrixGraph);
//                             undirectedMatrixGraph = FreeGraph<MatrixGraph>(undirectedMatrixGraph);
//                             undirectedMatrixGraph = GraphGenerator::GenerateMatrixGraphRepresentation(GraphType::Undirected, numberOfNodes, fill);
//                         }
//                     }
//                 else if ( option == "2")
//                     {
//                         if (graphRepresentation == GraphRepresentation::List)
//                         {
//                             if (directedListGraph != nullptr)  cout << directedListGraph->ToString() << '\n';
//                             if (undirectedListGraph != nullptr)  cout << undirectedListGraph->ToString() << '\n';
//                         }
//                         else
//                         {
//                             if (directedMatrixGraph != nullptr)  cout << directedMatrixGraph->ToString() << '\n';
//                             if (undirectedMatrixGraph != nullptr)  cout << undirectedMatrixGraph->ToString() << '\n';
//                         }
//                     }
//                 else if ( option == "3")
//                 {
//                     
//                 }
//                 else if ( option == "4")
//                 {
//                     
//                 }
//             }
//             while (option != "9");
//             
//             directedListGraph = FreeGraph<ListGraph>(directedListGraph);
//             undirectedListGraph = FreeGraph<ListGraph>(undirectedListGraph);
//             directedMatrixGraph = FreeGraph<MatrixGraph>(directedMatrixGraph);
//             undirectedMatrixGraph = FreeGraph<MatrixGraph>(undirectedMatrixGraph);
//         }
//         while (true);
//     }
//     catch (const std::exception& e)
//     {
//         std::cout << "Caught exception: " << e.what() << '\n';
//     }
//
//     return 0;
// }
