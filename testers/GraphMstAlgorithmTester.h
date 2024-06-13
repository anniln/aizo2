#pragma once

template <typename T>
class GraphMstAlgorithmTester
{
public:
    GraphMstAlgorithmTester() = default;
    ~GraphMstAlgorithmTester() = default;

    virtual void TestGraphAlgorithm(const T& graph) const = 0;
};
