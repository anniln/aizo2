#pragma once

template <typename T>
class GraphAlgorithmTester
{
protected:
    ~GraphAlgorithmTester() = default;

public:
    virtual void TestGraphAlgorithm(T& graph) = 0;
};
