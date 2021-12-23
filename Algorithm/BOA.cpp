#include "BOA.hpp"
#include "Service/BOANode.hpp"
#include <chrono>

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
        runAlgorithmImpl(graph, opts);
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
        open_->getAddedNodes(),
        solutions_->getAddedNodes()
    });
}

bool BOA::isDominated(const BOANode& node, int goalId, float epsTime) {
    bool dominatedByNode = node.getNode()->getHeuristicStatsTime().g >= gMin(node.getId());
    bool dominatedBySolution = (1 + epsTime) * node.getNode()->getHeuristicStatsTime().F >= gMin(goalId);
    return dominatedBySolution || dominatedByNode;
}

void BOA::runAlgorithmImpl(const Graph &graph, const Options& opts) {
    long countOfExpansions = 0;
    long countOfIterations = 0;

    {
        float hDist = hDistFunc_(opts.startId);
        float hTime = hTimeFunc_(opts.startId);
        auto startNode = std::make_shared<Node>(
            graph.getVertex(opts.startId),
            HeuristicStats{0, hDist, hDist},
            HeuristicStats{0, hTime, hTime}
        );
        BOANode st = BOANode(opts.startId, startNode);
        open_->add(st);
        if (writeHistory) updateHistory();
    }
    auto host_start = std::chrono::steady_clock::now();
    while (!open_->isEmpty()) {
        countOfIterations++;
        auto best = open_->getBest();

        if (isDominated(best, opts.goalId, opts.epsTime)) continue;
        setGMin(best.getId(), best.getNode()->getHeuristicStatsTime().g);
        if (best.getId() == opts.goalId) {
            solutions_->add(best);
            if (writeHistory) updateHistory();
            continue;
        }

        for (const Edge &edge: graph.getNeighbours(best.getId())) {
            float hDist = hDistFunc_(edge.to_id);
            float hTime = hTimeFunc_(edge.to_id);
            auto newNode = best.extend(edge, graph, hDist, hTime);
            if (isDominated(newNode, opts.goalId, opts.epsTime)) continue;
            countOfExpansions++;
            open_->add(std::move(newNode));
        }
        if (writeHistory) updateHistory();
    }
    auto host_end = std::chrono::steady_clock::now();
    auto exec_time = host_end - host_start;

    std::string algo_name = "BOA*";
    if (opts.epsDist != 0 || opts.epsTime != 0) {
        algo_name += "-epsilon";
    }

    std::map<std::string, std::string> res_local = {
        {"count_of_iterations", std::to_string(countOfIterations)},
        {"count_of_expansions", std::to_string(countOfExpansions)},
        {"time_us", std::to_string(exec_time.count() / 1000)},
        {"solution_size", std::to_string(solutions_->size())},
        {"time_epsilon", std::to_string(opts.epsTime)},
        {"dist_epsilon", std::to_string(opts.epsDist)},
        {"algo", algo_name}
    };
    res_.push_back(res_local);

    solutionPaths_ = solutions_->getAllNodes();
}
