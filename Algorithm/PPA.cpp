#include "PPA.hpp"

PPA::PPA(std::unique_ptr<PPFOpen> open, std::unique_ptr<PPFClosed> closed,
         std::function<float(int)> hDistFunc, std::function<float(int)> hTimeFunc)
    : Algorithm("PP-A*"),
      open_(std::move(open)), closed_(std::move(closed)),
      hDistFunc_(std::move(hDistFunc)), hTimeFunc_(std::move(hTimeFunc)) {}

void PPA::runAlgorithm(const Options &opts) {
    const Graph graph = [&opts]() -> Graph {
        std::vector<Vertex> vs;
        parseGraph(opts.graph_file, vs);
        return Graph(std::move(vs));
    }();

    for (int i = 0; i < opts.iterations; i++) {
        runAlgorithmImpl(graph, opts.startId, opts.goalId);
        open_->clear();
        closed_->clear();
    }
}

void PPA::runAlgorithmImpl(const Graph &graph, int idStart, int idGoal) {
    {
        float hDist = hDistFunc_(idStart);
        float hTime = hTimeFunc_(idStart);
        Node startNode(
            graph.getVertex(idStart),
            HeuristicStats{0, hDist, hDist},
            HeuristicStats{0, hTime, hTime}
        );
        open_->add(PPF(idStart, startNode, startNode));
    }

    while (!open_->isEmpty()) {
        PPF pair = open_->getBest();

        if (open_->isDominated(pair)) continue;
        if (pair.getId() == idGoal) {
            // mergeSolution(pair);
            continue;
        }

        for (const Edge &edge: graph.getNeighbours(pair.getId())) {
            float hDist = hDistFunc_(edge.to_id);
            float hTime = hTimeFunc_(edge.to_id);
            PPF newPair = pair.extend(edge, graph, hDist, hTime);
            if (open_->isDominated(newPair)) continue;
            open_->add(std::move(newPair));
        }
    }
}
