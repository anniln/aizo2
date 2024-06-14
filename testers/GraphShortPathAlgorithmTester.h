#pragma once

template <typename T>
class GraphShortPathAlgorithmTester
{
public:
    GraphShortPathAlgorithmTester() = default;
    ~GraphShortPathAlgorithmTester() = default;

    virtual std::string TestGraphAlgorithm(const T& graph, int startNode, int endNode, bool outputResults) const = 0;
};
