#pragma once

#include "Algorithm.hpp"
#include "Service/Graph.hpp"
#include "Service/PPF.hpp"
#include "Containers/MapSetOpen.hpp"
#include <memory>

class BOA : public Algorithm {
public:
    BOA(std::unique_ptr<Open<NodePtr>> open, std::unique_ptr<Open<NodePtr>> solutions,
        std::function<float(int)> hDistFunc, std::function<float(int)> hTimeFunc);

    void runAlgorithm(const Options &opts) override;

private:
    void runAlgorithmImpl(const Graph &graph, int startId, int goalId);
    float gMin(int id);
    void setGMin(int id, float newG);

    std::unique_ptr<Open<NodePtr>> open_;
    std::unique_ptr<Open<NodePtr>> solutions_;
    std::function<float(int)> hDistFunc_;
    std::function<float(int)> hTimeFunc_;

    std::unordered_map<int, float> gMin_;
};
