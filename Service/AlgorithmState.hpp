#pragma once

#include "Node.hpp"
#include "Options.hpp"

struct AlgorithmState {
    std::vector<Node> openNodes;
    std::vector<Node> solutions;
};

using AlgorithmStateHistory = std::vector<AlgorithmState>;

void writeHistory(const AlgorithmStateHistory& history, const Options& opts);
