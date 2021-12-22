#pragma once

#include "Algorithm.hpp"
#include "Service/Graph.hpp"

class PPA : public Algorithm {
public:
    PPA() : Algorithm("PP-A*") {};

    void runAlgorithm(const Options &opts) override;

private:
    void runAlgorithmImpl(const Graph& graph, int idStart, int idGoal);
};
