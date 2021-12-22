#pragma once

#include "Algorithm.hpp"
#include "Service/Graph.hpp"
#include "Service/PPF.hpp"
#include "Containers/PPFOpen.hpp"
#include "Containers/PPFClosed.hpp"

class PPA : public Algorithm {
public:
    PPA(std::unique_ptr<PPFOpen> open, std::unique_ptr<PPFClosed> closed);

    void runAlgorithm(const Options &opts) override;

private:
    void runAlgorithmImpl(const Graph &graph, int idStart, int idGoal);

    std::pair<float, float> getHeuristic(const Position& position) const;

    std::unique_ptr<PPFOpen> _open;
    std::unique_ptr<PPFClosed> _closed;
};
