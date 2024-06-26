﻿#pragma once
#include <string>

template <typename T>
class GraphMstAlgorithmTester
{
public:
    GraphMstAlgorithmTester() = default;
    ~GraphMstAlgorithmTester() = default;

    virtual std::string TestGraphAlgorithm(const T& graph, bool outputResults) const = 0;
};
