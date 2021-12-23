#include "BOA.hpp"
#include "Service/BOANode.hpp"

BOA::BOA(std::unique_ptr<MapSetOpen> open, std::unique_ptr<MapSetOpen> solutions,
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

void BOA::updateHistory() {
    history_.push_back({
        open_->getAllNodes(),
        solutions_->getAllNodes()
    });
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
        BOANode st = BOANode(startId, startNode);
        open_->add(st);
        if (writeHistory) updateHistory();
    }

    while (!open_->isEmpty()) {
        auto best = open_->getBest();
        std::cout << best.getId() << std::endl;

        if (best.getNode()->getHeuristicStatsTime().g >= gMin(best.getId()) || 
            best.getNode()->getHeuristicStatsTime().F >= gMin(goalId)) continue;
        setGMin(best.getId(), best.getNode()->getHeuristicStatsTime().g);
        if (best.getId() == goalId) {
            solutions_->add(best);
            if (writeHistory) updateHistory();
            continue;
        }

        for (const Edge &edge: graph.getNeighbours(best.getId())) {
            float hDist = hDistFunc_(edge.to_id);
            float hTime = hTimeFunc_(edge.to_id);
            auto newNode = best.extend(edge, graph, hDist, hTime);
            if (newNode.getNode()->getHeuristicStatsTime().g >= gMin(newNode.getId()) || 
                newNode.getNode()->getHeuristicStatsTime().F >= gMin(goalId)) continue;
            open_->add(std::move(newNode));
        }
        if (writeHistory) updateHistory();
        
    }
}
