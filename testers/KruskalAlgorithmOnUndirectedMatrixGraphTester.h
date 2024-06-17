#pragma once
#include <iostream>
#include "GraphMstAlgorithmTester.h"
#include "KruskalAlgorithmOnUndirectedListGraphTester.h"
#include "../models/MatrixGraph.h"

using namespace std;

class KruskalAlgorithmOnUndirectedMatrixGraphTester : public GraphMstAlgorithmTester<MatrixGraph>
{
public:
    virtual ~KruskalAlgorithmOnUndirectedMatrixGraphTester() = default;

    std::string TestGraphAlgorithm(const MatrixGraph& graph, bool outputResults) const override;

private:
};
