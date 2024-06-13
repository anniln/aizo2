#pragma once

template <typename T>
class GraphShortPathAlgorithmTester
{
public:
    GraphShortPathAlgorithmTester() = default;
    ~GraphShortPathAlgorithmTester() = default;

    virtual void TestGraphAlgorithm(const T& graph, int startNode, int endNode) const = 0;
};
