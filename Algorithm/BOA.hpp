#pragma once

#include "Algorithm.hpp"
#include "Service/Graph.hpp"
#include "Service/PPF.hpp"
#include "Containers/MapSetOpen.hpp"

class BOA : public Algorithm {
public:
    BOA(std::unique_ptr<Open<Node>> open, std::unique_ptr<Open<Node>> solutions,
        std::function<float(int)> hDistFunc, std::function<float(int)> hTimeFunc);

    void runAlgorithm(const Options &opts) override;

private:
    void runAlgorithmImpl(const Graph &graph, int startId, int goalId);
    float gMin(int id);

    std::unique_ptr<Open<Node>> open_;
    std::unique_ptr<Open<Node>> solutions_;
    std::function<float(int)> hDistFunc_;
    std::function<float(int)> hTimeFunc_;

    std::unordered_map<int, float> gMin_;
};
