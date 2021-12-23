#pragma once

#include "Node.hpp"
#include "Options.hpp"

struct AlgorithmState {
    std::vector<Node> addedNodes;
    std::vector<Node> addedSolutions;
};

using AlgorithmStateHistory = std::vector<AlgorithmState>;

void writeHistory(const AlgorithmStateHistory& history, const Options& opts);
