#pragma once
#include <fstream>

#include "testers/GraphShortPathAlgorithmTester.h"
#include "testers/PrimAlgorithmOnUndirectedListGraphTester.h"

class Simulation
{
public:
    static void Execute();
private:
    template <typename T>
    static long long ExecuteAlgorithmOnGraph(ofstream& file, const GraphMstAlgorithmTester<T>& tester,
                                        const char* algorithmName, const T& graph, float fill, int nodeCount, int iteration);
    template <typename T>
    static long long ExecuteAlgorithmOnGraph(ofstream& file, const GraphShortPathAlgorithmTester<T>& tester,
                                        const char* algorithmName, const T& graph, float fill, int nodeCount, int iteration, int startNode, int endNode);
    
    static void WriteAlgorithmAverageTime(ofstream& file, const char* algorithmName, float fill, int nodeCount,
                                          long long avarageTime);
};

