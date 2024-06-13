#pragma once

template <typename T>
class GraphShortPathAlgorithmTester
{
public:
    GraphShortPathAlgorithmTester() = default;
    ~GraphShortPathAlgorithmTester() = default;

    virtual std::string TestGraphAlgorithm(const T& graph, int startNode, int endNode) const = 0;
};
