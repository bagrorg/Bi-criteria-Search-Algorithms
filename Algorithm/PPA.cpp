#include "PPA.hpp"
#include <chrono>

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
        runAlgorithmImpl(graph, opts);
        open_->clear();
        solutions_->clear();
    }
}

void PPA::runAlgorithmImpl(const Graph &graph, const Options& opts) {
    bool writeHistory = !opts.historyFile.empty();
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
        open_->add(PPF(opts.startId, startNode, startNode));
        if (writeHistory) updateHistory();
    }
    auto host_start = std::chrono::steady_clock::now();
    while (!open_->isEmpty()) {
        countOfIterations++;
        PPF pair = open_->getBest();

        if (open_->isDominated(pair, opts.goalId, false)) continue;
        if (pair.getId() == opts.goalId) {
            solutions_->add(pair);
            if (writeHistory) updateHistory();
            continue;
        }
        for (const Edge &edge: graph.getNeighbours(pair.getId())) {
            float hDist = hDistFunc_(edge.to_id);
            float hTime = hTimeFunc_(edge.to_id);
            PPF newPair = pair.extend(edge, graph, hDist, hTime);
            if (open_->isDominated(newPair, opts.goalId, true)) continue;
            countOfExpansions++;
            open_->add(std::move(newPair));
        }
        if (writeHistory) updateHistory();
    }
    auto host_end = std::chrono::steady_clock::now();
    auto exec_time = host_end - host_start;

    std::map<std::string, std::string> res_local = {
        {"count_of_iterations", std::to_string(countOfIterations)},
        {"count_of_expansions", std::to_string(countOfExpansions)},
        {"time", std::to_string(exec_time.count())},
        {"solution_size", std::to_string(solutions_->size())}
    };
    res_.push_back(res_local);
    solutionPaths_ = solutions_->getAllNodes();
}

void PPA::updateHistory() {
    history_.push_back({
        open_->getAddedNodes(),
        solutions_->getAddedNodes()
    });
}
