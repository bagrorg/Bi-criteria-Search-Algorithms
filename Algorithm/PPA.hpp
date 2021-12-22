#pragma once

#include "Algorithm.hpp"
#include "Service/Graph.hpp"
#include "Service/PPF.hpp"
#include "Containers/PPFOpen.hpp"

class PPA : public Algorithm {
public:
    PPA(std::unique_ptr<PPFOpen> open, std::unique_ptr<PPFOpen> solutions,
        std::function<float(int)> hDistFunc, std::function<float(int)> hTimeFunc);

    void runAlgorithm(const Options &opts) override;

private:
    void runAlgorithmImpl(const Graph &graph, const Options& opts);

    void updateHistory();

    std::unique_ptr<PPFOpen> open_;
    std::unique_ptr<PPFOpen> solutions_;
    std::function<float(int)> hDistFunc_;
    std::function<float(int)> hTimeFunc_;
};
