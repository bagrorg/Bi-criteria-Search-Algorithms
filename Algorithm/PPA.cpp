#include "PPA.hpp"

PPA::PPA(std::unique_ptr<PPFOpen> open, std::unique_ptr<PPFClosed> closed)
    : Algorithm("PP-A*"), _open(std::move(open)), _closed(std::move(closed)) {}

void PPA::runAlgorithm(const Options &opts) {
    const Graph graph = [&opts]() -> Graph {
        std::vector<Vertex> vs;
        parseGraph(opts.graph_file, vs);
        return Graph(std::move(vs));
    }();

    for (int i = 0; i < opts.iterations; i++) {
        runAlgorithmImpl(graph, opts.startId, opts.goalId);
        _open->clear();
        _closed->clear();
    }
}

void PPA::runAlgorithmImpl(const Graph &graph, int idStart, int idGoal) {
    {
        const Vertex &v = graph.getVertex(idStart);
        auto [hDist, hTime] = getHeuristic(v.position);
        Node startNode(
            v,
            HeuristicStats{0, hDist, hDist},
            HeuristicStats{0, hTime, hTime}
        );
        _open->add(PPF(idStart, startNode, startNode));
    }

    while (!_open->isEmpty()) {
        PPF pair = _open->getBest();

        if (_open->isDominated(pair)) continue;
        if (pair.getId() == idGoal) {
            // mergeSolution(pair);
            continue;
        }

        for (const Edge &edge: graph.getNeighbours(pair.getId())) {
            const Vertex &v = graph.getVertex(idStart);
            auto [hDist, hTime] = getHeuristic(v.position);
            PPF newPair = pair.extend(edge, graph, hDist, hTime);
            if (_open->isDominated(newPair)) continue;
            _open->add(std::move(newPair));
        }
    }
}

std::pair<float, float> PPA::getHeuristic(const Position& position) const {
    return {0.f, 0.f};
}
