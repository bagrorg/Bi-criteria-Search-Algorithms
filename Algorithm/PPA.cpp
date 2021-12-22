#include "PPA.hpp"

PPA::PPA(std::unique_ptr<PPFOpen> open, std::unique_ptr<PPFOpen> solutions,
         std::function<float(int)> hDistFunc, std::function<float(int)> hTimeFunc)
    : Algorithm("PP-A*"),
      open_(std::move(open)), solutions_(std::move(solutions)),
      hDistFunc_(std::move(hDistFunc)), hTimeFunc_(std::move(hTimeFunc)) {}

void PPA::runAlgorithm(const Options &opts) {
    const Graph graph = [&opts]() -> Graph {
        std::vector<Vertex> vs;
        parseGraph(opts.graphFile, vs);
        return Graph(std::move(vs));
    }();
    open_->withEpsDist(opts.epsDist);
    open_->withEpsTime(opts.epsTime);
    solutions_->withEpsDist(opts.epsDist);
    solutions_->withEpsTime(opts.epsTime);

    for (int i = 0; i < opts.iterations; i++) {
        runAlgorithmImpl(graph, opts.startId, opts.goalId);
        open_->clear();
        solutions_->clear();
    }
}

void PPA::runAlgorithmImpl(const Graph &graph, int startId, int goalId) {
    {
        float hDist = hDistFunc_(startId);
        float hTime = hTimeFunc_(startId);
        Node startNode(
            graph.getVertex(startId),
            HeuristicStats{0, hDist, hDist},
            HeuristicStats{0, hTime, hTime}
        );
        open_->add(PPF(startId, startNode, startNode));
    }

    while (!open_->isEmpty()) {
        PPF pair = open_->getBest();

        if (open_->isDominated(pair, goalId)) continue;
        if (pair.getId() == goalId) {
            solutions_->add(pair);
            continue;
        }

        for (const Edge &edge: graph.getNeighbours(pair.getId())) {
            float hDist = hDistFunc_(edge.to_id);
            float hTime = hTimeFunc_(edge.to_id);
            PPF newPair = pair.extend(edge, graph, hDist, hTime);
            if (open_->isDominated(newPair, goalId)) continue;
            open_->add(std::move(newPair));
        }
    }
}
