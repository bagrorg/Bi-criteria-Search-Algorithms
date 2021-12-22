#include "BOA.hpp"

BOA::BOA(std::unique_ptr<Open<NodePtr>> open, std::unique_ptr<Open<NodePtr>> solutions,
         std::function<float(int)> hDistFunc, std::function<float(int)> hTimeFunc)
    : Algorithm("BOA*"),
      open_(std::move(open)), solutions_(std::move(solutions)),
      hDistFunc_(std::move(hDistFunc)), hTimeFunc_(std::move(hTimeFunc)) {}

void BOA::runAlgorithm(const Options &opts) {
    const Graph graph = [&opts]() -> Graph {
        std::vector<Vertex> vs;
        parseGraph(opts.graphFile, vs);
        return Graph(std::move(vs));
    }();

    for (int i = 0; i < opts.iterations; i++) {
        runAlgorithmImpl(graph, opts.startId, opts.goalId);
        open_->clear();
        solutions_->clear();
    }
}

float BOA::gMin(int id) {
    return gMin_.find(id) == gMin_.end() ? std::numeric_limits<float>::infinity() : gMin_[id];
}

void BOA::setGMin(int id, float newG) {
    gMin_[id] = newG;
}

void BOA::runAlgorithmImpl(const Graph &graph, int startId, int goalId) {
    {
        float hDist = hDistFunc_(startId);
        float hTime = hTimeFunc_(startId);
        auto startNode = std::make_shared<Node>(
            graph.getVertex(startId),
            HeuristicStats{0, hDist, hDist},
            HeuristicStats{0, hTime, hTime}
        );
        open_->add(startNode);
    }

    while (!open_->isEmpty()) {
        auto best = open_->getBest();

        if (best->getHeuristicStatsTime().g >= gMin(best->getVertex().id) || best->getHeuristicStatsTime().F >= gMin(goalId)) continue;
        setGMin(best->getVertex().id, best->getHeuristicStatsTime().g);
        if (best->getVertex().id == goalId) {
            solutions_->add(best);
            continue;
        }

        for (const Edge &edge: graph.getNeighbours(best->getVertex().id)) {
            float hDist = hDistFunc_(edge.to_id);
            float hTime = hTimeFunc_(edge.to_id);
            auto newNode = std::make_shared<Node>(Node::extend(edge, graph, hDist, hTime, best));
            if (newNode->getHeuristicStatsTime().g >= gMin(newNode->getVertex().id) || newNode->getHeuristicStatsTime().F >= gMin(goalId)) continue;
            open_->add(std::move(newNode));
        }
    }
}
