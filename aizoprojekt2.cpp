
#include <iostream>

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

int main(int argc, char* argv[])
{
    try {
    ListGraph listGraph = GraphGenerator::GenerateListGraphRepresentation(5, 0.5);
    cout << listGraph.ToString();
    MatrixGraph matrixGraph = GraphGenerator::ListGraphToMatrixGraph(listGraph);
        cout << matrixGraph.ToString();
        cout.flush();
    ListGraph listGraph2 = GraphGenerator::MatrixGraphToListGraph(matrixGraph);
        cout << listGraph2.ToString();
    
    // string testOutput = R"(C:\Temp\SortTest)";
    // auto testIterations = 100;
    //
    // auto graphRepresentation = GraphRepresentation::List;
    // Problem problemToTest;
    //
    // char optionNumber;
    // do
    // {
    //     cout << "\n\n";
    //     cout << "Author: Anna Ilnicka-Wandycz (CZW/N 11:15)\n";
    //     cout << "Ctrl+C to exit program\n";
    //
    //     string representation;
    //     cout << "Graph representation ('list' = ('d')efault or 'matrix'): ";
    //     cin >> representation;
    //     graphRepresentation = representation == "matrix" ? GraphRepresentation::Matrix : GraphRepresentation::List;
    //     
    //     string problem;
    //     cout << "Problem to test ('mst' = ('d')efault or 'sp' ShortestPath): ";
    //     cin >> problem;
    //     problemToTest = problem == "sp" ? Problem::ShortPath : Problem::Mst;
    //
    //     string option = "9";
    //     do
    //     {
    //         cout << "\n\n";
    //         cout << "Menu for graph: " << GetGraphRepresentationName(graphRepresentation) << ", problem: " << GetProblemName(problemToTest) << "\n";
    //         cout << "'0' - Read data from file \n";
    //         cout << "'1' - Generate random graph \n";
    //         cout << "'2' - Print graph \n";
    //         cout << "'3' - Algorithm " << (problemToTest == Problem::Mst ? "Prim" : "Dijkstra") << "\n";
    //         cout << "'4' - Algorithm " << (problemToTest == Problem::Mst ? "Kruskal" : "Ford-Bellmann") << "\n";
    //         cout << "'9' - Back to previous menu" << "\n";
    //         cin >> option;
    //     } while (option != "9");
    //
    //     
    // } while (true);
    } catch (const std::exception& e)
    {
        std::cout << "Caught exception: " << e.what() << '\n';
    }
    
    return 0;
}
