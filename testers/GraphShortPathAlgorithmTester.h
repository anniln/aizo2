#pragma once

template <typename T>
class GraphShortPathAlgorithmTester
{
protected:
    ~GraphShortPathAlgorithmTester() = default;

public:
    virtual void TestGraphAlgorithm(const T& graph, int startNode, int endNode) = 0;
};
