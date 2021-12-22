#pragma once

#include "Algorithm.hpp"
#include "Service/Graph.hpp"
#include "Service/PPF.hpp"
#include "Containers/PPFOpen.hpp"
#include "Containers/PPFClosed.hpp"

class PPA : public Algorithm {
public:
    PPA(std::unique_ptr<PPFOpen> open, std::unique_ptr<PPFClosed> closed,
        std::function<float(int)> hDistFunc, std::function<float(int)> hTimeFunc);

    void runAlgorithm(const Options &opts) override;

private:
    void runAlgorithmImpl(const Graph &graph, int idStart, int idGoal);

    std::unique_ptr<PPFOpen> open_;
    std::unique_ptr<PPFClosed> closed_;
    std::function<float(int)> hDistFunc_;
    std::function<float(int)> hTimeFunc_;
};
