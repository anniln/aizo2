#include "Simulation.h"

#include <chrono>
#include <fstream>
#include <iostream>

#include "testers/BellmanFordAlgorithmOnDirectedListGraphTester.h"
#include "testers/BellmanFordAlgorithmOnDirectedMatrixGraph.h"
#include "testers/DijkstryAlgorithmOnDirectedListGraph.h"
#include "testers/DijkstryAlgorithmOnDirectedMatrixGraph.h"
#include "testers/KruskalAlgorithmOnUndirectedMatrixGraphTester.h"
#include "testers/PrimAlgorithmOnUndirectedListGraphTester.h"
#include "testers/PrimAlgorithmOnUndirectedMatrixGraphTester.h"
#include "utils/GraphGenerator.h"
#include "utils/TimeUtils.h"


using namespace std;

const float fills[3] = {
    0.5, 0.75, 0.99
};

const int nodeCounts[7] = {
    10, 30, 50, 70, 90, 110, 130
};

void Simulation::Execute()
{
    string testOutput = R"(C:\Temp\GraphTest)";
    auto iterations = 50;

    const BellmanFordAlgorithmOnDirectedListGraphTester bellmanFordAlgorithmOnDirectedListGraphTester;
    const BellmanFordAlgorithmOnDirectedMatrixGraphTester bellmanFordAlgorithmOnDirectedMatrixGraphTester;
    const DijkstryAlgorithmOnDirectedListGraph dijkstryAlgorithmOnDirectedListGraphTester;
    const DijkstryAlgorithmOnDirectedMatrixGraph dijkstryAlgorithmOnDirectedMatrixGraphTester;
    const KruskalAlgorithmOnUndirectedMatrixGraphTester kruskalAlgorithmOnUndirectedMatrixGraphTester;
    const KruskalAlgorithmOnUndirectedListGraphTester kruskalAlgorithmOnUndirectedGraphTester;
    const PrimAlgorithmOnUndirectedListGraphTester primAlgorithmOnUndirectedListGraphTester;
    const PrimAlgorithmOnUndirectedMatrixGraphTester primAlgorithmOnUndirectedMatrixGraphTester;
    
    try
    {
        std::cout << "Start simulation: Number of iterations: " << iterations << ", OutputDir=" << testOutput << "\n";

        // otwarcie pliku csv dla wyników: z nazwą Simulation + biezacy_czas
        std::ofstream file(
            testOutput + (testOutput.back() == '\\' ? "" : "\\") + "Simulation_" + TimeUtils::CurrentTimeAsString() +
            ".csv");

        // nagłowki w pliku csv - + kolumny per ilośc iteracji
        file << "Algorithm;Fill;NodeCount;Iteration;IterationTime;AverageTime" << "\n";

        for (auto fill : fills)
        {
            for (auto nodeCount : nodeCounts)
            {
                const int startNode = 0;
                const int endNode = nodeCount / 2;
                long long primAlgorithmOnUndirectedListGraphTesterTime = 0;
                long long kruskalAlgorithmOnUndirectedGraphTesterTime = 0;

                long long kruskalAlgorithmOnUndirectedMatrixGraphTesterTime = 0;
                long long primAlgorithmOnUndirectedMatrixGraphTesterTime = 0;

                long long dijkstryAlgorithmOnDirectedListGraphTesterTime = 0;
                long long bellmanFordAlgorithmOnDirectedListGraphTesterTime = 0;

                long long dijkstryAlgorithmOnDirectedMatrixGraphTime = 0;
                long long bellmanFordAlgorithmOnDirectedMatrixGraphTime = 0;

                for (int i = 0; i < iterations; i++)
                {
                    const ListGraph* listGraphUndirected = GraphGenerator::GenerateListGraphRepresentation(Undirected, nodeCount, fill);
                    primAlgorithmOnUndirectedListGraphTesterTime += ExecuteAlgorithmOnGraph<ListGraph>(file, primAlgorithmOnUndirectedListGraphTester, "PrimAlgorithmOnUndirectedListGraphTester", *listGraphUndirected, fill, nodeCount, i);
                    kruskalAlgorithmOnUndirectedGraphTesterTime += ExecuteAlgorithmOnGraph<ListGraph>(file, kruskalAlgorithmOnUndirectedGraphTester, "KruskalAlgorithmOnUndirectedGraphTester", *listGraphUndirected, fill, nodeCount, i);

                    const MatrixGraph* matrixGraphUndirected = GraphGenerator::ListGraphToMatrixGraph(*listGraphUndirected);
                    primAlgorithmOnUndirectedMatrixGraphTesterTime += ExecuteAlgorithmOnGraph<MatrixGraph>(file, primAlgorithmOnUndirectedMatrixGraphTester, "PrimAlgorithmOnUndirectedMatrixGraphTester", *matrixGraphUndirected, fill, nodeCount, i);
                    kruskalAlgorithmOnUndirectedMatrixGraphTesterTime += ExecuteAlgorithmOnGraph<MatrixGraph>(file, kruskalAlgorithmOnUndirectedMatrixGraphTester, "KruskalAlgorithmOnUndirectedMatrixGraphTester", *matrixGraphUndirected, fill, nodeCount, i);

                    delete listGraphUndirected;
                    delete matrixGraphUndirected;

                    const ListGraph* listGraphDirected = GraphGenerator::GenerateListGraphRepresentation(Directed, nodeCount, fill);
                    
                    dijkstryAlgorithmOnDirectedListGraphTesterTime += ExecuteAlgorithmOnGraph<ListGraph>(file, dijkstryAlgorithmOnDirectedListGraphTester, "DijkstryAlgorithmOnDirectedListGraph", *listGraphDirected, fill, nodeCount, i, startNode, endNode);
                    bellmanFordAlgorithmOnDirectedListGraphTesterTime += ExecuteAlgorithmOnGraph<ListGraph>(file, bellmanFordAlgorithmOnDirectedListGraphTester, "bellmanFordAlgorithmOnDirectedListGraphTester", *listGraphDirected, fill, nodeCount, i, startNode, endNode);

                    const MatrixGraph* matrixGraphDirected = GraphGenerator::ListGraphToMatrixGraph(*listGraphDirected);
                    dijkstryAlgorithmOnDirectedMatrixGraphTime += ExecuteAlgorithmOnGraph<MatrixGraph>(file, dijkstryAlgorithmOnDirectedMatrixGraphTester, "DijkstryAlgorithmOnDirectedMatrixGraphTester", *matrixGraphDirected, fill, nodeCount, i, startNode, endNode);
                    bellmanFordAlgorithmOnDirectedMatrixGraphTime += ExecuteAlgorithmOnGraph<MatrixGraph>(file, bellmanFordAlgorithmOnDirectedMatrixGraphTester, "BellmanFordAlgorithmOnDirectedMatrixGraphTester", *matrixGraphDirected, fill, nodeCount, i, startNode, endNode);

                    delete listGraphDirected;
                    delete matrixGraphDirected;
                }
                WriteAlgorithmAverageTime(file, "PrimAlgorithmOnUndirectedListGraphTester", fill, nodeCount, primAlgorithmOnUndirectedListGraphTesterTime);
                WriteAlgorithmAverageTime(file, "KruskalAlgorithmOnUndirectedGraphTester", fill, nodeCount, kruskalAlgorithmOnUndirectedGraphTesterTime);
                WriteAlgorithmAverageTime(file, "PrimAlgorithmOnUndirectedMatrixGraphTester", fill, nodeCount, primAlgorithmOnUndirectedMatrixGraphTesterTime);
                WriteAlgorithmAverageTime(file, "KruskalAlgorithmOnUndirectedMatrixGraphTester", fill, nodeCount, kruskalAlgorithmOnUndirectedMatrixGraphTesterTime);
                WriteAlgorithmAverageTime(file, "DijkstryAlgorithmOnDirectedListGraph", fill, nodeCount, dijkstryAlgorithmOnDirectedListGraphTesterTime);
                WriteAlgorithmAverageTime(file, "bellmanFordAlgorithmOnDirectedListGraphTester", fill, nodeCount, bellmanFordAlgorithmOnDirectedListGraphTesterTime);
                WriteAlgorithmAverageTime(file, "DijkstryAlgorithmOnDirectedMatrixGraphTester", fill, nodeCount, dijkstryAlgorithmOnDirectedMatrixGraphTime);
                WriteAlgorithmAverageTime(file, "BellmanFordAlgorithmOnDirectedMatrixGraphTester", fill, nodeCount, bellmanFordAlgorithmOnDirectedMatrixGraphTime);
                
            }
        }
        // zamknięcie pliku
        file.close();
    }
    catch
    (std::exception& e)
    {
        cout << "Caught exception: " << e.what() << endl;
    }
}
void Simulation::WriteAlgorithmAverageTime(ofstream& file, const char* algorithmName, float fill, int nodeCount, long long avarageTime)
{
    //"Algorithm;Fill;NodeCount;Iteration;IterationTime;Average"
    std::string line;
    line.append(algorithmName)
    .append(";").append(to_string(fill))
    .append(";").append(to_string(nodeCount))
    .append(";-1")
    .append(";").append(TimeUtils::FormatMicrosecondToMilliseconds(avarageTime))
    .append(";");
    
    cout << line << "\n" << "\n";
    
    file << line << "\n";
    file.flush();
}



template <typename T>
long long Simulation::ExecuteAlgorithmOnGraph(ofstream& file, const GraphMstAlgorithmTester<T>& tester,
    const char* algorithmName, const T& graph, float fill, int nodeCount, int iteration)
{
    const auto start = std::chrono::high_resolution_clock::now();
    tester.TestGraphAlgorithm(graph);
    const auto end = std::chrono::high_resolution_clock::now();
    long long durationMs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();   

    //"Algorithm;Fill;NodeCount;Iteration;IterationTime;Average"
    std::string line;
    line.append(algorithmName)
    .append(";").append(to_string(fill))
    .append(";").append(to_string(nodeCount))
    .append(";").append(to_string(iteration))
    .append(";").append(TimeUtils::FormatMicrosecondToMilliseconds(durationMs))
    .append(";");
    file << line << "\n";
    file.flush();
    return durationMs;
}

template <typename T>
long long Simulation::ExecuteAlgorithmOnGraph(ofstream& file, const GraphShortPathAlgorithmTester<T>& tester,
    const char* algorithmName, const T& graph, float fill, int nodeCount, int iteration, int startNode, int endNode)
{
    const auto start = std::chrono::high_resolution_clock::now();
    tester.TestGraphAlgorithm(graph, startNode, endNode);
    const auto end = std::chrono::high_resolution_clock::now();
    long long durationMs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();   

    //"Algorithm;Fill;NodeCount;Iteration;IterationTime;Average"
    std::string line;
    line.append(algorithmName)
    .append(";").append(to_string(fill))
    .append(";").append(to_string(nodeCount))
    .append(";").append(to_string(iteration))
    .append(";").append(TimeUtils::FormatMicrosecondToMilliseconds(durationMs))
    .append(";");
    file << line << "\n";
    file.flush();
    return durationMs;
}
