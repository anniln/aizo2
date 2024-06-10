#pragma once

template <typename T>
class GraphMstAlgorithmTester
{
protected:
    ~GraphMstAlgorithmTester() = default;

public:
    virtual void TestGraphAlgorithm(const T& graph) = 0;
};
